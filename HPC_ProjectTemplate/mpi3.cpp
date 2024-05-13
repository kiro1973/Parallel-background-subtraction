/*
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include<string.h>
#include<msclr\marshal_cppstd.h>
#include<mpi.h>
#include <ctime>// include this header 
#pragma once

#define NUM_OF_IMAGES 495

#using <mscorlib.dll>
#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

using namespace std;
using namespace msclr::interop;

// Function to read image and convert it to grayscale
int* readAndConvertToGrayScale(int* width, int* height, System::String^ imagePath)
{
    int* grayScaleImage;

    int originalWidth, originalHeight;

    System::Drawing::Bitmap bitmap(imagePath);

    originalWidth = bitmap.Width;
    originalHeight = bitmap.Height;
    *width = bitmap.Width;
    *height = bitmap.Height;
    int* redChannel = new int[bitmap.Height * bitmap.Width];
    int* greenChannel = new int[bitmap.Height * bitmap.Width];
    int* blueChannel = new int[bitmap.Height * bitmap.Width];
    grayScaleImage = new int[bitmap.Height * bitmap.Width];
    for (int i = 0; i < bitmap.Height; i++)
    {
        for (int j = 0; j < bitmap.Width; j++)
        {
            System::Drawing::Color color = bitmap.GetPixel(j, i);

            redChannel[i * bitmap.Width + j] = color.R;
            blueChannel[i * bitmap.Width + j] = color.B;
            greenChannel[i * bitmap.Width + j] = color.G;

            grayScaleImage[i * bitmap.Width + j] = ((color.R + color.B + color.G) / 3); // Gray scale value equals the average of RGB values
        }
    }
    return grayScaleImage;
}

// Function to create a new image from grayscale pixel values
void createImage(int* image, int width, int height, int index)
{
    System::Drawing::Bitmap newImage(width, height);

    for (int i = 0; i < newImage.Height; i++)
    {
        for (int j = 0; j < newImage.Width; j++)
        {
            if (image[i * width + j] < 0)
            {
                image[i * width + j] = 0;
            }
            if (image[i * width + j] > 255)
            {
                image[i * width + j] = 255;
            }
            System::Drawing::Color color = System::Drawing::Color::FromArgb(image[i * newImage.Width + j], image[i * newImage.Width + j], image[i * newImage.Width + j]);
            newImage.SetPixel(j, i, color);
        }
    }
    newImage.Save("C:/semester_10/HPC/project_versions/Parallel-Background-Subtraction-main/Data/Output/outputResult" + index + ".png");
    cout << "Result Image Saved " << index << endl;
}

// Function to get the path of the image given its index
std::string getImagePath(int index)
{
    std::string imagePath;
    if (index < 10)
    {
        imagePath = "C:/semester_10/HPC/project_versions/Parallel-Background-Subtraction-main/Data/Input/in00000" + to_string(index) + ".jpg";
    }
    else if (index < 100)
    {
        imagePath = "C:/semester_10/HPC/project_versions/Parallel-Background-Subtraction-main/Data/Input/in0000" + to_string(index) + ".jpg";
    }
    else if (index < 1000)
    {
        imagePath = "C:/semester_10/HPC/project_versions/Parallel-Background-Subtraction-main/Data/Input/in000" + to_string(index) + ".jpg";
    }
    return imagePath;
}

int main()
{
    MPI_Init(NULL, NULL);
    int worldSize, rank;
    int imageWidth = 4, imageHeight = 4;
    int startTime, stopTime, totalTime = 0;
    MPI_Comm_size(MPI_COMM_WORLD, &worldSize);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0)
    {
        startTime = clock();
    }
    int** imagesArray = new int* [NUM_OF_IMAGES / worldSize];
    int imageCounter = 0;
    for (int i = (NUM_OF_IMAGES * rank / worldSize) + 1; i < (NUM_OF_IMAGES * (rank + 1) / worldSize) + 1; i++)
    {
        System::String^ imagePath;
        std::string img = getImagePath(i);
        imagePath = marshal_as<System::String^>(img);
        int* imageData = readAndConvertToGrayScale(&imageWidth, &imageHeight, imagePath);
        imagesArray[imageCounter] = new int[imageHeight * imageWidth];
        for (int j = 0; j < imageHeight * imageWidth; j++)
        {
            imagesArray[imageCounter][j] = imageData[j];
        }
        free(imageData);
        imageCounter++;
    }
    int* means = new int[imageHeight * imageWidth];
    int sum;
    for (int i = 0; i < imageHeight * imageWidth; i++)
    {
        sum = 0;
        for (int j = 0; j < NUM_OF_IMAGES / worldSize; j++)
        {
            sum += imagesArray[j][i];
        }
        means[i] = sum / (NUM_OF_IMAGES / worldSize);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    int* globalMeans = new int[imageHeight * imageWidth];
    MPI_Reduce(means, globalMeans, imageHeight * imageWidth, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    if (rank == 0)
    {
        for (int i = 0; i < imageHeight * imageWidth; i++)
        {
            globalMeans[i] /= worldSize;
        }
        createImage(globalMeans, imageWidth, imageHeight, 0);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(globalMeans, imageHeight * imageWidth, MPI_INT, 0, MPI_COMM_WORLD);
    imageCounter = 0;
    int threshold = 75;
    for (int i = (NUM_OF_IMAGES * rank / worldSize) + 1; i < (NUM_OF_IMAGES * (rank + 1) / worldSize) + 1; i++)
    {
        int* subtraction = new int[imageHeight * imageWidth];
        for (int j = 0; j < imageHeight * imageWidth; j++)
        {
            subtraction[j] = abs(globalMeans[j] - imagesArray[imageCounter][j]) > threshold ? 255 : 0;
        }
        createImage(subtraction, imageWidth, imageHeight, i);
        free(subtraction);
        imageCounter++;
    }
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0)
    {
        stopTime = clock();
        totalTime += (stopTime - startTime) / double(CLOCKS_PER_SEC) * 1000;
        cout << "Total time: " << totalTime << " ms" << endl;
    }
    MPI_Finalize();
    return 0;
}
*/