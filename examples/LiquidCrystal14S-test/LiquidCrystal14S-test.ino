#include <LiquidCrystal14S.h>
#include <MyDisplay.h>

#define SS   6
#define RW   5
#define DATA 4

MyDisplay display(SS, RW, DATA);
LiquidCrystal14S lcd(display, 8);

void setup() {
  lcd.begin();
  lcd.print("HELLO"); // This will dispay as OLLEH.
  delay(5000);
}

void loop() {
  // Cycle through displaying only numbers
 lcd.print("00000000");
 delay(1000);
 lcd.print(11111111);
 delay(1000);
 lcd.print(22222222);
 delay(1000);
 lcd.print(33333333);
 delay(1000);
 lcd.print(44444444);
 delay(1000);
 lcd.print(55555555);
 delay(1000);
 lcd.print(66666666);
 delay(1000);
 lcd.print(77777777);
 delay(1000);
 lcd.print(88888888);
 delay(1000);
 lcd.print(99999999);
 delay(1000);

  // Cycle through each letter of the alphabet. This will write from right to left,
  // wrap around, and overwirte whats currently displayed.
  lcd.print("A");
  delay(1000);
  lcd.print("B");
  delay(1000);
  lcd.print("C");
  delay(1000);
  lcd.print("D");
  delay(1000);
  lcd.print("E");
  delay(1000);
  lcd.print("F");
  delay(1000);
  lcd.print("G");
  delay(1000);
  lcd.print("H");
  delay(1000);
  lcd.print("I");
  delay(1000);
  lcd.print("J");
  delay(1000);
  lcd.print("K");
  delay(1000);
  lcd.print("L");
  delay(1000);
  lcd.print("M");
  delay(1000);
  lcd.print("N");
  delay(1000);
  lcd.print("O");
  delay(1000);
  lcd.print("P");
  delay(1000);
  lcd.print("Q");
  delay(1000);
  lcd.print("R");
  delay(1000);
  lcd.print("S");
  delay(1000);
  lcd.print("T");
  delay(1000);
  lcd.print("U");
  delay(1000);
  lcd.print("V");
  delay(1000);
  lcd.print("W");
  delay(1000);
  lcd.print("X");
  delay(1000);
  lcd.print("Y");
  delay(1000);
  lcd.print("Z");
  delay(1000);
}
