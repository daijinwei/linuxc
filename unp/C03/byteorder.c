#include <stdio.h>

// Judge big-endian or little-endian
int main()
{
    int s = 0x5102;
    if ((0x02 == (*((char *)&s))) && (0x51 == (*((char *)&s + 1)))) {
        printf("little-endian\n"); 
    } else if (0x51 == (*((char *)&s)) && (0x02 == (*((char *)&s + 1)))) {
        printf("big-endian\n"); 
    }else{
        printf("Unkown\n"); 
    }
    return 0;
}
