#include <stdio.h>

int get_endianness(void)
{
    int num = 1;
    char *endian = (char *)&num;
    return (*endian == 1);
}
