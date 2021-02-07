// scd30 oled Test

#include "SparkFun_SCD30_Arduino_Library.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

SCD30 airSensor;

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup()
{
  // initialize sdc30
  if (airSensor.begin() == false)
  {
    while (1)
      ;
  }
  delay(1000);

  // initialize oled
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))   {
    while (1)
      ;
  }
  delay(1000);

  display.display();
  //delay(2000); // Pause for 2 seconds
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("CO2-\nMonitor");
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("starting...");
  display.display();
  delay(2000);
}




int dataLen = 60;
int data [60];

void showData(int co2ppm, float temperature, float humidity) {

  // add new measurement to data buffer and remove oldest entry
  for (int di = 0; di < dataLen - 1; di++)
  {
    data[di] = data[di + 1];
  }
  data[dataLen - 1] = co2ppm;

  // print text for CO2 measurement
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.setTextSize(1);
  display.setTextSize(4);
  display.setCursor(0, 0);
  display.print(co2ppm);
  display.setTextSize(1);
  display.setCursor(110, 10);
  display.print("ppm");

  // print text for temperature and humidity measurements
  display.setTextSize(1);
  display.setCursor(0, 56);
  display.print(temperature, 1);
  display.setTextSize(1);
  display.print("C           ");
  display.setTextSize(1);
  display.print(humidity, 1);
  display.setTextSize(1);
  display.print("%");

  // find maximum and minimum CO2 values in data buffer
  float minData = 32767;
  float maxData = -32768;
  int len = sizeof(data) / sizeof(data[0]);
  for (int i = 0; i < len; i++) {
    if (data[i] > maxData) maxData = data[i];
    if (data[i] < minData) minData = data[i];
  }

  // print text for maximum and minimum values of CO2
  display.setTextSize(1);
  display.setCursor(100, 20);
  display.print(minData, 0);
  display.setTextSize(1);
  display.setCursor(100, 0);
  display.print(maxData, 0);

  // calculate stepsize for chart
  float xStep = float(display.width()) / float(len);

  // draw a line from the previous data point to the current data point for all data points
  int previousY = 48 - ((data[0] - minData) / (maxData - minData)) * 16;
  int previousX = 5;
  for (int i = 0; i < len; i++) {
    int x = xStep * i;
    int y = ((data[i] - minData) / (maxData - minData)) * 16; //
    display.drawCircle(x + 5, 48 - y , 2, SSD1306_WHITE);
    display.drawLine(previousX, previousY, x + 5, 48 - y, SSD1306_WHITE);
    previousX = x + 5;
    previousY = 48 - y;
  }

  // oled display
  display.display();
  delay(100);
}

int tick;
void loop()
{
  // wait for new data available
  if (airSensor.dataAvailable()) {

    // acquire and show data
    int co2 = airSensor.getCO2(); //Cut off decimal as co2 is 0 to 10,000
    float humidity = airSensor.getHumidity();
    float temperature = airSensor.getTemperature();
    showData(co2, temperature, humidity);

    // print screen refresh rate in seconds. when data buffer length is 60, this is also the time shown in the graph in minutes.
    int tock = millis();
    display.setCursor(50, 57);
    display.setTextSize(1);
    display.println((tock - tick) / 1000., 3);
    display.display();
    tick = tock;
    
    delay(2700);
  }
  delay(100);
}
