/*
 * HamsterAPIClientSimpleBehaviourExample.cpp
 *
 *  Created on: Aug 10, 2016
 *      Author: ofir
 */

#include <HamsterAPIClientCPP/Hamster.h>
#include <iostream>
#include "Maps.h"
#include "LocalizationManager.h"
#include "Robot.h"
#include "RandomWalk.h"
#include "Utils.h"
#include <time.h>
using namespace std;
using namespace HamsterAPI;
HamsterAPI::Hamster * hamster;

int main() {
	try {

		Utils* utils; // Occupancy Grid <-> Matrix coordinates transformer
		srand(time(0));// Initial srand to generate random numbers
		hamster = new HamsterAPI::Hamster(1);

		sleep(2);

		OccupancyGrid ogrid = hamster->getSLAMMap();

		/*clock and duration variable take care of the robot movement (the robot change movement every 0.5 seconds ) */
		std::clock_t start;
		double duration;

		utils = new Utils(ogrid.getHeight(),ogrid.getWidth(),ogrid.getResolution());


		Maps* gridMap = new Maps(ogrid,hamster , utils);

		LocalizationManager* manager = new LocalizationManager(ogrid, hamster,utils);

		RandomWalk randWalk(hamster);

		manager->initParticals();

		bool isStop = false;

		gridMap->buildMap(); 	//builds initial map


		while (hamster->isConnected()) {
			try {
				gridMap->showMap();
				start = std::clock();

				/*loop which run 0.5 seconds approximately */
				do{
					LidarScan scan = hamster->getLidarScan();
					randWalk.start(scan);
					duration = ( std::clock() - start ) / (float) CLOCKS_PER_SEC;
				}while(duration<0.5);


				Speed s = hamster->getSpeed();
				float speed = s.getVelocity();
				float wheelsAngle = s.getWheelsAngle();


				/*this  section update the particles location according to the robot estimated movement */

				if(speed>0)
				{
					if(wheelsAngle>0)//left and forward
					{
						manager->update(0.01,45);

					}
					else if(wheelsAngle==0)
					{
						manager->update(0.16,0);

					}
					else if(wheelsAngle<0)//right and forward
					{
						manager->update(0.01,-45);

					}
				}else{
					if(wheelsAngle>0)//left and backwards
					{
						manager->update(-0.01,45);

					}
					else if(wheelsAngle==0)
					{
						manager->update(-0.16,0);

					}
					else if(wheelsAngle<0)//right and backwards
					{
						manager->update(-0.01,-45);

					}
				}

				isStop = gridMap->drawPraticles(manager->getParticles());

			} catch (const HamsterAPI::HamsterError & message_error) {
				HamsterAPI::Log::i("Client", message_error.what());
			}


		}

	} catch (const HamsterAPI::HamsterError & connection_error) {
		HamsterAPI::Log::i("Client", connection_error.what());
	}

	return 0;

}

