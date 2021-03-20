////////////////////////////////////////////////////////////////
// CShip.h
// Definintion of class CShip
// Member function are defined in CShip.cpp
// Created March 01, 2021 by Laurel Kinahan 
////////////////////////////////////////////////////////////////
#pragma once
#include "stdafx.h"
#include "CGameObject.h"
#include "CBase4618.h"

/**
* @brief Child class inherits from CGameObject
* to set the position, velocity, number of lives, color, shape and size of Ship
* @author Laurel Kinahan
*/
class CShip : public CGameObject {
private:
	static cv::Scalar ship;

public:
	/**
	* @brief This is the class constructor
	* @param None
	* @return Nothing
	*/
	CShip();

	/**
	* @brief This is the class destructor
	* @param None
	* @return Nothing
	*/
	~CShip();

	/**
	* @brief Draws Ship on the created image
	* @param im mat to draw Ship on
	* @return Nothing
	*/
	void draw(cv::Mat& im);
	};