#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //grayscale value variable
    float greycol;
    //loop over each row
    for (int i = 0; i < height; i++)
    {
        //loop over each column
        for (int j = 0; j < width; j++)
        {
            //computate the RGB grayscale values of a pixel
            greycol = round(((float)image[i][j].rgbtRed + (float) image[i][j].rgbtBlue + (float) image[i][j].rgbtGreen)/3);
            //set the RGB values in the pixel to the greyscale value
            image[i][j].rgbtRed = greycol;
            image[i][j].rgbtBlue = greycol;
            image[i][j].rgbtGreen = greycol;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //empty temporary array of the original image
    RGBTRIPLE temp[height][width];

    //loop over each row
    for (int i = 0; i < height; i++)
    {
        //loop over each column
        for (int j = 0; j < width; j++)
        {
            //copy the pixels to a temporary RGBTRIPLE variable in reverse order
            temp[i][j].rgbtRed = image[i][width-(j+1)].rgbtRed;
            temp[i][j].rgbtBlue = image[i][width-(j+1)].rgbtBlue;
            temp[i][j].rgbtGreen = image[i][width-(j+1)].rgbtGreen;
        }
    }
    //replace the pixels in the original image with pixels in the image with a filter applied
    //loop over each row
    for (int i = 0; i < height; i++)
    {
        //loop over each column
        for (int j = 0; j < width; j++)
        {
            //replace the original RGB values of each pixel with the RGB values in the temporary array
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //empty temporary image array
    RGBTRIPLE blur[height][width];
    //variables for total RGB values in a box
    int totalR;
    int totalG;
    int totalB;
    //varibale for number of pixels counted for in the box algorithm
    int count;
    //loop over rows
    for (int i = 0; i < height; i++)
    {
        //loop over columns
        for (int j = 0; j < width; j++)
        {
            //reset the values of variables used in the loop
            totalR = 0;
            totalG = 0;
            totalB = 0;
            count = 0;
            //compuatate the average RGB values for a pixel in the topleft corner
            if(i == 0 && j == 0)
            {
                for(int k = 0; k < 2;k++)
                {
                    for(int l = 0; l < 2; l++)
                    {
                        totalR = totalR + image[k][l].rgbtRed;
                        totalB = totalB + image[k][l].rgbtBlue;
                        totalG = totalG + image[k][l].rgbtGreen;
                    }
                }
                count = 4;
            }
            // compuatate the average RGB values for a pixel in the topright corner
            else if(i == 0 && j == (width-1))
            {
                for(int k = 0; k <= 1;k++)
                {
                    for(int l = j-1; l < width; l++)
                    {
                        totalR = totalR + image[k][l].rgbtRed;
                        totalB = totalB + image[k][l].rgbtBlue;
                        totalG = totalG + image[k][l].rgbtGreen;
                    }
                }
                count = 4;
            }
            //compuatate the average RGB values for a pixel in the bottomleft corner
            else if(i == (height-1) && j == 0)
            {
                for(int k = (height-2); k < height;k++)
                {
                    for(int l = 0; l <=1; l++)
                    {
                        totalR = totalR + image[k][l].rgbtRed;
                        totalB = totalB + image[k][l].rgbtBlue;
                        totalG = totalG + image[k][l].rgbtGreen;
                    }
                }
                count = 4;
            }
            //compuatate the average RGB values for a pixel in the bottomright corner
            else if(i == (height-1) && j == (width-1))
            {
                for(int k = (height-2); k < height;k++)
                {
                    for(int l = (width-2); l < width; l++)
                    {
                        totalR = totalR + image[k][l].rgbtRed;
                        totalB = totalB + image[k][l].rgbtBlue;
                        totalG = totalG + image[k][l].rgbtGreen;
                    }
                }
                count = 4;
            }
            //computate the average RGB values for a pixel on the top row
            else if(i == 0 && (j != 0 | j!= (width-1)))
            {
                for(int k = 0; k <= 1;k++)
                {
                    for (int l = j-1;l <= j+1;l++)
                    {
                        totalR = totalR + image[k][l].rgbtRed;
                        totalB = totalB + image[k][l].rgbtBlue;
                        totalG = totalG + image[k][l].rgbtGreen;
                        count++;
                    }
                }
            }
            //computate the average RGB values for a pixel on the bottom row
            else if(i==(height-1) && (j != 0 | j!= (width-1)))
            {
                for(int k = (height-2); k <= i;k++)
                {
                    for (int l = j-1;l <= j+1;l++)
                    {
                        totalR = totalR + image[k][l].rgbtRed;
                        totalB = totalB + image[k][l].rgbtBlue;
                        totalG = totalG + image[k][l].rgbtGreen;
                        count++;
                    }
                }
            }
            //computate the average RGB values for a pixel on the left column
            else if(j == 0 && !(i == 0 | i == (height-1)))
            {
                for(int k = i -1; k <= i+1; k++)
                {
                    for(int l = j; l <= j+1;l++)
                    {
                        totalR = totalR + image[k][l].rgbtRed;
                        totalB = totalB + image[k][l].rgbtBlue;
                        totalG = totalG + image[k][l].rgbtGreen;
                        count++;
                    }
                }
            }
            //computate the average RGB values for a pixel on the right column
            else if(j == (height-1) && !(i == 0 | i == (height-1)))
            {
                for(int k = i -1; k <= i+1; k++)
                {
                    for(int l = j-1; l <= j;l++)
                    {
                        totalR = totalR + image[k][l].rgbtRed;
                        totalB = totalB + image[k][l].rgbtBlue;
                        totalG = totalG + image[k][l].rgbtGreen;
                        count++;
                    }
                }
            }
            //computate the average RGB values for a pixel that is not touching any edge
            else
            {
                for (int k = i-1; k < i+2;k++)
                {
                    for(int l = j-1; l < j+2; l++)
                    {
                        totalR = totalR + image[k][l].rgbtRed;
                        totalB = totalB + image[k][l].rgbtBlue;
                        totalG = totalG + image[k][l].rgbtGreen;
                        count++;
                    }
                }
            }
            blur[i][j].rgbtRed = round( (float) totalR/count);
            blur[i][j].rgbtBlue = round( (float) totalB/count);
            blur[i][j].rgbtGreen = round( (float) totalG/count);
        }
    }
    //replace the pixels in the original image with pixels in the image with a filter applied
    //loop over rows
    for (int i = 0; i < height; i++)
    {
        //loops over columns
        for (int j = 0; j < width; j++)
        {
            //replace the original RGB values of each pixel with the RGB values in the temporary array
            image[i][j].rgbtRed = blur[i][j].rgbtRed;
            image[i][j].rgbtBlue = blur[i][j].rgbtBlue;
            image[i][j].rgbtGreen = blur[i][j].rgbtGreen;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //variable arrays for algorithm used in the filter
    int gX[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int gY[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
    //variables to save sum of RGB values in a box
    int totalXR = 0;
    int totalXG = 0;
    int totalXB = 0;
    int totalYR = 0;
    int totalYG = 0;
    int totalYB = 0;
    //counters to help in applying the algorithm to the pixel
    int counterX = 1;
    int counterY = 1;
    //empty temporary array of original image
    RGBTRIPLE newarr[height][width];

    //loop over rows
    for (int i = 0; i < height; i++)
    {
        //loop over columns
        for (int j = 0; j < width; j++)
        {
            //reset the values of variables used in the loop
            totalXR = 0;
            totalXG = 0;
            totalXB = 0;
            totalYR = 0;
            totalYG = 0;
            totalYB = 0;
            counterX = 1;
            counterY = 1;
            //compuatate the average RGB values for a pixel in the topleft corner
            if(i == 0 && j == 0)
            {
                for(int k = 0; k < 2;k++)
                {
                    for(int l = 0; l < 2; l++)
                    {
                        //apply the given filter algorithm to each pixel and get the sum of the Gx and Gy RGB values in a box
                        totalXR = totalXR + image[k][l].rgbtRed*gX[counterX][counterY];
                        totalYR = totalYR + image[k][l].rgbtRed*gY[counterX][counterY];
                        totalXG = totalXG + image[k][l].rgbtGreen*gX[counterX][counterY];
                        totalYG = totalYG + image[k][l].rgbtGreen*gY[counterX][counterY];
                        totalXB = totalXB + image[k][l].rgbtBlue*gX[counterX][counterY];
                        totalYB = totalYB + image[k][l].rgbtBlue*gY[counterX][counterY];
                        counterY++;
                    }
                    counterX++;
                    counterY =1;
                }
            }
            // compuatate the average RGB values for a pixel in the topright corner
            else if(i == 0 && j == (width-1))
            {
                counterY=0;
                for(int k = 0; k <= 1;k++)
                {
                    for(int l = j-1; l < width; l++)
                    {
                        //apply the given filter algorithm to each pixel and get the sum of the Gx and Gy RGB values in a box
                        totalXR = totalXR + image[k][l].rgbtRed*gX[counterX][counterY];
                        totalYR = totalYR + image[k][l].rgbtRed*gY[counterX][counterY];
                        totalXB = totalXB + image[k][l].rgbtBlue*gX[counterX][counterY];
                        totalYB = totalYB + image[k][l].rgbtBlue*gY[counterX][counterY];
                        totalXG = totalXG + image[k][l].rgbtGreen*gX[counterX][counterY];
                        totalYG = totalYG + image[k][l].rgbtGreen*gY[counterX][counterY];
                        counterY++;
                    }
                    counterX++;
                    counterY = 0;
                }
            }
            //compuatate the average RGB values for a pixel in the bottomleft corner
            else if(i == (height-1) && j == 0)
            {
                counterX = 0;
                for(int k = (height-2); k < height;k++)
                {
                    for(int l = 0; l <=1; l++)
                    {
                        //apply the given filter algorithm to each pixel and get the sum of the Gx and Gy RGB values in a box
                        totalXR = totalXR + image[k][l].rgbtRed*gX[counterX][counterY];
                        totalYR = totalYR + image[k][l].rgbtRed*gY[counterX][counterY];
                        totalXG = totalXG + image[k][l].rgbtGreen*gX[counterX][counterY];
                        totalYG = totalYG + image[k][l].rgbtGreen*gY[counterX][counterY];
                        totalXB = totalXB + image[k][l].rgbtBlue*gX[counterX][counterY];
                        totalYB = totalYB + image[k][l].rgbtBlue*gY[counterX][counterY];
                        counterY--;
                    }
                    counterX++;
                    counterY = 1;
                }
            }
            //compuatate the average RGB values for a pixel in the bottomright corner
            else if(i == (height-1) && j == (width-1))
            {
                counterX = 0;
                counterY = 0;
                for(int k = (height-2); k < height;k++)
                {
                    for(int l = (width-2); l < width; l++)
                    {
                        //apply the given filter algorithm to each pixel and get the sum of the Gx and Gy RGB values in a box
                        totalXR = totalXR + image[k][l].rgbtRed*gX[counterX][counterY];
                        totalYR = totalYR + image[k][l].rgbtRed*gY[counterX][counterY];
                        totalXG = totalXG + image[k][l].rgbtGreen*gX[counterX][counterY];
                        totalYG = totalYG + image[k][l].rgbtGreen*gY[counterX][counterY];
                        totalXB = totalXB + image[k][l].rgbtBlue*gX[counterX][counterY];
                        totalYB = totalYB + image[k][l].rgbtBlue*gY[counterX][counterY];
                        counterY++;
                    }
                    counterX++;
                    counterY = 0;
                }
            }
            //computate the average RGB values for a pixel on the top row
            else if(i == 0 && (j != 0 | j!= (width-1)))
            {
                counterY = 0;
                for(int k = 0; k <= 1;k++)
                {
                    for (int l = j-1;l <= j+1;l++)
                    {
                        //apply the given filter algorithm to each pixel and get the sum of the Gx and Gy RGB values in a box
                        totalXR = totalXR + image[k][l].rgbtRed*gX[counterX][counterY];
                        totalYR = totalYR + image[k][l].rgbtRed*gY[counterX][counterY];
                        totalXG = totalXG + image[k][l].rgbtGreen*gX[counterX][counterY];
                        totalYG = totalYG + image[k][l].rgbtGreen*gY[counterX][counterY];
                        totalXB = totalXB + image[k][l].rgbtBlue*gX[counterX][counterY];
                        totalYB = totalYB + image[k][l].rgbtBlue*gY[counterX][counterY];
                        counterY++;
                    }
                    counterX++;
                    counterY = 0;
                }
            }
            //computate the average RGB values for a pixel on the bottom row
            else if(i==(height-1) && (j != 0 | j!= (width-1)))
            {
                counterX = 0;
                counterY = 0;
                for(int k = (height-2); k <= i;k++)
                {
                    for (int l = j-1;l <= j+1;l++)
                    {
                        //apply the given filter algorithm to each pixel and get the sum of the Gx and Gy RGB values in a box
                        totalXR = totalXR + image[k][l].rgbtRed*gX[counterX][counterY];
                        totalYR = totalYR + image[k][l].rgbtRed*gY[counterX][counterY];
                        totalXG = totalXG + image[k][l].rgbtGreen*gX[counterX][counterY];
                        totalYG = totalYG + image[k][l].rgbtGreen*gY[counterX][counterY];
                        totalXB = totalXB + image[k][l].rgbtBlue*gX[counterX][counterY];
                        totalYB = totalYB + image[k][l].rgbtBlue*gY[counterX][counterY];
                        counterY++;
                    }
                    counterX++;
                    counterY = 0;
                }
            }
            //computate the average RGB values for a pixel on the left column
            else if(j == 0 && !(i == 0 | i == (height-1)))
            {
                counterX = 0;
                for(int k = i -1; k <= i+1; k++)
                {
                    for(int l = j; l <= j+1;l++)
                    {
                        //apply the given filter algorithm to each pixel and get the sum of the Gx and Gy RGB values in a box
                        totalXR = totalXR + image[k][l].rgbtRed*gX[counterX][counterY];
                        totalYR = totalYR + image[k][l].rgbtRed*gY[counterX][counterY];
                        totalXG = totalXG + image[k][l].rgbtGreen*gX[counterX][counterY];
                        totalYG = totalYG + image[k][l].rgbtGreen*gY[counterX][counterY];
                        totalXB = totalXB + image[k][l].rgbtBlue*gX[counterX][counterY];
                        totalYB = totalYB + image[k][l].rgbtBlue*gY[counterX][counterY];
                        counterY++;
                    }
                    counterX++;
                    counterY =1;
                }
            }
            //computate the average RGB values for a pixel on the right column
            else if(j == (height-1) && !(i == 0 | i == (height-1)))
            {
                counterY = 0;
                counterX = 0;
                for(int k = i -1; k <= i+1; k++)
                {
                    for(int l = j-1; l <= j;l++)
                    {
                        //apply the given filter algorithm to each pixel and get the sum of the Gx and Gy RGB values in a box
                        totalXR = totalXR + image[k][l].rgbtRed*gX[counterX][counterY];
                        totalYR = totalYR + image[k][l].rgbtRed*gY[counterX][counterY];
                        totalXG = totalXG + image[k][l].rgbtGreen*gX[counterX][counterY];
                        totalYG = totalYG + image[k][l].rgbtGreen*gY[counterX][counterY];
                        totalXB = totalXB + image[k][l].rgbtBlue*gX[counterX][counterY];
                        totalYB = totalYB + image[k][l].rgbtBlue*gY[counterX][counterY];
                        counterY++;
                    }
                    counterX++;
                    counterY=0;
                }
            }
            //computate the average RGB values for a pixel that is not touching any edge
            else
            {
                counterX = 0;
                counterY = 0;
                for (int k = i-1; k < i+2;k++)
                {
                    for(int l = j-1; l < j+2; l++)
                    {
                        //apply the given filter algorithm to each pixel and get the sum of the Gx and Gy RGB values in a box
                        totalXR = totalXR + image[k][l].rgbtRed*gX[counterX][counterY];
                        totalYR = totalYR + image[k][l].rgbtRed*gY[counterX][counterY];
                        totalXG = totalXG + image[k][l].rgbtGreen*gX[counterX][counterY];
                        totalYG = totalYG + image[k][l].rgbtGreen*gY[counterX][counterY];
                        totalXB = totalXB + image[k][l].rgbtBlue*gX[counterX][counterY];
                        totalYB = totalYB + image[k][l].rgbtBlue*gY[counterX][counterY];
                        counterY++;
                    }
                    counterX++;
                    counterY=0;
                }
            }
            //apply the algorithm sqrt(Gx^2 + Gy^2)
            totalXR = (totalXR*totalXR) + (totalYR*totalYR);
            totalXG = (totalXG*totalXG) + (totalYG*totalYG);
            totalXB = (totalXB*totalXB) + (totalYB*totalYB);
            totalXR = round(sqrt(totalXR));
            totalXG = round(sqrt(totalXG));
            totalXB = round(sqrt(totalXB));
            //check for any RGB values over 255, if yes, replace value with 255
            if (totalXR > 255)
            {
                totalXR = 255;
            }
            if (totalXB > 255)
            {
                totalXB = 255;
            }
            if (totalXG > 255)
            {
                totalXG = 255;
            }
            //apply new filtered RGB value of original pixel to temporary array pixel
            newarr[i][j].rgbtRed = totalXR;
            newarr[i][j].rgbtBlue = totalXB;
            newarr[i][j].rgbtGreen = totalXG;
        }
    }
    //replace the pixels in the original image with pixels in the image with a filter applied
    //loop over rows
    for (int i = 0; i < height; i++)
    {
        //loop over columns
        for (int j = 0; j < width; j++)
        {
            //replace the original RGB values of each pixel with the RGB values in the temporary array
            image[i][j].rgbtRed = newarr[i][j].rgbtRed;
            image[i][j].rgbtBlue = newarr[i][j].rgbtBlue;
            image[i][j].rgbtGreen = newarr[i][j].rgbtGreen;
        }
    }
    return;
}