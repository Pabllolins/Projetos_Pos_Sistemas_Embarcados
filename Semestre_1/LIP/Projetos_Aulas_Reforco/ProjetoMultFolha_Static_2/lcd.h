#ifndef __LCD_H__
#define __LCD_H__

    #ifdef __cplusplus
        extern "C" {
    #endif

    unsigned char lcd_init(void);
    unsigned char lcd_write(unsigned int value);

    #ifdef __cplusplus
        }
    #endif

#endif