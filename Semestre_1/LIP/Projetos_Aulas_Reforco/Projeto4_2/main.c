#include <stdio.h>
#include <stdlib.h>

unsigned char Soma(unsigned char, unsigned char);
int Divide(int, int);

int main (void)
{
    unsigned char result;
    result = Soma (200, 56);
    printf ("%d - %d \n\n", result, Divide(100, 50));

    printf("tamanho de a: %d bits \n\n", (sizeof(200)*8)); //converte bytes em bits
    return 0;
}

unsigned char Soma(unsigned char x, unsigned char z)
{
    return x+z;
}


int Divide(int x, int z)
{
    return x/z;
}