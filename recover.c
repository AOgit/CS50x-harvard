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

    while (fread(buffer, 1, 512, card) == 512)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff  && ((buffer[3] & 0xf0) == 0xe0)  )
        {
            char filename[8];
            sprintf(filename, "%03i.jpg", i);
            FILE *outputfile = fopen(filename, "w");
            fwrite(buffer, 1, 512, outputfile);
            // printf("%s foto writed\n", filensame);
            fclose(outputfile);
            i++;
        }
    }
    fclose(card);
}
