#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // Compute average
            float avg =
                (image[row][col].rgbtBlue + image[row][col].rgbtGreen + image[row][col].rgbtRed) /
                3.0;

            // Update pixel values
            image[row][col].rgbtBlue = round(avg);
            image[row][col].rgbtGreen = round(avg);
            image[row][col].rgbtRed = round(avg);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // Compute sepia value
            float sepiaRed = .393 * image[row][col].rgbtRed + .769 * image[row][col].rgbtGreen +
                             .189 * image[row][col].rgbtBlue;
            float sepiaGreen = .349 * image[row][col].rgbtRed + .686 * image[row][col].rgbtGreen +
                               .168 * image[row][col].rgbtBlue;
            float sepiaBlue = .272 * image[row][col].rgbtRed + .534 * image[row][col].rgbtGreen +
                              .131 * image[row][col].rgbtBlue;
            // Update pixel value
            int temp = round(sepiaRed);
            image[row][col].rgbtRed = (temp < 255) ? temp : 255;
            temp = round(sepiaGreen);
            image[row][col].rgbtGreen = (temp < 255) ? temp : 255;
            temp = round(sepiaBlue);
            image[row][col].rgbtBlue = (temp < 255) ? temp : 255;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int left = 0, right = width - 1; left < right; left++, right--)
        {
            RGBTRIPLE tmp = image[row][left];
            image[row][left] = image[row][right];
            image[row][right] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Back up origin image
    RGBTRIPLE copy[height][width];
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            copy[row][col] = image[row][col];
        }
    }

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // Compute blur value, notice edge case
            int count = 0;
            float tmpR = 0, tmpG = 0, tmpB = 0;
            for (int i = -1; i < 2; i++)
            {
                // Top or buttom row case
                if (row + i < 0 || row + i > height - 1)
                {
                    continue;
                }
                for (int j = -1; j < 2; j++)
                {
                    // Left or right column case
                    if (col + j < 0 || col + j > width - 1)
                    {
                        continue;
                    }

                    count++;
                    tmpR += copy[row + i][col + j].rgbtRed;
                    tmpG += copy[row + i][col + j].rgbtGreen;
                    tmpB += copy[row + i][col + j].rgbtBlue;
                }
            }
            image[row][col].rgbtRed = round(tmpR / count);
            image[row][col].rgbtGreen = round(tmpG / count);
            image[row][col].rgbtBlue = round(tmpB / count);
        }
    }

    return;
}
