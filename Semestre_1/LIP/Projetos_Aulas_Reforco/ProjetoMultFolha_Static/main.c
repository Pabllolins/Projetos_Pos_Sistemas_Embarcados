#include "sys.h"
#include "lcd.h"
#include "calc.h"

int main (void)
{
    Soma();
    lcd_init();         
    lcd_write(45);
    printf("Count = %d", lcd_read_count());
    
    return 0;
}