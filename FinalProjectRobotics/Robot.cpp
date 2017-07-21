

#include "Robot.h"

Robot::Robot(Hamster* hamster) {
	this->hamster=hamster;
	updateRobotPosition();
}

 /*
  * calculates the delta between current x value and previous x value
  * */
double Robot::deltaX() const {
	return currentX - prevX;
}

/*
 * calculate the delta between current Y value and previous Y value
 * */
double Robot::deltaY() const {
	return currentY - prevY;
}

 /*
  * calculates the delta between current angle value and previous angle value
  * */
double Robot::deltaAngle() const {
	return currentAngle - prevAngle;
}

/*
 * Update Robot Variables
 * */
void Robot::updateRobotPosition() {

	//get starting position from the robot
	Pose pose = hamster->getPose();
	prevX = currentX;
	prevY = currentY;
	prevAngle = currentAngle;
	currentX = pose.getX();
	currentY = pose.getY();
	currentAngle = pose.getHeading();
}


Robot::~Robot() {}
