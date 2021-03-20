////////////////////////////////////////////////////////////////
// CBase.cpp for ELEX 4618
// Member function definitions for class CBase that 
//     define canvas for basic games
// Created Feb 27, 2021 by Laurel Kinahan 
////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "CAsteroid.h"
#include "CGameObject.h"

#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/opencv.hpp"

using namespace std;


////////////////////////////////////////////////////////////////
// Class constructor
////////////////////////////////////////////////////////////////
CAsteroid::CAsteroid(int comport)
{
	mCControl.init_com(comport);
	mCanvas_size = cv::Size(1000, 800);
	mCanvas = Mat(mCanvas_size, CV_8UC3, Scalar(128, 128, 128));
	blaster_fire_time = 0.1;
	reset();
}

////////////////////////////////////////////////////////////////
// Class destructor
////////////////////////////////////////////////////////////////
CAsteroid::~CAsteroid()
{

}

////////////////////////////////////////////////////////////////
// Class run
////////////////////////////////////////////////////////////////
void CAsteroid::run()
{
	srand(cv::getTickCount());
	double time1 = cv::getTickCount(), time2 = cv::getTickCount(), delta_time;
	do
	{
		time1 = cv::getTickCount();
		delta_time = (time1 - time2) / cv::getTickFrequency();

		if (delta_time > rand() / 10000)
		{
			CRock temp_rock(ship.get_pos());
			rocks.push_back(temp_rock);
			time2 = cv::getTickCount();
		}
		update();
		draw();
	}
	while (cv::waitKey(1) != 'q');
}

////////////////////////////////////////////////////////////////
// Class update
////////////////////////////////////////////////////////////////
void CAsteroid::update()
{
	// Move ship according to joystick input
	float joy_x, joy_y;
	joy_x = mCControl.get_analog(2);
	joy_y = mCControl.get_analog(26);

	// Ship bounded by vertical window dimensions
	if (joy_x > Window_Y)
	{
		ship.set_pos(cv::Point(ship.get_pos().x + 15, ship.get_pos().y));
		if (ship.get_pos().x + 10 > 1000)
			ship.set_pos(cv::Point(1000, ship.get_pos().y));
	}
	else if (joy_x < Window_X)
	{
		ship.set_pos(cv::Point(ship.get_pos().x - 15, ship.get_pos().y));
		if (ship.get_pos().x - 10 < 0)
			ship.set_pos(cv::Point(0, ship.get_pos().y));
	}

	// Ship bounded by horizontal window dimensions
	if (joy_y > Window_Y)
	{
		ship.set_pos(cv::Point(ship.get_pos().x, ship.get_pos().y - 15));
		if (ship.get_pos().y - 10 < 0)
			ship.set_pos(cv::Point(ship.get_pos().x, 0));;
	}
	else if (joy_y < Window_X)
	{
		ship.set_pos(cv::Point(ship.get_pos().x, ship.get_pos().y + 15));
		if (ship.get_pos().y + 10 > 800)
			ship.set_pos(cv::Point(ship.get_pos().x, 800));
	}

	// Fire blasters if button pressed/held
	// Debounce button by setting max number of blaster fires per second
	blaster_time_1 = cv::getTickCount();
	delta_blaster_time = (blaster_time_1 - blaster_time_2) / cv::getTickFrequency();

	if (mCControl.get_button(BUTTON2) == true && delta_blaster_time > blaster_fire_time)
	{
		blaster_time_2 = cv::getTickCount();
		blaster_flag = true;
		CBlaster temp_blaster(ship.get_pos());
		blaster.push_back(temp_blaster);
	}
	else
		blaster_flag = false;

	// Move all blasters and rocks
	// Blaster and rocks can leave the window dimensions 
	for (int i = 0; i < blaster.size(); i++)
	{
		blaster[i].move();
		if (blaster[i].collide_wall(mCanvas_size) == true)
			blaster[i].hit();
	}

	for (int i = 0; i < rocks.size(); i++)
	{
		rocks[i].move();
		if (rocks[i].collide_wall(mCanvas_size) == true)
			rocks[i].hit();
	}

	// Detect collision between blasters/rocks and ship/rocks
	for (int i = 0; i < rocks.size(); i++)
	{
		for (int j = 0; j < blaster.size(); j++)
		{
			if (blaster[j].collide(rocks[i]) == true)
			{
				rocks[i].hit();
				blaster[j].hit();
				player_score += 1;
			}
		}
		if (rocks[i].collide(ship) == true)
		{
			ship.hit();
			rocks[i].hit();
		}
	}

	// Remove objects from canvas with 0 life
	for (int i = 0; i < blaster.size(); i++)
	{
		if (blaster[i].get_lives() <= 0)
			blaster.erase(blaster.begin() + i);
	}
	for (int i = 0; i < rocks.size(); i++)
	{
		if (rocks[i].get_lives() <= 0)
			rocks.erase(rocks.begin() + i);
	}
	if (ship.get_lives() <= 0)
		game_over = true;

	// Button 1 actitvates reset flag
	if (mCControl.get_button(BUTTON1) == true)
	{
		reset_flag = true;
		reset();
	}
	else
		reset_flag = false;
}

