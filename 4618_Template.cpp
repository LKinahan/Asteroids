////////////////////////////////////////////////////////////////
// ELEX 4618 Template project for BCIT
// Created Oct 5, 2016 by Craig Hennessey.
// Last updated January 19, 2021
// Modified March 3 2021 by laurel Kinahan
////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CControl.h"
#include "CBase4618.h"
#include "CAsteroid.h"
#include "Server.h"
#include "Serial.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>

#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/opencv.hpp"


using namespace std;
using namespace cv;

////////////////////////////////////////////////////////////////
// Display Image on screen
////////////////////////////////////////////////////////////////
void do_image()
{
	Mat im;
	im = imread("Hyperspace_falcon.png");
	imshow("Image", im);
	waitKey(1000);
	destroyAllWindows();
}

////////////////////////////////////////////////////////////////
// Display Video on screen
////////////////////////////////////////////////////////////////
void do_video()
{
	VideoCapture vid;

	vid.open("SpaceJump.mp4");

	if (vid.isOpened() == TRUE)
	{
		while (1)
		{
			Mat frame;
			vid >> frame;
			waitKey(15);
			break;
		}
	}
	//imshow("Frame", frame);
	vid.release();
	destroyAllWindows();
}

int main(int argc, char* argv[])
{
	char inputSelect;

	do {
		cout << "**************************************** \n"
			<< "              ELEX4618 \n"
			<< "       Embedded System Control \n"
			<< "**************************************** \n\n"
			<< "(A)stroids \n"
			<< "(S)ketch App\n"
			<< "(P)ong \n"
			<< "(Q)uit \n"
			<< "\nCommand:";

		cin >> inputSelect;

		switch (inputSelect) {

		case 'A':
		case 'a': {
			do_image();
			CAsteroid Asteroids;
			Asteroids.run();
			break;
		}
		case 'Q':
		case 'q': {
			cout << "Quiting" << endl;
			exit(0);
			break;
		}
		default: {
			cout << "Command not found\n";
			inputSelect = 0;
			break;
		}
		}

	} while (inputSelect == 'Y' || inputSelect == 'y' || inputSelect == 0);
	return 0;
}

