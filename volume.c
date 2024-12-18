// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    uint8_t *header;

    header = malloc(HEADER_SIZE * sizeof(uint8_t));

    if (header == NULL)
    {
        printf("Fragmentation error\n");
        return 1;
    }

    // Copy header from input file to output file
    fread(header, HEADER_SIZE, sizeof(uint8_t), input);
    fwrite(header, HEADER_SIZE, sizeof(uint8_t), output);
    free(header);

    // Read samples from input file and write updated data to output file
    int16_t buffer;
    while (fread(&buffer, 1, sizeof(int16_t), input) != 0)
    {
        // Update volume of sample
        buffer *= factor;
        fwrite(&buffer, 1, sizeof(int16_t), output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
