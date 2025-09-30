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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Gx Gy for calculation
    int Gx_kernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy_kernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    // Copy the original image array
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }
    // Compute Gx, Gy for each RGB channel
    // Compute new value for RGB channel in image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gxR = 0, gyR = 0, tmpR = 0;
            int gxG = 0, gyG = 0, tmpG = 0;
            int gxB = 0, gyB = 0, tmpB = 0;

            // Calculate weighted sum for 3x3 matrix
            // Weight out of image = 0, act as continue
            for (int row = -1; row < 2; row++)
            {
                if (i + row < 0 || i + row > height - 1)
                {
                    continue;
                }
                for (int col = -1; col < 2; col++)
                {
                    if (j + col < 0 || j + col > width - 1)
                    {
                        continue;
                    }
                    // Update each channel for each pixel
                    gxR += copy[i + row][j + col].rgbtRed * Gx_kernel[row + 1][col + 1];
                    gyR += copy[i + row][j + col].rgbtRed * Gy_kernel[row + 1][col + 1];

                    gxG += copy[i + row][j + col].rgbtGreen * Gx_kernel[row + 1][col + 1];
                    gyG += copy[i + row][j + col].rgbtGreen * Gy_kernel[row + 1][col + 1];

                    gxB += copy[i + row][j + col].rgbtBlue * Gx_kernel[row + 1][col + 1];
                    gyB += copy[i + row][j + col].rgbtBlue * Gy_kernel[row + 1][col + 1];
                }
            }
            tmpR = round(sqrt(pow(gxR, 2) + pow(gyR, 2)));
            image[i][j].rgbtRed = (tmpR < 255) ? tmpR : 255;

            tmpG = round(sqrt(pow(gxG, 2) + pow(gyG, 2)));
            image[i][j].rgbtGreen = (tmpG < 255) ? tmpG : 255;

            tmpB = round(sqrt(pow(gxB, 2) + pow(gyB, 2)));
            image[i][j].rgbtBlue = (tmpB < 255) ? tmpB : 255;
        }
    }

    return;
}
