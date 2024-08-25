
#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#define OLED_ADDRESS 0x3C
#define OLED_RESET -1
Adafruit_SSD1306 display(OLED_RESET);
int RX = 0, TX = 1;
TinyGPSPlus gps;
SoftwareSerial gpssoft(RX, TX);
void setup()
{
 Serial.begin(9600);
 gpssoft.begin(9600);
 display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
 display.clearDisplay();
 display.display();
}
void loop()
{
 Serial.print("working");
 display.clearDisplay();
 display.setTextSize(1);
 display.setTextColor(WHITE);
 display.setCursor(35, 5);
 display.print("SPEED(KMPH)");
 display.display();
while (gpssoft.available() > 0)
 if (gps.encode(gpssoft.read()))
 displayspeed();
 if (millis() > 5000 && gps.charsProcessed() < 10)
 {
 display.setTextSize(1);
 display.setCursor(35, 20);
 display.print("Error!!!");
 display.display();
 Serial.print("Error!!!");
 }
}
void displayspeed()
{
 if (gps.speed.isValid())
 {
 display.setTextSize(1);
 display.setCursor(35, 15);
 display.print(gps.speed.kmph());
 display.display();
 
 if(gps.speed.kmph()>5.0)
 {
 display.setTextSize(1);
 display.setCursor(35, 25);
 display.print("Over speeding!!!");display.display();
}
Serial.print("working");
 }
 else
 {
 display.setTextSize(1);
 display.setCursor(35, 20);
 display.print("No Data!!!");
 display.display();
 Serial.print("No Data!!!"); 
 }
 delay(100);
}
