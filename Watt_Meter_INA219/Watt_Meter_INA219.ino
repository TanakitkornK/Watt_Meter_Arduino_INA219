#include <SPI.h>
#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

Adafruit_INA219 ina219;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
  Serial.begin(9600);
  delay(1000);

  if (!ina219.begin()) {
    Serial.println("Failed to find INA219 chip");
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("INA219 Power Monitor");
    display.setTextSize(2);
    display.println("Can't find");
    display.setTextSize(1);
    display.println("      INA 219");
    display.display();
    while (1) { delay(10); }
  }
}

void loop() {
  float busvoltage_V = ina219.getBusVoltage_V();
  float current_mA = ina219.getCurrent_mA();
  float power_mW = ina219.getPower_mW();

  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("INA219 Power Monitor");
  
  display.setTextSize(1);
  display.print("Vol [V]: ");
  display.println(busvoltage_V,3);

  display.setTextSize(1);
  display.print("Amp [m.A]: ");
  display.println(current_mA,3);
  
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.print("Pwr [m.W]: ");
  display.println(power_mW,3);
  display.display();
  delay(50);
}
