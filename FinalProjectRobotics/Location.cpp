
#include "Location.h"

Location::Location(double x, double y,double yaw) {
	this->x = x;
	this->y = y;
	this->yaw = yaw;

}


double Location::getYaw()  {
	return yaw;
}

void Location::setYaw(double yaw) {
	this->yaw = yaw;
}

double Location::getX()  {
	return x;
}

void Location::setX(double x) {
	this->x = x;
}

double Location::getY()  {
	return y;
}

void Location::setY(double y) {
	this->y = y;
}
Location::~Location() {}
