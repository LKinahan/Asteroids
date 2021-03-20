////////////////////////////////////////////////////////////////
// CAsteroid.h
// Definintion of class CBase
// Member function are defined in CCBase.cpp
// Created Feb 09, 2021 by Laurel Kinahan 
////////////////////////////////////////////////////////////////

#pragma once
#include "stdafx.h"
#include "CBase4618.h"
#include "CShip.h"
#include "CBlaster.h"
#include "CRock.h"

/**
* @brief A mini game of Asteroids
* This class inherits from CBase4618 to update and draw a game using open cv
* @author Laurel Kinahan
*/
class CAsteroid : public CBase4618 {
private:

public:
	/**
	* @brief This is the class constructor
	* @param None
	* @return None
	*/
	CAsteroid(int comport = 3);

	/**
	* @brief This is the class destructor
	* @param None
	* @return None
	*/
	~CAsteroid();

	/**
	* @brief Start Update() and draw() and loop them
	* @param none
	* @return none
	*/
	void run();

	/**
	* @brief Update will do all the assignings and instantiating for the game
	* user input from joysitck, score handling etc
	* @param none
	* @return none
	*/
	void update();

	/**
	* @brief Draw is in charge of rendering all objects that need to be displayed
	* paddles, ball, text etc
	* @param none
	* @return none
	*/
	void draw();

	/**
	* @brief Reset is charge of resetting to the intial conditions
	* @param none
	* @return none
	*/
	void reset();

	/**
	* @brief Backgound is charge of rendering backdrop for game
	* @param none
	* @return image
	*/
	void Background();

	//incluce object in minigame
	CShip ship; ///< include CShip in rendering
	std::vector <CRock> rocks; ///< vector to include Rock objects in rendering
	std::vector <CBlaster> blaster; ///< vector to include blaster objects in rendering
	 
	//flags
	bool blaster_flag; ///< uses digital input from Button to determine if missile should fire
	bool reset_flag; ///< set to reset game
	bool game_over; ///< if Player lives = 0 game_over is true, else false

	//Canvas variables
	cv::Size mCanvas_size; ///< X and Y dimensions for canvas
	cv::Size textsize; ///< text size for putText
	cv::Scalar red; ///< Red color for draw
	cv::Scalar green; ///< Green color for draw
	cv::Scalar aqua; ///< Aqua color for draw
	cv::Scalar coral; ///< Coral color for draw

	//other variables
	int player_score; ///< keeps track of number of asteroids destroyed
	double blaster_time_1; ///< variable to hold blaster time
	double blaster_time_2; ///< variable to hold blaster time
	double delta_blaster_time; ///< variable to hold change in blaster time 
	double blaster_fire_time; ///< variable to hold blaster firing time
};
