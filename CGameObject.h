////////////////////////////////////////////////////////////////
// CGameObject.h
// Definintion of class CGameObject
// Member function are defined in CGameObject.cpp
// Created March 01, 2021 by Laurel Kinahan 
////////////////////////////////////////////////////////////////
#pragma once
#include "stdafx.h"

/**
* @brief Base class for objects within mini games
* 
* @author Laurel Kinahan
*/
class CGameObject {
protected:
	cv::Point2f position; ///< point to float conversion for object position
	cv::Point2f velocity; ///< point to float conversion for object velocity
	int _radius; ///< variable to set radius of game objects
	int _lives; ///< variable to set number of lives of game objects 
	double current_time; ///< variable to hold current time 
	double delta_time; ///< variable to hold change in time
	double prev_time; ///< variable to hold previous time

public:
	/**
	* @brief Constructs position and velocity for game components to move
	* @param none
	* @return none
	*/
	void move();

	/**
	* @brief Check for object collisions
	* @param obj object to compare with 
	* @return true if collision detected, else false
	*/
	bool collide(CGameObject& obj);

	/**
	* @brief Check for object collision with wall
	* @param board size of mat
	* @return true if collision detected, else false
	*/
	bool collide_wall(cv::Size board);

	/**
	* @brief decrements _lives of objects
	* @param none
	* @return none
	*/
	void hit();

	/**
	* @brief _lives getter
	* @param none
	* @return _lives
	*/
	int get_lives() { return _lives; }

	/**
	* @brief _lives setter
	* @param none
	* @return _lives
	*/
	void set_lives(int lives) { _lives = lives; }

	/**
	* @brief Sets the position of the ship object to match the joystick inputs
	* @param pos point
	* @return pos vector
	*/
	void set_pos(cv::Point2f pos) { position = pos; }

	/**
	* @brief position getter for each game object
	* @param none
	* @return position
	*/
	cv::Point2f get_pos() { return position; }

	/**
	* @brief draws an object on the cv image
	* @param im mat to draw objects on
	* @return none
	*/
	virtual void draw(cv::Mat& im);
	};