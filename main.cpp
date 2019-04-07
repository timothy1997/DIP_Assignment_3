#include <stdio.h>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <opencv2/core/core.hpp>
#include <iostream>

using namespace std;
using namespace cv;

bool RetrieveImage(int argc, char** argv);
void GetRGBChannels();
int display_dst(int delay);

int DELAY_CAPTION = 1500;
int DELAY_BLUR = 100;
int MAX_KERNEL_LENGTH = 31;
Mat src;  // Holds source image
Mat channel[3]; // Holds rgb channels
char window_name[] = "Filter Demo 1";
Mat dst;

int main(int argc, char** argv)
{
    if(!RetrieveImage(argc, argv))  // Try and get the image
      return -1;

    namedWindow("Original Image", WINDOW_AUTOSIZE);
    namedWindow("Resulting Image", WINDOW_AUTOSIZE);
    namedWindow("Final Image", WINDOW_AUTOSIZE);
    namedWindow("Channel 0", WINDOW_AUTOSIZE);
    namedWindow("Channel 1", WINDOW_AUTOSIZE);  // Create windows
    namedWindow("Channel 2", WINDOW_AUTOSIZE);

    split(src, channel);  // Split the source image (src) into multiple channels

    imshow("Original Image", src);
    medianBlur(channel[0],channel[0],255); // Applying Median blur to channel 0
    medianBlur(channel[1],channel[1],123); // Applying Median blur to channel 1
    medianBlur(channel[2],channel[2],123); // Applying Median blur to channel 2
    imshow("Channel 0", channel[0]);
    imshow("Channel 1", channel[1]);
    imshow("Channel 2", channel[2]);
    Mat image;
    merge(channel, 3, image);
    imshow("Resulting Image", image);
    Mat final;
    subtract(src*2, image, final);  //  image subtraction img3=img1-img2
    imshow("Final Image", final);

    waitKey(0);
    return 0;
}

bool RetrieveImage(int argc, char** argv) {
  if ( argc != 2 )  {
      printf("usage: PicRepair.out <Image_Path>\n");
      return false;
  }

  src = imread( argv[1], 1 );

  if ( !src.data )  {
      printf("No image data \n");
      return false;
  } else {
    return true;
  }
}

int display_dst(int delay)
{
    imshow( window_name, dst );
    int c = waitKey ( delay );
    if( c >= 0 ) { return -1; }
    return 0;
}
