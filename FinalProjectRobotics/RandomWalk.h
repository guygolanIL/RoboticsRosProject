#include <HamsterAPIClientCPP/Hamster.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

#ifndef RANDOMWALK_H_
#define RANDOMWALK_H_


/*
 * hamster - Hamster object
 * scan - Lidar scan object to check for obstacles
 * moveBack - boolean indicates that the robot is moving back
 * moveLeft - boolean indicates that the robot is moving Left
 * moveRight  boolean indicates that the robot is moving Right
 * */
class RandomWalk{
private:
	HamsterAPI::Hamster * hamster;
	HamsterAPI::LidarScan scan;
	bool moveBack;
	bool moveLeft;
	bool moveRight;
public:
	RandomWalk();
	RandomWalk(HamsterAPI::Hamster * hamster);


	virtual void start(HamsterAPI::LidarScan scan);


	bool isFrontFree();


	bool isLeftFree();


	bool isRightFree();


	bool isBackFree();


	void moveForward();


	void turnLeft();


	void turnRight();


	void moveBackwards();


	void stopMoving();


	void turn();


	void getScansBetween(double min, double max, std::vector<double> & distances);


	bool willCollide(std::vector<double> distances, int angle_from_center);


	void moveLeftBack();


	void moveRightBack();


	virtual ~RandomWalk();
};

#endif /* RANDOMWALK_H_ */
