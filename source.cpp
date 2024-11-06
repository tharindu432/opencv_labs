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


	cvNamedWindow("Image");
	cvShowImage("Image", img);
	cvNamedWindow("GrayImage");
	cvShowImage("GrayImage", gray_img);
	cvWaitKey(0);
	cvDestroyWindow("Image");
	cvReleaseImage(&img);
	cvDestroyWindow("GrayImage");
	cvReleaseImage(&gray_img);
	return 0;
}