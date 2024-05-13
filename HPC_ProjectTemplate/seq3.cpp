
/*
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <msclr\marshal_cppstd.h>
#include <ctime> // include this header 

#define NUM_OF_IMAGES 420 // Renamed from NUM_OF_PHOTOES

#using <mscorlib.dll>
#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

using namespace std;
using namespace msclr::interop;

// Function to read an image and convert it to grayscale
int* readAndConvertToGrayScale(int* width, int* height, System::String^ imagePath)
{
    int* grayScaleImage;

    int originalWidth, originalHeight;

    // Read Image and convert it to grayscale

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

            // Convert RGB to grayscale by averaging the color channels
            grayScaleImage[i * bitmap.Width + j] = ((color.R + color.B + color.G) / 3); // Gray scale value equals the average of RGB values

        }
    }
    return grayScaleImage;
}

// Function to create a new image from grayscale pixel values
void createImage(int* image, int width, int height, int index)
{
    System::Drawing::Bitmap newImage(width, height);

    // Set pixels of the new image with grayscale values
    for (int i = 0; i < newImage.Height; i++)
    {
        for (int j = 0; j < newImage.Width; j++)
        {
            // Ensure pixel values are within the range [0, 255]
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
    // Save the created image
    newImage.Save("C:/semester_10/HPC/project_versions/Parallel-Background-Subtraction-main/Data/Output/outputRes" + index + ".png");
    cout << "Result Image Saved " << index << endl;
}

// Function to get the path of the image given its index
std::string getImagePath(int index)
{
    std::string imagePath;
    // Construct the image path based on the index
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
    // Set initial image width and height
    int imageWidth = 4, imageHeight = 4;
    int startClock, stopClock, totalTime = 0;

    // Start the clock to measure execution time
    startClock = clock();

    // Allocate memory for storing images
    int** imagesArray = new int* [NUM_OF_IMAGES];

    // Iterate through each image
    for (int i = 1; i < NUM_OF_IMAGES + 1; i++)
    {
        // Get the path of the image
        System::String^ imagePath;
        std::string img = getImagePath(i);
        imagePath = marshal_as<System::String^>(img);

        // Read and convert the image to grayscale
        int* imageData = readAndConvertToGrayScale(&imageWidth, &imageHeight, imagePath);

        // Store the grayscale image data
        imagesArray[i - 1] = new int[imageHeight * imageWidth];
        for (int j = 0; j < imageHeight * imageWidth; j++)
        {
            imagesArray[i - 1][j] = imageData[j];
        }
        // Free memory allocated for temporary image data
        free(imageData);
    }

    // Calculate mean grayscale values
    int* means = new int[imageHeight * imageWidth];
    int sum;
    for (int i = 0; i < imageHeight * imageWidth; i++)
    {
        sum = 0;
        for (int j = 0; j < NUM_OF_IMAGES; j++)
        {
            sum += imagesArray[j][i];
        }
        means[i] = sum / NUM_OF_IMAGES;
    }

    // Calculate the mean of means
    int* meanOfMeans = new int[imageHeight * imageWidth];
    for (int i = 0; i < imageHeight * imageWidth; i++)
    {
        meanOfMeans[i] = means[i];
    }

    // Create the reference image using the mean of means
    createImage(meanOfMeans, imageWidth, imageHeight, 0);

    // Threshold value
    int threshold = 75;

    // Perform background subtraction for each image
    for (int i = 1; i < NUM_OF_IMAGES + 1; i++)
    {
        // Allocate memory for storing subtraction result
        int* subtraction = new int[imageHeight * imageWidth];

        // Perform subtraction
        for (int j = 0; j < imageHeight * imageWidth; j++)
        {
            subtraction[j] = abs(meanOfMeans[j] - imagesArray[i - 1][j]) > threshold ? 255 : 0;
        }

        // Create and save the resulting image
        createImage(subtraction, imageWidth, imageHeight, i);

        // Free memory allocated for subtraction
        free(subtraction);
    }

    // Stop the clock and calculate total execution time
    stopClock = clock();
    totalTime += (stopClock - startClock) / double(CLOCKS_PER_SEC) * 1000;

    // Output total execution time
    cout << "Total Execution Time: " << totalTime << " ms" << endl;

    // Wait for user input before exiting
    std::getchar();

    return 0;
}
*/