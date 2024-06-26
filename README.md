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


![image](https://github.com/saidijongo/LCD_NTC_Thermistor_DIP/assets/31678025/c8d6bd64-d444-4b0c-8b4b-01770fd0549e)


![image](https://github.com/saidijongo/LCD_NTC_Thermistor_DIP/assets/31678025/d67c196c-5d48-4d1c-b64d-c8e6904af965)

![image](https://github.com/saidijongo/LCD_NTC_Thermistor_DIP/assets/31678025/fda1ea7c-6ae0-481d-9748-03b63f463947)


STM32 16x2 LCD lm016l
https://deepbluembedded.com/stm32-lcd-16x2-tutorial-library-alphanumeric-lcd-16x2-interfacing/



