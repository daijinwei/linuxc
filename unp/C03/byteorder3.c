#include <stdio.h>

// Judge big endian or Litel endian
int main()
{
    // s, c share memory
    union {
        short s;
        char c[sizeof(short)];
    } un;       

    un.s = 0x5102;
    if ((0x02  == un.c[0]) && (0x51 == un.c[1])) {
        printf("Litle endian\n"); 
    } else if ((0x51  == un.c[0]) && (0x01 == un.c[1])) {
        printf("Big endian\n"); 
    }else{
        printf("Unkown\n"); 
    }
    return 0;
}
