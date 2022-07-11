#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>


#define NUMBER_LINES 2u
#define NUMBER_CHARACTERS 16u
#define ADDRESS_SCREEN 0x27
//lcd.setCursor(Character:1,Line:0)

LiquidCrystal_I2C lcd(0x27, NUMBER_CHARACTERS,NUMBER_LINES);

extern void screen_setup(void)
{
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0);
}


extern void print_screen(uint8_t *  msg, uint8_t line)
{
  assert(msg<(NUMBER_CHARACTERS-1u));
  assert(line<(NUMBER_LINES-1u));

  lcd.setCursor(1,line);
  lcd.print (msg);
}





