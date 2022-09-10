#include <stdio.h>

extern unsigned int count;
extern char txt[];

unsigned char lcd_init(void)
{   
    txt[0] = 23;
    printf("lcd_init()\n");
    return 0;
}

unsigned char lcd_write(unsigned int value)
{
    printf("lcd_write(%d)\n", value);
    return 0;
}
