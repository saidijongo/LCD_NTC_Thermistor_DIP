#include <LiquidCrystal_I2C.h>

#define thermistor A0

int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

LiquidCrystal_I2C lcd(0x27,16,2); // Set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  pinMode(thermistor, INPUT); // Set thermistor pin as input
  
  Serial.begin(9600); // Initialize serial communication
  
  lcd.init(); // Initialize the LCD
  lcd.backlight(); // Turn on the backlight
  lcd.setCursor(0,0); // Set cursor to the beginning of the first line
  lcd.print("Temperature: "); // Display text on LCD
}

void loop() {
  Vo = analogRead(thermistor); // Read analog value from thermistor
  R2 = R1 * (1023.0 / (float)Vo - 1.0); // Calculate resistance of the thermistor
  logR2 = log(R2); // Calculate natural logarithm of the resistance
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2)); // Calculate temperature in Celsius
  T = T - 273.15; // Convert temperature to Celsius
  T = (T * 9.0)/ 5.0 + 32.0; // Convert temperature to Fahrenheit

  Serial.println("Temperature(F): " + String(T)); // Print temperature to serial monitor
  
  lcd.setCursor(1,1); // Set cursor to the second line, second column
  lcd.print(T); // Display temperature on LCD
  delay(500); // Delay for stability
}
