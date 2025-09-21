#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup()
{
  lcd.begin(16,2);
}

void loop()
{
  lcd.setCursor(2,0);
  lcd.print("Pozdrav");
  delay(1000);

  lcd.setCursor(6,1);
  lcd.print("Svima :)");
  delay(1000);

  lcd.clear();
  delay(500);


}
