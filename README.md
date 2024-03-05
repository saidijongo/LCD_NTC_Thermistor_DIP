# LCD_NTC_Thermistor_DIP
Reading temperature values with NTC (Negative Temperature Coefficient) thermistor and displaying them on LCD.

LCD Communication lines in I2C (Inter-Integrated Circuit)
SDA (Serial Data): A4 
SCL (Serial Clock): A5

LCD VCC: Arduino +5V and GND of the LCD 
LCD GND: Arduino GND

10kΩ R1 between thermistor and VCC 5V
Thermistor One-leg to Arduino GND
Thermistor One-leg to Arduino A0

Calculator:
https://thinksrs.com/downloads/programs/therm%20calc/ntccalibrator/ntccalculator.html
Steinhart-Hart equation:
https://www.ametherm.com/thermistor/ntc-thermistors-steinhart-and-hart-equation
