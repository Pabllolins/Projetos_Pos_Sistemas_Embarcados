#include <stdio.h>
#include "lcd.h"

unsigned int count = 2;
char txt[2];

int main(void)
{
    lcd_init();         
    lcd_write(45);
    printf("\n\n");
    return 0;
}