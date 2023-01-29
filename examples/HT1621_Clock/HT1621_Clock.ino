/*
 * File    - HT1621_Clock
 * Brief   - Simple clock usuing HT1621 library.
 * Author  - Enrico Formenti (Original post https://macduino.blogspot.com/2017/12/pdc1211-simple-clock-sketch.html)
 *         - Justdienow
 * Date    - 23 Jan 2023
 * Version - 1.0
 */

#include <LiquidCrystal14S.h>
#include <MyDisplay.h>

#define SS 6
#define RW 5
#define DATA 4

MyDisplay display(SS, RW, DATA);
LiquidCrystal14S lcd(display, 8);

/*
 * Not the best way to do this, but this is because of how this library writes to the 
 * display (from RIGHT to LEFT) - or is it the display layout/wiring (thinking)?
 * So, to get around this, I created arrays that have numbers in reverse so that when
 * they are printed to the display, they are printed in the correct order (just realised
 * these arrays are not needed). I could change the underlying libaray to print chars 
 * from left to right, or convert the numbers to a string and use strrev() 
 * instead -- IDK, I'm no SW eng ¯\_(ツ)_/¯.
 */

const char * secarr[] = {
    "00", "10", "20", "30", "40", "50", "60", "70", "80", "90", // 00 - 09
    "01", "11", "21", "31", "41", "51", "61", "71", "81", "91", // 10 - 19
    "02", "12", "22", "32", "42", "52", "62", "72", "82", "92", // 20 - 29
    "03", "13", "23", "33", "43", "53", "63", "73", "83", "93", // 30 - 39
    "04", "14", "24", "34", "44", "54", "64", "74", "84", "94", // 40 - 49
    "05", "15", "25", "35", "45", "55", "65", "75", "85", "95"  // 50 - 59
};

const char * minarr[] = {
    "00", "10", "20", "30", "40", "50", "60", "70", "80", "90", // 00 - 09
    "01", "11", "21", "31", "41", "51", "61", "71", "81", "91", // 10 - 19
    "02", "12", "22", "32", "42", "52", "62", "72", "82", "92", // 20 - 29
    "03", "13", "23", "33", "43", "53", "63", "73", "83", "93", // 30 - 39
    "04", "14", "24", "34", "44", "54", "64", "74", "84", "94", // 40 - 49
    "05", "15", "25", "35", "45", "55", "65", "75", "85", "95"  // 50 - 59
};

const char * hr12arr[] = {
    "10", "20", "30", "40", "50", "60", "70", "80", "90",       // 01 - 09
    "01", "11", "21"                                            // 10 - 12
};

const char * hr24arr[] = {
    "00", "10", "20", "30", "40", "50", "60", "70", "80", "90", // 00 - 09
    "01", "11", "21", "31", "41", "51", "61", "71", "81", "91", // 10 - 19
    "02", "12", "22", "32"                                      // 20 - 23
};

char timestr[8] = {'0', '0', '|', '5', '1', '|', '0', '2'};

uint8_t seconds = 00;
uint8_t minutes = 15;
uint8_t hours = 20;

bool Blink = false;
uint16_t compensation = 0;


void setup() {
    lcd.begin();
}

void loop() {
    delay(500);
    if(Blink) {
        timestr[2] = ' ';
        timestr[5] = ' ';
        lcd.print(timestr);
    }
    else
    {
        lcd.home();
        ++seconds;

        if(seconds==60) {
            seconds = 0;
            ++minutes;
        }

        if(minutes==60) {
            minutes = 0;
            ++hours;
        }

        if(hours == 24) {
            hours=0;
        }

        timestr[0] = secarr[seconds][0];
        timestr[1] = secarr[seconds][1];
        timestr[2] = '|';
        timestr[3] = minarr[minutes][0];
        timestr[4] = minarr[minutes][1];
        timestr[5] = '|';
        timestr[6] = hr24arr[hours][0];
        timestr[7] = hr24arr[hours][1];
        lcd.print(timestr);
    }
    Blink ^= true;
}
