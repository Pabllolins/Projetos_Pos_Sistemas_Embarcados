#include <stdio.h>
#include <stdlib.h>


unsigned int Soma();

int main (void)
{
    printf("%d\n", Soma());
    printf("%d\n", Soma());
    printf("%d\n", Soma());
    printf("\n");
    return 0;
}

unsigned int Soma(void)
{
    /*
    PRBSL - 07/09/2022 -Quando definimos com a classe static, a variavel é 
    inicializada no setor .data da memoria RAM.
    Se invocada novamente dentro da mesma função principal, ela não será 
    criada novamente, pois ja foi inicializada e existe na região .bss
    */
    static unsigned char t = 0; 
    t++;
    t++;

    return t;
}
