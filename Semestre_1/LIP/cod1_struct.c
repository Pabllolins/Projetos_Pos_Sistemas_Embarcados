

#include <stdio.h>
#include <stdlib.h>

#pragma pack(1)

// struct _serial
// {
//     int baudrate;
//     char *ComPort[10];
//     /* data */
// };
// typedef struct _serial Serial_t

typedef struct _serial
{
    int baudrate;
    char ComPort[10];
}Serial_t;


void print(Serial_t * Serial){
    //printf("%d", (*Serial).baudrate);
    printf("%d\n\n", Serial->baudrate);
}

int main(int argc, char *argv[]){
    Serial_t Serial = 
    {
        .ComPort = "COM3",
        .baudrate = 9600,   
    };
    //printf("%d", sizeof(Serial));

    print(&Serial);
}