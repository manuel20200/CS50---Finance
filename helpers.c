#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = (image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3;
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            char temp = 0;
            temp = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][width - 1 - j].rgbtRed = temp;
            temp = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][width - 1 - j].rgbtBlue = temp;
            temp = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][width - 1 - j].rgbtGreen = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = 0;
            //blur no borders pixels
            if (i > 0 && j > 0 && i < (height - 2) && j < (width - 2))
            {
            avg = (image[i - 1][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i + 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / 9;
            image[i][j].rgbtRed = avg;
            avg = (image[i - 1][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 9;
            image[i][j].rgbtBlue = avg;
            avg = (image[i - 1][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 9;
            image[i][j].rgbtGreen = avg;
            }
            // top left corner
            else if (i == 0 && j == 0)
            {
                avg = (image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed) / 4;
                image[i][j].rgbtRed = avg;
                avg = (image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 4;
                image[i][j].rgbtBlue = avg;
                avg = (image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 4;
                image[i][j].rgbtGreen = avg;
            }
            // top right corner
            else if (i == 0 && j == (width - 1))
            {
                avg = (image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / 4;
                image[i][j].rgbtRed = avg;
                avg = (image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 4;
                image[i][j].rgbtBlue = avg;
                avg = (image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 4;
                image[i][j].rgbtGreen = avg;
            }
            // bottom left corner
            else if (i == (height - 1) && j == 0)
            {
                avg = (image[i][j].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j].rgbtRed) / 4;
                image[i][j].rgbtRed = avg;
                avg = (image[i][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j].rgbtBlue) / 4;
                image[i][j].rgbtBlue = avg;
                avg = (image[i][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j].rgbtGreen) / 4;
                image[i][j].rgbtGreen = avg;
            }
            // botton right corner
            else if (i == (height - 1) && j == (width - 1))
            {
                avg = (image[i][j].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j].rgbtRed) / 4;
                image[i][j].rgbtRed = avg;
                avg = (image[i][j].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue) / 4;
                image[i][j].rgbtBlue = avg;
                avg = (image[i][j].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen) / 4;
                image[i][j].rgbtGreen = avg;
            }
            // left side
            else if (j == 0 && i != 0 && i != (height - 1))
            {
                avg = (image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 6;
                image[i][j].rgbtRed = avg;
                avg = (image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 6;
                image[i][j].rgbtBlue = avg;
                avg = (image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 6;
                image[i][j].rgbtGreen = avg;
            }
            // right side
            else if (j == (width - 1) && i != 0 && i != (height - 1))
            {
                avg = (image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6;
                image[i][j].rgbtRed = avg;
                avg = (image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6;
                image[i][j].rgbtBlue = avg;
                avg = (image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6;
                image[i][j].rgbtGreen = avg;
            }
            // upper side
            else if (i == 0 && j != 0 && j != (width - 1))
            {
                avg = (image[i][j].rgbtRed + image[i + 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i + 1][j + 1].rgbtRed + image[i + 1][j - 1].rgbtRed) / 6;
                image[i][j].rgbtRed = avg;
                avg = (image[i][j].rgbtBlue + image[i + 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue + image[i + 1][j - 1].rgbtBlue) / 6;
                image[i][j].rgbtBlue = avg;
                avg = (image[i][j].rgbtGreen + image[i + 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen + image[i + 1][j - 1].rgbtGreen) / 6;
                image[i][j].rgbtGreen = avg;
            }
            // lower side
            else if (i == (height - 1) && j != 0 && j != (width - 1))
            {
                avg = (image[i][j].rgbtRed + image[i - 1][j].rgbtRed + image[i][j + 1].rgbtRed + image[i][j - 1].rgbtRed + image[i - 1][j + 1].rgbtRed + image[i - 1][j - 1].rgbtRed) / 6;
                image[i][j].rgbtRed = avg;
                avg = (image[i][j].rgbtBlue + image[i - 1][j].rgbtBlue + image[i][j + 1].rgbtBlue + image[i][j - 1].rgbtBlue + image[i - 1][j + 1].rgbtBlue + image[i - 1][j - 1].rgbtBlue) / 6;
                image[i][j].rgbtBlue = avg;
                avg = (image[i][j].rgbtGreen + image[i - 1][j].rgbtGreen + image[i][j + 1].rgbtGreen + image[i][j - 1].rgbtGreen + image[i - 1][j + 1].rgbtGreen + image[i - 1][j - 1].rgbtGreen) / 6;
                image[i][j].rgbtGreen = avg;
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3] = {{-1, 0, 1},
                    {-2, 0, 2},
                    {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1},
                    {0, 0, 0},
                    {1, 2, 1}};
    int avgRx = 0;
    int avgRy = 0;
    int avgGx = 0;
    int avgGy = 0;
    int avgBx = 0;
    int avgBy = 0;
    int aa, aaa, aaaa;
    int a0, a1, a2, a3, a4, a5, a6;
    char a7 = 9;
    double Redxy;
    double Greenxy;
    double Bluexy;
    RGBTRIPLE(*imagetemp)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //edge no borders pixels
            if (i > 0 && j > 0 && i < (height - 1) && j < (width - 1))
            {
            avgRx = (image[i - 1][j - 1].rgbtRed * gx[0][0]) + (image[i - 1][j + 1].rgbtRed * gx[0][2]) +
                (image[i][j - 1].rgbtRed * gx[1][0]) + (image[i][j + 1].rgbtRed * gx[1][2]) +
                (image[i + 1][j - 1].rgbtRed * gx[2][0]) + (image[i + 1][j + 1].rgbtRed * gx[2][2]);

            avgRy = (image[i - 1][j - 1].rgbtRed * gy[0][0]) + (image[i - 1][j + 1].rgbtRed * gy[0][2]) +
                (image[i][j - 1].rgbtRed * gy[1][0]) + (image[i][j + 1].rgbtRed * gy[1][2]) +
                (image[i + 1][j - 1].rgbtRed * gy[2][0]) + (image[i + 1][j + 1].rgbtRed * gy[2][2]);

            avgGx = (image[i - 1][j - 1].rgbtGreen * gx[0][0]) + (image[i - 1][j + 1].rgbtGreen * gx[0][2]) +
                (image[i][j - 1].rgbtGreen * gx[1][0]) + (image[i][j + 1].rgbtGreen * gx[1][2]) +
                (image[i + 1][j - 1].rgbtGreen * gx[2][0]) + (image[i + 1][j + 1].rgbtGreen * gx[2][2]);

            avgGy = (image[i - 1][j - 1].rgbtGreen * gy[0][0]) + (image[i - 1][j + 1].rgbtGreen * gy[0][2]) +
                (image[i][j - 1].rgbtGreen * gy[1][0]) + (image[i][j + 1].rgbtGreen * gy[1][2]) +
                (image[i + 1][j - 1].rgbtGreen * gy[2][0]) + (image[i + 1][j + 1].rgbtGreen * gy[2][2]);

            avgBx = (image[i - 1][j - 1].rgbtBlue * gx[0][0]) + (image[i - 1][j + 1].rgbtBlue * gx[0][2]) +
                (image[i][j - 1].rgbtBlue * gx[1][0]) + (image[i][j + 1].rgbtBlue * gx[1][2]) +
                (image[i + 1][j - 1].rgbtBlue * gx[2][0]) + (image[i + 1][j + 1].rgbtBlue * gx[2][2]);

            avgBy = (image[i - 1][j - 1].rgbtBlue * gy[0][0]) + (image[i - 1][j + 1].rgbtBlue * gy[0][2]) +
                (image[i][j - 1].rgbtBlue * gy[1][0]) + (image[i][j + 1].rgbtBlue * gy[1][2]) +
                (image[i + 1][j - 1].rgbtBlue * gy[2][0]) + (image[i + 1][j + 1].rgbtBlue * gy[2][2]);
            }

            aa = image[i][j].rgbtRed;
            aaa = image[i][j - 1].rgbtRed;
            aaaa = image[i][j + 1].rgbtRed;

            a0 = image[i - 1][j - 1].rgbtRed * gx[0][0];
            a1 = image[i - 1][j + 1].rgbtRed * gx[0][2];
            a2 = image[i][j - 1].rgbtRed * gx[1][0];
            a3 = image[i][j + 1].rgbtRed * gx[1][2];
            a4 = image[i + 1][j - 1].rgbtRed * gx[2][0];
            a5 = image[i + 1][j + 1].rgbtRed * gx[2][2];


            Redxy = sqrt(pow(avgRx, 2) + pow(avgRy, 2));
            Greenxy = sqrt(pow(avgGx, 2) + pow(avgGy, 2));
            Bluexy = sqrt(pow(avgBx, 2) + pow(avgBy, 2));
            //printf("%f %f %f \n", Redxy, Greenxy, Bluexy);

            //check red pixel value
            if (Redxy > 255)
            {
                imagetemp[i][j].rgbtRed = 255;
            }
            else
            {
                imagetemp[i][j].rgbtRed = Redxy;
            }

            if (Greenxy > 255)
            {
                imagetemp[i][j].rgbtGreen = 255;
            }
            else
            {
                imagetemp[i][j].rgbtGreen = Greenxy;
            }

            if (Bluexy > 255)
            {
                imagetemp[i][j].rgbtBlue = 255;
            }
            else
            {
                imagetemp[i][j].rgbtBlue = Bluexy;
            }


        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = imagetemp[i][j].rgbtRed;
            image[i][j].rgbtGreen = imagetemp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = imagetemp[i][j].rgbtBlue;
        }
    }

    free(imagetemp);




    return;
}
