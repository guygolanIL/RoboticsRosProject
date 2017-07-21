
#include "Utils.h"

/*
 *
 * height - Occupancy grid height
 * width - Occupancy grid width
 * resolution - Occupancy grid resolution
 *
 */
Utils::Utils(int height, int width, double resolution): resolution(resolution) {

	this->height = (double)height;
	this->width = (double)width;

}
 /*
  * this function gets an occupancy grid j and returns the matching x
  */
double Utils::fromJToX(double j){
	return (j - width / 2)* resolution;
}

 /*
  *  this function gets an occupancy grid i and returns the matching y
  */
double Utils::fromIToY(double i){
	return (height / 2 - i) * resolution;
}

/*
 * this function gets a matrix y and returns the matching i
 */
double Utils::fromYToI(double y){
	return height / 2 - y / resolution;
}

/*
 * this function gets a matrix x and returns the matching j
 */
double Utils::fromXToJ(double x){
	return x / resolution + width / 2 ;
}
Utils::~Utils() {}

