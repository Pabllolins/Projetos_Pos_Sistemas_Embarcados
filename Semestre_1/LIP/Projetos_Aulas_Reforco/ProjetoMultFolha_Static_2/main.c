#include <stdio.h>
#include "lcd.h"

unsigned int count = 5;
char txt[5];

int main(void)
{
    lcd_init();         
    lcd_write(45);
    printf("\n\n");
    return 0;
}