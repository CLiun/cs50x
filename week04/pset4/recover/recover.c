#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

const int BLOCKSIZE = 512;
int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: %s filename.raw\n", argv[0]);
        return 1;
    }
    // Open the file
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Cannot open file.\n");
        return 1;
    }
    FILE *new_jpg = NULL;
    // Read file 512B one time until end
    BYTE buffer[BLOCKSIZE] = {};
    int count = 0;
    char name_jpg[8];
    while (fread(buffer, 1, BLOCKSIZE, card) == 512)
    {
        // Start new .jpg, when meeting signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            if (count == 0)
            {
                new_jpg = fopen("000.jpg", "w");
                fwrite(buffer, 1, BLOCKSIZE, new_jpg);
                count++;
            }
            else
            {
                fclose(new_jpg);
                sprintf(name_jpg, "%03i.jpg", count);
                new_jpg = fopen(name_jpg, "w");
                if (new_jpg == NULL)
                {
                    fclose(card);
                    return 1;
                }
                fwrite(buffer, 1, BLOCKSIZE, new_jpg);
                count++;
            }
        }
        // Copy to .jpg until next signature
        else
        {
            if (count)
                fwrite(buffer, 1, BLOCKSIZE, new_jpg);
        }
    }
    fclose(card);
    fclose(new_jpg);
}
