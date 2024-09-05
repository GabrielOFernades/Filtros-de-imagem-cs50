#include "helpers.h"
#include<math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int sum[height][width];
    float average[height][width];

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            sum[i][j] = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
            average[i][j] = round((float) sum[i][j]/ 3);

            image[i][j].rgbtRed = average[i][j];
            image[i][j].rgbtGreen = average[i][j];
            image[i][j].rgbtBlue = average[i][j];
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width/2; j++)
        {
            RGBTRIPLE placeholder = image[i][j];
            image[i][j] = image[i][width - (j+1)];
            image[i][width - (j+1)] = placeholder;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width-1; j++)
        {
            int contador = 0;
            int sum[3] = {0};

            if(i > 0)
            {
                sum[0] += image[i-1][j].rgbtRed;
                sum[1] += image[i-1][j].rgbtGreen;
                sum[2] += image[i-1][j].rgbtBlue;
                contador++;

               if(i < height)
                {
                    sum[0] += image[i+1][j].rgbtRed;
                    sum[1] += image[i+1][j].rgbtGreen;
                    sum[2] += image[i+1][j].rgbtBlue;
                    contador++;
                }
            }
            if(i > 0 && j < width)
            {
                sum[0] += image[i-1][j+1].rgbtRed;
                sum[1] += image[i-1][j+1].rgbtGreen;
                sum[2] += image[i-1][j+1].rgbtBlue;
                contador++;
            }
            if(i > 0  && j > 0)
            {
                sum[0] += image[i-1][j-1].rgbtRed;
                sum[1] += image[i-1][j-1].rgbtGreen;
                sum[2] += image[i-1][j-1].rgbtBlue;
                contador++;
            }
            if(j > 0)
            {
                sum[0] += image[i][j-1].rgbtRed;
                sum[1] += image[i][j-1].rgbtGreen;
                sum[2] += image[i][j-1].rgbtBlue;
                contador++;

                if(j < width)
                {
                    sum[0] += image[i][j+1].rgbtRed;
                    sum[1] += image[i][j+1].rgbtGreen;
                    sum[2] += image[i][j+1].rgbtBlue;
                    contador++;
                }
            }



            if(i < height && j < width)
            {
                sum[0] += image[i+1][j+1].rgbtRed;
                sum[1] += image[i+1][j+1].rgbtGreen;
                sum[2] += image[i+1][j+1].rgbtBlue;
                contador++;
            }

            if(i < height && j > 0)
            {
                sum[0] += image[i+1][j-1].rgbtRed;
                sum[1] += image[i+1][j-1].rgbtGreen;
                sum[2] += image[i+1][j-1].rgbtBlue;
                contador++;
            }

            sum[0] += image[i][j].rgbtRed;
            sum[1] += image[i][j].rgbtGreen;
            sum[2] += image[i][j].rgbtBlue;
            contador++;

            image[i][j].rgbtRed = sum[0]/contador;
            image[i][j].rgbtGreen = sum[1]/contador;
            image[i][j].rgbtBlue = sum[2]/contador;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    int Gx[3][3] = {{-1,0,1}, {-2,0,2}, {-1,0,1}};
    int Gy[3][3] = {{-1,-2,-1}, {0,0,0}, {1,2,1}};

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int redX = 0;
            int greenX = 0;
            int blueX = 0;
            int redY = 0;
            int greenY = 0;
            int blueY = 0;

            for(int x = 0; x < 3; x++)
            {
                for(int y = 0; y < 3; y++)
                {
                    if(i - 1 + x < 0 || i - 1 + x > height - 1 ||
                    j - 1 + y < 0 || j - 1 + y > width -1)
                    {
                        continue;
                    }

                    redX = redX + (image[i - 1 + x][j - 1 + y].rgbtRed * Gx[x][y]);
                    greenX = greenX + (image[i - 1 + x][j - 1 + y].rgbtGreen * Gx[x][y]);
                    blueX = blueX + (image[i - 1 + x][j - 1 + y].rgbtBlue * Gx[x][y]);


                    redY = redY + (image[i - 1 + x][j - 1 + y].rgbtRed * Gy[x][y]);
                    greenY = greenY + (image[i - 1 + x][j - 1 + y].rgbtGreen * Gy[x][y]);
                    blueY = blueY + (image[i - 1 + x][j - 1 + y].rgbtBlue * Gy[x][y]);

                }
            }
            int red = round(sqrt(redX * redX) + (redY * redY));
            int green = round(sqrt(greenX * greenX) + (greenY * greenY));
            int blue = round(sqrt(blueX * blueX) + (blueY * blueY));

            if (red > 255)
                red = 255;
            if (green > 255)
                green = 255;
            if (blue > 255)
                blue = 255;

            temp[i][j].rgbtRed = red;
            temp[i][j].rgbtGreen = green;
            temp[i][j].rgbtBlue = blue;
        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }

    return;
}
