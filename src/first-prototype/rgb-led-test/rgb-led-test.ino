// RGB LED Test

int LEDblau = 11; // Farbe blau an Pin
int LEDrot = 9; // Farbe rot an Pin
int LEDgruen = 10; // Farbe gruen an Pin

void setup()
{
  pinMode(LEDblau, OUTPUT);
  pinMode(LEDgruen, OUTPUT);
  pinMode(LEDrot, OUTPUT);
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

void testRGB() {
  // aus
  analogWrite(LEDblau, 0);
  analogWrite(LEDrot, 0);
  analogWrite(LEDgruen, 0);
  delay(500); // pause

  // rot
  analogWrite(LEDblau, 0);
  analogWrite(LEDrot, 150);
  analogWrite(LEDgruen, 0);
  delay(500); // pause

  // gruen
  analogWrite(LEDblau, 0);
  analogWrite(LEDrot, 0);
  analogWrite(LEDgruen, 150);
  delay(500); // pause

  // blau
  analogWrite(LEDblau, 150);
  analogWrite(LEDrot, 0);
  analogWrite(LEDgruen, 0);
  delay(500); // pause
}

void testRGB2() {
  // aus
  showColor(0, 0, 0);
  delay(500); // pause

  // rot
  showColor(200, 0, 0);
  delay(500); // pause

  // gruen
  showColor(0, 200, 0);
  delay(500); // pause

  // blau
  showColor(0, 0, 200);
  delay(500); // pause
}

void loop()
{
  for ( int i = 0; i < 100; i++)
  {
    float danger = 0;
    danger = i / 100.;
    showDanger(danger);
    delay(10);
  }
  for ( int i = 0; i < 1000; i++)
  {
    float danger = 0;
    danger = i / 1000.;
    showDanger(danger);
    delay(10);
  }
}
