#include <DFRobot_RGBLCD1602.h>
#include <DFRobot_MAX31855.h>
#include <DFRobot_DF1101S.h>
#include <SoftwareSerial.h>

// Variables for temperature and rate of change
float temp = 0;
float lasttemp = 0;
float fpm = 0;

// Variables for timing
unsigned long lastmillis = 0;
unsigned long lastamillis = 0;

// Flags for controlling announcements
bool active = true;
bool extraactive = false;
bool off = false;
bool announced = false;

// Initialize LCD, MAX31855, DF1101S, and software serial for DF1101S
DFRobot_RGBLCD1602 lcd(0x2D, 16, 2);  // LCD object
DFRobot_MAX31855 max31855;            // Thermocouple sensor object
SoftwareSerial df1101sSerial(9, 10);  // RX, TX pins for DF1101S
DFRobot_DF1101S df1101s;              // Audio module object

void setup() {
  // Begin serial communication for debugging
  Serial.begin(115200);
  df1101sSerial.begin(115200);

  // Initialize LCD
  lcd.init();

  // Initialize DF1101S and check connection
  if (!df1101s.begin(df1101sSerial)) {
    Serial.println("Init failed, please check the wire connection!");
    delay(1000);
  }
  
  // Set volume to 80 (out of 100)
  df1101s.setVol(80);
  Serial.print("VOL:");
  // Print current volume
  Serial.println(df1101s.getVol());

  // Switch to music mode
  df1101s.switchFunction(df1101s.MUSIC);
  // Delay for the end of prompt tone
  delay(2000);

  // Set playback mode to "repeat all"
  df1101s.setPlayMode(df1101s.ALLCYCLE);
  Serial.print("PlayMode:");
  // Print current playback mode
  Serial.println(df1101s.getPlayMode());

  // Disable prompt
  df1101s.setPrompt(false);

  // Read initial temperature
  lasttemp = temperature(true);
}

void loop() {
  // Display current temperature
  display(temperature(true));

  // Check temperature announcements once per minute
  if (millis() - lastmillis > 60000) {
    Serial.println("Checking announcements...");
    announcements(temperature(true));
  }

  // Adjust announcement timing based on temperature fluctuation
  if (active) {
    if (millis() - lastamillis > 60000 * 12) { // 10 minutes
      if (!off) {
        announced = false;
        Serial.println("Reset 'announced'");
        lastamillis = millis();
      }
    }
  } else if (extraactive) {
    if (millis() - lastamillis > 60000 * 4) { // 4 minutes
      if (!off) {
        announced = false;
        Serial.println("Reset 'announced'");
        lastamillis = millis();
      }
    }
  } else {
    if (millis() - lastamillis > 60000 * 50) { // 45 minutes
      if (!off) {
        announced = false;
        Serial.println("Reset 'announced'");
        lastamillis = millis();
      }
    }
  }
}

// Function to read temperature from MAX31855 sensor
float temperature(bool F) {
  float t = 0;

  // Read temperature in Celsius or Fahrenheit
  if (!F) {
    t = max31855.readCelsius();
  } else {
    t = (max31855.readCelsius() * 1.8) + 32;
  }

  // Print temperature to serial monitor
  Serial.print("Temperature:");
  Serial.println(t);

  return t;
}

// Function to display temperature on LCD
void display(float t) {
  // Display temperature
  lcd.setCursor(0, 0);
  lcd.print("Temp (F): ");
  lcd.print(t, 1);

  // Display temperature status message
  lcd.setCursor(0, 1);
  if (t <= 350) {
    lcd.setRGB(255, 255, 0); // Yellow
    lcd.print("Creosote");
  } else if (t > 350 && t <= 650) {
    lcd.setRGB(0, 255, 0); // Green
    lcd.print("Optimal");
  } else if (t > 650) {
    lcd.setRGB(255, 0, 0); // Red
    lcd.print("Overfire");
  }

  // Display rate of change of temperature
  lcd.setCursor(9, 1);
  lcd.print("FPM:");
  lcd.print(fpm);
}

// Function to handle temperature announcements
void announcements(float temp) {
  // Determine activity level based on temperature change
  if (abs(temp - lasttemp) >= 2 && abs(temp - lasttemp) < 5) {
    active = true;
  } else {
    active = false;
  }
  if (abs(temp - lasttemp) >= 5) {
    extraactive = true;
  } else {
    extraactive = false;
  }
  Serial.println(temp - lasttemp);
  
  // Perform temperature-based announcements
  if (temp < 170) {
    if (!announced) {
      // Need more wood
      df1101s.playSpecFile(11);
      delay(4000);
      announced = true;
      active = false;
      extraactive = false;
    }
  }

  // More announcement conditions based on temperature change and threshold

  // Update last temperature and timing variables
  Serial.print("Last temp:");
  Serial.println(lasttemp);
  fpm = temp - lasttemp;
  Serial.print("F per minute:");
  Serial.println(fpm);
  lasttemp = temp;
  lastmillis = millis();
}
