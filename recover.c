#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");

    uint8_t buffer[512];

    int i = 0;
    char filename[8];
    sprintf(filename, "%03i.jpg", i);
    FILE *outputfile = fopen(filename, "w");

    while (fread(buffer, 1, 512, card) == 512)
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            ((buffer[3] & 0xf0) == 0xe0))
        {

            if (i == 0)
            {
                fwrite(buffer, 1, 512, outputfile);
            }
            else
            {
                fclose(outputfile);
                sprintf(filename, "%03i.jpg", i);
                outputfile = fopen(filename, "w");
                fwrite(buffer, 1, 512, outputfile);
            }
            i++;
        }
        else
        {
            if (i > 0)
            {
                fwrite(buffer, 1, 512, outputfile);
            }
        }
    }
    fclose(outputfile);
    fclose(card);
}
