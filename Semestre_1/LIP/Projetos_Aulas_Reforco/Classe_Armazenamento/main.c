#include <stdio.h>
#include <stdlib.h>


unsigned int Soma(unsigned char, unsigned char);

int main (void)
{
    unsigned int result;
    result = Soma (200, 56);
    result = Soma (200, 56);
    result = Soma (200, 56);
    printf ("%d\n\n", result);
    return 0;
}

unsigned int Soma(unsigned char x, unsigned char z)
{
    static unsigned char t = 0;
    t++;
    t++;

    return x+z+t;
}
