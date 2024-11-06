#include "cv.h"
#include "highgui.h"

int main(int argc, char* argv[])
{
	IplImage* img;
	img = cvLoadImage(argv[1], CV_LOAD_IMAGE_COLOR);

	if (!img) {
		printf("Could not load image file: %s\n", argv[1]);
		return -1;
	}

	int width = img->width;
	int height = img->height;
	int widthstep = img->widthStep;
	int channels = img->nChannels;

	// print ipl attributes ( width,height,widthStep  and no of channels

	printf("width: %d\n", width);
	printf("height: %d\n", height);
	printf("widthStep: %d\n", widthstep);
	printf("channels: %d\n", channels);

	uchar* data = (uchar*)img->imageData;

	//print no of blue ,green and red pixels between 100*100

	int i = 100; //y axis
	int j = 100; //x axis

	int b = data[i * widthstep + j * channels];
	int g = data[i * widthstep + j * channels +1];
	int r = data[i * widthstep + j * channels + 2];

	printf("blue: %d\n", b);
	printf("green: %d\n", g);
	printf("red: %d\n", r);

	//change those pixels to black color or white color
	data[i * widthstep + j * channels] = 0;
	data[i * widthstep + j * channels + 1] = 0;
	data[i * widthstep + j * channels + 2] = 0;

	//200*200 to white color
	for (int a = 0;a <= 100;a++)
	{
		for (int b = 0;b <= 100;b++)
		{
			data[a * widthstep + b * channels] = 255;
			data[a * widthstep + b * channels + 1] = 255;
			data[a * widthstep + b * channels + 2] = 255;
		}
	}

	//convert BGR  image to grayscale image
	IplImage* gray_img = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
	uchar* gray_data = (uchar*)gray_img->imageData;
	int gray_widthstep = gray_img->widthStep;
	int gray_channels = gray_img->nChannels;

	for (int i = 0;i < height;i++)
	{
		for (int j = 0;j < width;j++)
		{
			gray_data[i * gray_widthstep + j * gray_channels] = data[i * widthstep + j * channels] * 0.1140 + data[i * widthstep + j * channels + 1] * 0.5870 + data[i * widthstep + j * channels + 2] * 0.2989;

		}
	}

	//convert grayscale image to binary image
	//160 is the threshold value
	for (int i = 0;i < height;i++)
	{
		for (int j = 0;j < width;j++)
		{
			if (gray_data[i * gray_widthstep + j * gray_channels] > 160)
			{
				gray_data[i * gray_widthstep + j * gray_channels] = 255;
			}
			else
			{
				gray_data[i * gray_widthstep + j * gray_channels] = 0;
			}

		}
	}

	//Invert BGR

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			data[i * widthstep + j * channels] = 255 - data[i * widthstep + j * channels];
			data[i * widthstep + j * channels + 1] = 255 - data[i * widthstep + j * channels + 1];
			data[i * widthstep + j * channels + 2] = 255 - data[i * widthstep + j * channels + 2];
		}
	}

	IplImage* blue = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
	IplImage* green = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
	IplImage* red = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);

	uchar* dataB = (uchar*)blue->imageData;
	uchar* dataG = (uchar*)green->imageData;
	uchar* dataR = (uchar*)red->imageData;


	//Split BGR image into 3 channels
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			dataB[i * widthstep + j * channels] = data[i * widthstep + j * channels];
			dataB[i * widthstep + j * channels + 1] = 0;
			dataB[i * widthstep + j * channels + 2] = 0;

			dataG[i * widthstep + j * channels] = 0;
			dataG[i * widthstep + j * channels + 1] = data[i * widthstep + j * channels];
			dataG[i * widthstep + j * channels + 2] = 0;

			dataR[i * widthstep + j * channels] = 0;
			dataR[i * widthstep + j * channels + 1] = 0;
			dataR[i * widthstep + j * channels + 2] = data[i * widthstep + j * channels];
		}
	}


	cvNamedWindow("Image");
	cvShowImage("Image", img);
	cvNamedWindow("GrayImage");
	cvShowImage("GrayImage", gray_img);
	
	cvNamedWindow("Blue");
	cvShowImage("Blue", blue);

	cvNamedWindow("Green");
	cvShowImage("Green", green);

	cvNamedWindow("Red");
	cvShowImage("Red", red);

	cvWaitKey(0);
	cvDestroyAllWindows();
	return 0;
}