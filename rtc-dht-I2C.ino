/*
   Libraries: LiquidCrystal_I2C; RTClib; DHT
   Connections are shown in the Fritzing (.fzz) or PNG file
   
   Made with <3 by u/Galatony0311
   For any question, DM me on Reddit
*/

#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include <DHT.h>


#define dhtp 8
#define dhtt DHT11 //for this project I'll use a DHT11

RTC_DS3231 rtc;
LiquidCrystal_I2C lcd(0x27, 20, 4); //my LCD has a I2C module and it's 20x4
DHT dht(dhtp, dhtt);

void setup () {
  rtc.begin();
  dht.begin();
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("---Weather Station---");
  lcd.setCursor(0, 3);
  lcd.print("---------------------");
}


void loop () {
  DateTime now = rtc.now();
  printDateTime(now);
  delay(1000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  lcd.setCursor(1, 2);
  lcd.print(t);
  lcd.setCursor(6, 2);
  lcd.print("C");

  lcd.setCursor(13, 2);
  lcd.print(h);
  lcd.setCursor(18, 2);
  lcd.print("%");
}

void printDateTime(DateTime dt) {
  char dateBuffer[] = "DD/MM/YY";
  char timeBuffer[] = "  hh:mm:ss";

  lcd.setCursor(0, 1);
  lcd.print(dt.toString(dateBuffer));
  lcd.setCursor(10, 1);
  lcd.print(dt.toString(timeBuffer));

}
