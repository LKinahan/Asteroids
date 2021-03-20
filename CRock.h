////////////////////////////////////////////////////////////////
// CRock.h
// Definintion of class CRock
// Member function are defined in CRock.cpp
// Created March 01, 2021 by Laurel Kinahan 
////////////////////////////////////////////////////////////////
#pragma once
#include "stdafx.h"
#include "CGameObject.h"

/**
* @brief Child class inherits from CGameObject
* to set the position, velocity, color, shape and size of Rocks
* @author Laurel Kinahan
*/
class CRock : public CGameObject {
private:
	static cv::Scalar CRock::rock;

public:
	/**
	* @brief This is the class constructor
	* @param pos point to float conversion to give Rock movement
	* @return Nothing
	*/
	CRock(cv::Point2f pos);

	/**
	* @brief This is the class destructor
	* @param None
	* @return Nothing
	*/
	~CRock(void);

	/**
	* @brief Draws Rock on the created image
	* @param im mat to draw Rock on
	* @return Nothing
	*/
	void draw(cv::Mat& im);
	};