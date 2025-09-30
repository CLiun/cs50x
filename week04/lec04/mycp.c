#include <cs50.h>
#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    FILE *src = fopen(argv[1], "rb");
    FILE *dst = fopen(argv[2], "wb");

    if (src == NULL)
    {
        printf("No source file.\n");
        return 1;
    }
    BYTE b;

    while (fread(&b, 1, 1, src) != 0)
    {
        fwrite(&b, 1, 1, dst);
    }

    fclose(src);
    fclose(dst);
}
