///////////////////////////////////////////////////////////////////////////////////////////
// CBlaster.cpp for ELEX 4618
// Member function definitions for class CBlaster that 
//     defines poisition, velcoity, number of lives, color, shape and size of Blasters
// Created March 01, 2021 by Laurel Kinahan 
//////////////////////////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CBlaster.h"

////////////////////////////////////////////////////////////////
// Class Constructor
////////////////////////////////////////////////////////////////
CBlaster::CBlaster(cv::Point2f pos)
	{
	//radius of blaster
	_radius = 5;
	//initialize poisition to match ship
	set_pos(pos);
	//blaster have 1 life before removed from image
	set_lives(1);
	//initialize srand for velocity
	srand(cv::getTickCount());
	prev_time = cv::getTickCount();
	velocity = cv::Point2f(rand() % 26 - 5, -300);
	}

////////////////////////////////////////////////////////////////
// Class Destructor
////////////////////////////////////////////////////////////////
CBlaster::~CBlaster()
	{

	}

////////////////////////////////////////////////////////////////
// Class Draw
////////////////////////////////////////////////////////////////
cv::Scalar CBlaster::Blaster = cv::Scalar(102, 51, 153);
//shape of missile to be filled circle
void CBlaster::draw(cv::Mat& im)
	{
	cv::circle(im, get_pos(), _radius, Blaster, -1);
	}
