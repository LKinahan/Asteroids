///////////////////////////////////////////////////////////////////////////////////////////
// CRock.cpp for ELEX 4618
// Member function definitions for class CRock that 
//     defines poisition, velcoity, number of lives, color, shape and size of Rock
// Created March 01, 2021 by Laurel Kinahan 
//////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CRock.h"

////////////////////////////////////////////////////////////////
// Class Constructor
////////////////////////////////////////////////////////////////
CRock::CRock(cv::Point2f pos)
	{
	//asteroids have 1 life before removed from image
	set_lives(1);
	//initilaize srand to randomize direction, velocity and size
	srand(cv::getTickCount());
	prev_time = cv::getTickCount();
	//randomize size
	_radius = rand() % 22 + 10;
	//asteroids come from top of frame
	pos = cv::Point2f(rand() % 1003, 0);
	//randomize direction
	set_pos(pos);
	if (pos.x < 500)
		velocity = cv::Point2f(rand() % 51 + 25, rand() % 101 + 200);
	else
		velocity = cv::Point2f(-(rand() % 51 + 25), rand() % 101 + 200);
	}

////////////////////////////////////////////////////////////////
// Class Deconstructor
////////////////////////////////////////////////////////////////
CRock::~CRock(void)
	{

	}

////////////////////////////////////////////////////////////////
// Class draw
////////////////////////////////////////////////////////////////
//set color of Rock
cv::Scalar CRock::rock = cv::Scalar(128, 192, 255);
//shape of asteroid to be unfilled circle
void CRock::draw(cv::Mat& im)
	{
	cv::circle(im, get_pos(), _radius, rock, 3, 8, 0);
	}
