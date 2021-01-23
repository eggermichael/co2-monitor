// danger Test

#include <LCD_ST7032.h>

LCD_ST7032 lcd;

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

void loop()
{

  lcd.clear();
  for ( int i = 0; i < 100; i++)
  {
    float danger = 0;
    danger = i / 100.;
    showDanger(danger);
    printDanger(danger);
    delay(10);
  }
  
  lcd.clear();
  for ( int i = 0; i < 1000; i++)
  {
    float danger = 0;
    danger = i / 1000.;
    showDanger(danger);
    printDanger(danger);
    delay(10);
  }
}
