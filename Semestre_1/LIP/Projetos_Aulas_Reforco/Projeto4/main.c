#include <stdio.h>
#include <stdlib.h>

char a;
char b;
int c;

unsigned char Soma(unsigned char, unsigned char);

int main (void)
{
    a = 200;
    b = 55;
    c = 0;
    unsigned char result; //0 a 255
    result = Soma (a, b);
    printf ("%d \n", result);

    printf("tamanho de a: %d bits \n\n", (sizeof(a)*8)); //converte bytes em bits
    return 0;
}

unsigned char Soma(unsigned char x, unsigned char z)
{
    return x + z;
}