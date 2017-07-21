

#ifndef ROBOT_H_
#define ROBOT_H_
#include <iostream>
#include <HamsterAPIClientCPP/Hamster.h>
#include "time.h"
using namespace HamsterAPI;
using namespace std;


class Robot {
	Hamster* hamster;
	double currentX, currentY,currentAngle;
	double prevX,prevY,prevAngle;

public:


	Robot(Hamster* hamster);


	void updateRobotPosition();


	double deltaX() const;

	double deltaAngle() const;

	double deltaY() const;

	virtual ~Robot();
};

#endif /* ROBOT_H_ */
