

#ifndef ROBOT_H_
#define ROBOT_H_
#include <iostream>
#include <HamsterAPIClientCPP/Hamster.h>
#include <iostream>
#include "Maps.h"
#include "LocalizationManager.h"
#include "RandomWalk.h"
#include "Utils.h"
#include <time.h>
#include "time.h"
using namespace HamsterAPI;
using namespace std;


class Robot {
	Hamster* hamster;
	OccupancyGrid ogrid;
	LocalizationManager* manager;
	Utils* utils;  // Occupancy Grid <-> Matrix coordinates transformer
	Maps* gridMap;

	/*clock and duration variable take care of the robot movement (the robot change movement every 0.5 seconds ) */
	std::clock_t start;
	double duration;

public:


	Robot(Hamster* hamster, LocalizationManager* a_manager, Utils* a_utils);

	bool locator();

	virtual ~Robot();
};

#endif /* ROBOT_H_ */


