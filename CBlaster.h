////////////////////////////////////////////////////////////////
// CBlaster.h
// Definintion of class CBlaster
// Member function are defined in CBlaster.cpp
// Created March 01, 2021 by Laurel Kinahan 
////////////////////////////////////////////////////////////////
#pragma once
#include "stdafx.h"
#include "CGameObject.h"

/**
* @brief Child class inherits from CGameObject 
* to set the position, velocity, color, shape and size of Blasters
* @author Laurel Kinahan
*/
class CBlaster : public CGameObject {
private:
	static cv::Scalar Blaster;

public:
	/**
	* @brief This is the class constructor
	* @param pos point to float conversion to give Blaster movement
	* @return None
	*/
	CBlaster(cv::Point2f pos);

	/**
	* @brief This is the class destructor
	* @param None
	* @return None
	*/
	~CBlaster();

	/**
	* @brief Draws Blaster on the created image
	* @param im mat to draw Missile on
	* @return None
	*/
	void draw(cv::Mat& im);
	};