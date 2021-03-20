////////////////////////////////////////////////////////////////
// CBase4618.h
// Definintion of class CBase
// Member function are defined in CCBase.cpp
// Created Feb 09, 2021 by Laurel Kinahan 
////////////////////////////////////////////////////////////////
#pragma once

#include "stdafx.h"

#include "CControl.h"
#include <Windows.h>
#include <iostream>

using namespace std;

#define Window_Y 0.6
#define Window_X 0.4
#define BUTTON1 33
#define BUTTON2 32

/**
* @brief Base Class for Update, Draw, and Run functions
* This class communcates between CControl and mini games
* @author Laurel Kinahan
*/
class CBase4618 {
private:

public:
	cv::Mat mCanvas; ///< Matrix canvas to draw on
	CControl mCControl; ///< CControl gamepad object

	/** 
	* @brief This is the class constructor
	* @param None
	* @return None
	*/
	CBase4618();

	/** 
	* @brief This is the class destructor
	* @param None
	* @return None
	*/	
	~CBase4618();

	/**
	* @brief Updates internal variables
	* @param none
	* @return none
	*/
	virtual void update();

	/**
	* @brief Draws on the created image
	* @param None
	* @return None
	*/
	virtual void draw();

	/**
	* @brief Initializes the COM port
	* @param nothing to receive
	* @return nothing to return
	*/
	void run();
	};