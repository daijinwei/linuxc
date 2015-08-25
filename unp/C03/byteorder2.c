#include <stdio.h>

// Judge big endian or Litel endian
int main()
{
    int s = 0x5102;
    if ((0x02  == ((char *)&s)[0]) && (0x51 == ((char *)&s )[1])) {
        printf("Litle endian\n"); 
    } else if ((0x51  == ((char *)&s)[0]) && (0x02 == ((char *)&s)[1])) {
        printf("Big endian\n"); 
    }else{
        printf("Unkown\n"); 
    }
    return 0;
}
