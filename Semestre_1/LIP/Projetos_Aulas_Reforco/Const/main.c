#include <stdio.h>
#include <stdlib.h>

//#define PI 3.1415;
const float PI = 3.1415;

void print(const char * txt)
{
    while (*txt != 0)
    {
        printf("%c", txt++);
    }
    
}

int main(void)
{   
    //const char * const pot = "HELLO";
    //*pot = 'A';

    char pot[6] = "HELLO";
    //pot[0] = 'A';

    //printf("%s", pot);

    print(pot);

    printf("\n\n");
    return 0;
}