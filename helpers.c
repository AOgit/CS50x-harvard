#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
   int avarage;
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Take average of red, green, and blue
            avarage =  round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            // Update pixel values
            image[i][j].rgbtRed = avarage;
            image[i][j].rgbtGreen = avarage;
            image[i][j].rgbtBlue = avarage;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
   int sepiaRed, sepiaGreen, sepiaBlue;
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Compute sepia values
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            // Update pixel with sepia values
            image[i][j].rgbtRed = sepiaRed > 255 ? 255 : sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen > 255 ? 255 : sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue > 255 ? 255 : sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed, sepiaGreen, sepiaBlue;
    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
             if (j == width/2 )
                break;
            // Swap pixels
            sepiaRed = image[i][j].rgbtRed;
            sepiaGreen = image[i][j].rgbtGreen;
            sepiaBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = image[i][width - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j].rgbtBlue;
            image[i][width - j].rgbtRed = sepiaRed;
            image[i][width - j].rgbtGreen = sepiaGreen;
            image[i][width - j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }

    }

    // Loop over all pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int summRed = 0;
            int summGreen= 0;
            int summBlue = 0;
            int counter = 0;
            if (i - 1 >= 0)
            {
                summRed += copy[i - 1][j].rgbtRed;
                summGreen += copy[i - 1][j].rgbtGreen;
                summBlue += copy[i - 1][j].rgbtBlue;
                counter++;
                if (j - 1 >= 0)
                {
                        summRed += copy[i - 1][j - 1].rgbtRed;
                        summGreen += copy[i - 1][j - 1].rgbtGreen;
                        summBlue += copy[i - 1][j - 1].rgbtBlue;
                        counter++;
                }
                if (j + 1 <= width)
                {

                        summRed += copy[i - 1][j + 1].rgbtRed;
                        summGreen += copy[i - 1][j + 1].rgbtGreen;
                        summBlue += copy[i - 1][j + 1].rgbtBlue;
                        counter++;
                }
            }
            if (i + 1 <= height)
            {
                summRed += copy[i + 1][j].rgbtRed;
                summGreen += copy[i + 1][j].rgbtGreen;
                summBlue += copy[i + 1][j].rgbtBlue;
                counter++;
                if (j - 1 >= 0)
                {
                        summRed += copy[i + 1][j - 1].rgbtRed;
                        summGreen += copy[i + 1][j - 1].rgbtGreen;
                        summBlue += copy[i + 1][j - 1].rgbtBlue;
                        counter++;
                }
                if (j + 1 <= width)
                {
                        summRed += copy[i + 1][j + 1].rgbtRed;
                        summGreen += copy[i + 1][j + 1].rgbtGreen;
                        summBlue += copy[i + 1][j + 1].rgbtBlue;
                        counter++;
                }
            }
            if (j - 1 >= 0)
            {
                summRed += copy[i][j - 1].rgbtRed;
                summGreen += copy[i][j - 1].rgbtGreen;
                summBlue += copy[i][j - 1].rgbtBlue;
                counter++;
            }
            if (j + 1 <= width)
            {
                summRed += copy[i][j + 1].rgbtRed;
                summGreen += copy[i][j + 1].rgbtGreen;
                summBlue += copy[i][j + 1].rgbtBlue;
                counter++;
            }
            image[i][j].rgbtRed = round((summRed + image[i][j].rgbtRed) / (counter + 1.0));
            image[i][j].rgbtGreen = round((summGreen + image[i][j].rgbtGreen) / (counter + 1.0));
            image[i][j].rgbtBlue = round((summBlue  + image[i][j].rgbtBlue)/ (counter + 1.0));
        }
    }
    return;
}
