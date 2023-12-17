#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int y = 0; y < width; y++)
        {
            float blue = image[i][y].rgbtBlue;
            float green = image[i][y].rgbtGreen;
            float red = image[i][y].rgbtRed;
            float result = (blue + green + red) / 3.0;
            image[i][y].rgbtBlue = round(result);
            image[i][y].rgbtGreen = round(result);
            image[i][y].rgbtRed = round(result);
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int y = 0; y < width; y++)
        {
            float blue = image[i][y].rgbtBlue;
            float green = image[i][y].rgbtGreen;
            float red = image[i][y].rgbtRed;
            float sepiaRed = .393 * red + .769 * green + .189 * blue;
            float sepiaGreen = .349 * red + .686 * green + .168 * blue;
            float sepiaBlue = .272 * red + .534 * green + .131 * blue;
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][y].rgbtBlue = round(sepiaBlue);
            image[i][y].rgbtGreen = round(sepiaGreen);
            image[i][y].rgbtRed = round(sepiaRed);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int y = 0; y < width / 2; y++)
        {
            RGBTRIPLE temp = image[i][y];
            image[i][y] = image[i][width - 1 - y];
            image[i][width - 1 - y] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Allocate memory for new_image
    RGBTRIPLE **new_image = (RGBTRIPLE **) malloc(sizeof(RGBTRIPLE *) * height);
    for (int i = 0; i < height; i++)
    {
        new_image[i] = (RGBTRIPLE *) malloc(sizeof(RGBTRIPLE) * width);
    }

    // Iterate through each pixel in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            int count = 0;

            // Iterate through the surrounding pixels
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;
                    // Check if the surrounding pixel is within bounds
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        sumRed += image[ni][nj].rgbtRed;
                        sumGreen += image[ni][nj].rgbtGreen;
                        sumBlue += image[ni][nj].rgbtBlue;
                        count++;
                    }
                }
            }

            // Calculate the average values
            new_image[i][j].rgbtRed = round((float) sumRed / count);
            new_image[i][j].rgbtGreen = round((float) sumGreen / count);
            new_image[i][j].rgbtBlue = round((float) sumBlue / count);
        }
    }

    // Copy the blurred image back to the original image array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }

    // Free allocated memory for new_image
    for (int i = 0; i < height; i++)
    {
        free(new_image[i]);
    }
    free(new_image);

    return;
}