////////////////////////////////////////////////////////////////
// Class draw
////////////////////////////////////////////////////////////////
void CAsteroid::draw()
{
	//declare colors
	red = Scalar(0, 0, 255);
	green = Scalar(0, 255, 0);
	aqua = Scalar(255, 255, 0);
	coral = Scalar(255, 0, 255);

	Background();
	mCanvas = cv::Mat::zeros(mCanvas_size, CV_8UC3);
	ship.draw(mCanvas);
	// continuously add more blasters to canvas
	for (int i = 0; i < blaster.size(); i++)
		blaster[i].draw(mCanvas);
	// continuously add more asteroids to canvas
	for (int i = 0; i < rocks.size(); i++)
		rocks[i].draw(mCanvas);

	// print on console when blaster fired and when reset is set
	if (blaster_flag == true)
		cout << "Fire blaster!" << endl;
	if (reset_flag == true)
		cout << "Reseting game" << endl;

	// header tells number of asteroids destroyed and number of lives left
	// print out of number of lives changes color based on lives left
	putText(mCanvas, "Astroids Destroyed: " + to_string(player_score), cv::Point(5, 25), cv::FONT_HERSHEY_PLAIN, 2, coral, 1);
	if (ship.get_lives() >= 4)
		putText(mCanvas, "Lives Left: " + to_string(ship.get_lives()), cv::Point(750, 25), cv::FONT_HERSHEY_PLAIN, 2, green, 1);
	else
		putText(mCanvas, "Lives Left: " + to_string(ship.get_lives()), cv::Point(750, 25), cv::FONT_HERSHEY_PLAIN, 2, red, 2);

	// clear screen when no lives left
	if (game_over == true)
	{
		mCanvas = cv::Mat::zeros(mCanvas_size, CV_8UC3);
		putText(mCanvas, "Game over!", cv::Size(300, 300), cv::FONT_HERSHEY_PLAIN, 4, aqua, 2);
		waitKey(100);
		putText(mCanvas, "Asteroids Destroyed: " + to_string(player_score), cv::Size(100, 400), cv::FONT_HERSHEY_PLAIN, 4, aqua, 2);
		putText(mCanvas, "Reset to play again", cv::Size(300, 600), cv::FONT_HERSHEY_PLAIN, 2, aqua, 2);
	}

	// print game to declared canvas
	imshow("Asteroid", mCanvas);
}

////////////////////////////////////////////////////////////////
// Class reset
////////////////////////////////////////////////////////////////
void CAsteroid::reset()
{
	game_over = false;
	player_score = 0;
	ship.set_lives(10);
	ship.set_pos(cv::Point2f(500, 600));
	blaster.clear();
	rocks.clear();
}

////////////////////////////////////////////////////////////////
// Class Background
////////////////////////////////////////////////////////////////
void CAsteroid::Background()
{
	Mat im;
	im = imread("nasastars.jpg");
	cv::resize(im, mCanvas, mCanvas_size);
}

