// danger Test

#include <LCD_ST7032.h>
#include "SparkFun_SCD30_Arduino_Library.h"
#include <Wire.h>


LCD_ST7032 lcd;
SCD30 airSensor;


int LEDblau = 11; // Farbe blau an Pin
int LEDrot = 9; // Farbe rot an Pin
int LEDgruen = 10; // Farbe gruen an Pin

void setup()
{
  pinMode(LEDblau, OUTPUT);
  pinMode(LEDgruen, OUTPUT);
  pinMode(LEDrot, OUTPUT);

  lcd.begin();
  lcd.setcontrast(25);
  lcd.setCursor(0, 0);
  lcd.print("LCD-Test");
  delay(100);

  if (airSensor.begin() == false)
  {
    lcd.setCursor(0, 0);
    lcd.print("Error SCD30");
    while (1)
      ;
  }

}

void showColor(int r, int g, int b) {

  analogWrite(LEDrot, r);
  analogWrite(LEDgruen, g);
  analogWrite(LEDblau, b);
}

void showDanger(float danger) {
  // 255   0   0   -> 1.0
  // 255 255   0   -> 0.5
  //   0 255   0   -> 0.0

  int red, green, blue;

  blue = 0;
  red = 255 * danger;
  green = 255 * (1 - danger);

  showColor(red, green, blue);
}

void printDanger(float danger) {
  //lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(danger, 3);
}

  bool temp = true;


void loop()
{

lcd.clear();

  if (airSensor.dataAvailable()) {

    int co2 = airSensor.getCO2(); //Cut off decimal as co2 is 0 to 10,000
    float humidity = airSensor.getHumidity();
    float temperature = airSensor.getTemperature();

    float danger;

    lcd.setCursor(0, 0);
    lcd.print("co2(ppm):");
    lcd.print(co2);
    lcd.setCursor(1, 0);
    if (temp) {
      lcd.print("temp(C):");
      lcd.print(temperature, 1);
      temp = false;
    }
    else {
      lcd.print("humi(%):");
      lcd.print(humidity, 1);
      temp = true;
    }

    if (co2 < 500 && co2 >= 0)
    {
      danger = 0.0;
    }
    else if( co2 < 2000 && co2 >= 0)
    {
      danger = (co2 - 500) / 1500.;
    }
    else 
    {
      danger = 1.0;
    }

    showDanger(danger);
  }
  delay(3000);


}
