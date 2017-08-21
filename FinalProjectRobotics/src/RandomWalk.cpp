#include "RandomWalk.h"

RandomWalk::RandomWalk(HamsterAPI::Hamster * hamster) {
	this->hamster = hamster;
	moveBack = false;
	moveLeft = false;
	moveRight = false;
}

RandomWalk::RandomWalk(){

}

RandomWalk::~RandomWalk() {}

/*
 *moving the robot forward unless forward isn't free
 * */
void RandomWalk::start(HamsterAPI::LidarScan scan)
{
	this->scan = scan;
	if (isFrontFree() && (!moveBack) && (!moveLeft) && (!moveRight)){
		moveForward();
	}
	else{
		turn();
	}
}

/*
 *Checks if moving forward is available
 * */
bool RandomWalk::isFrontFree() {
	// Degrees : [120, 240]

	std::vector<double> distances;

	getScansBetween(120, 240, distances);

	return !willCollide(distances, 40);
}

/*
 *Checks if moving Left is available
 * */
bool RandomWalk::isLeftFree() {
	// Degrees : [240,300]

	std::vector<double> distances;

	getScansBetween(240, 300, distances);

	return !willCollide(distances, 40);
}

/*
 *Checks if moving Right is available
 **/
bool RandomWalk::isRightFree() {
	// Degrees : [60, 120]

	std::vector<double> distances;

	getScansBetween(60, 120, distances);

	return !willCollide(distances, 40);
}

/*
 *Checks if moving Back is available
 * */
bool RandomWalk::isBackFree() {
	// Degrees : [315,360], [0, 45]

	std::vector<double> distances;

	getScansBetween(315, 360, distances);
	getScansBetween(0, 45, distances);

	return !willCollide(distances, 40);
}

/*
 * Moves the robot Forward
 * */
void RandomWalk::moveForward() {
	this->hamster->sendSpeed(0.4, 0.0);
}

/*
 * Turning Left
 * */
void RandomWalk::turnLeft() {
	this->moveLeft = true;
	if(isFrontFree())
		this->moveLeft = false;
	else if(isLeftFree())
		this->hamster->sendSpeed(0.4, 45.0);
	else{
		this->moveLeft = false;
		return;
	}
}

/*
 * Turning right
 * */
void RandomWalk::turnRight() {
	this->moveRight = true;
	if(isFrontFree())
		this->moveRight = false;
	else if(isRightFree())
		this->hamster->sendSpeed(0.4, -45.0);
	else{
		this->moveRight = false;
		return;
	}
}

/*
* Moving backwards - according to available place
* */
void RandomWalk::moveBackwards() {
	this->moveBack = true;
	if(isLeftFree()){
		this->moveBack = false;
		moveLeftBack();
	}
	else if(isRightFree()){
		this->moveBack = false;
		moveRightBack();
	}
	else if (isBackFree())
		this->hamster->sendSpeed(-0.4, 0.0);
	else{
		this->moveBack = false;
		return;
	}
}

/*
* Moving left in Right angle
* */
void RandomWalk::moveRightBack(){
	for (int i = 0; i < 150000; i++) {
		this->hamster->sendSpeed(-0.4, -45.0);
	}
}

/*
* Moving back in left angle
* */
void RandomWalk::moveLeftBack(){
	for (int i = 0; i < 150000; i++) {
		this->hamster->sendSpeed(-0.4, 45.0);
	}
}

/*
* stop moving
* */
void RandomWalk::stopMoving() {
	int i = 0;
	while(i<300000)
	{
		this->hamster->sendSpeed(0.0, 0.0);
		i++;
		printf("%d\n",i);
	}
}

/*
* get all scans between specific range
* */
void RandomWalk::getScansBetween(double min, double max, std::vector<double> & distances) {

	for (size_t i = 0; i < this->scan.getScanSize(); i++) {
		double degree = this->scan.getScanAngleIncrement() * i;
		if (degree >= min && degree <= max)
			distances.push_back(this->scan.getDistance(i));
	}
}

/*
* check if the robot is going to hit and obstacle according the vector of distances
* */
bool RandomWalk::willCollide(std::vector<double> distances, int angle_from_center) {

	int collisions = 0;

	for (size_t i = distances.size() / 2 - angle_from_center / 2;
			i < distances.size() / 2 + angle_from_center / 2; i++)
		if (distances[i] < this->scan.getMaxRange() / 6.0)
			collisions++;

	return collisions >= angle_from_center / 6.0;
}

void RandomWalk::turn(){
	bool leftFree = isLeftFree();
	bool rightFree = isRightFree();
	int randNum;

	if(this->moveBack){
		moveBackwards();
	}
	else if(this->moveLeft){
		turnLeft();
	}
	else if(this->moveRight){
		turnRight();
	}
	else if(leftFree && rightFree){//random turn
		randNum = rand()%2;
		if(randNum == 0)
			turnRight();
		else
			turnLeft();
	}
	else if(!(leftFree || rightFree)){//backwards
		moveBackwards();
	}
	else if(leftFree){//left
		turnLeft();
	}
	else{//right
		turnRight();
	}
}
