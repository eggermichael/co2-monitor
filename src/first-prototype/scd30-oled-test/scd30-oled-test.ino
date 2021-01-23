// scd30 oled Test

#include <LCD_ST7032.h>
#include "SparkFun_SCD30_Arduino_Library.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

LCD_ST7032 lcd;
SCD30 airSensor;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


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
  lcd.setCursor(0, 0);
  lcd.print("SCD30 OK");
  delay(1000);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))   {
    lcd.setCursor(0, 0);
    lcd.print("Error OLED");
    while (1)
      ;
  }
  lcd.setCursor(0, 0);
  lcd.print("OLED OK");
  delay(1000);

  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Hello");
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("World!");
  display.display();
  delay(2000);
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

  if (airSensor.dataAvailable()) {

    int co2 = airSensor.getCO2(); //Cut off decimal as co2 is 0 to 10,000
    float humidity = airSensor.getHumidity();
    float temperature = airSensor.getTemperature();

    float danger;

    lcd.clear();
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

    delay(100);

    if (co2 < 500 && co2 >= 0)
    {
      danger = 0.0;
    }
    else if ( co2 < 2000 && co2 >= 0)
    {
      danger = (co2 - 500) / 1500.;
    }
    else
    {
      danger = 1.0;
    }

    showDanger(danger);

    delay(100);
    
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("co2(ppm):");
    display.println(co2);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println("temp(C):");
    display.println(temperature);
    display.println("humidity(%):");
    display.println(humidity);
    display.display();

    delay(100);

  }
  delay(5000);


}
