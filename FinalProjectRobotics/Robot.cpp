
#include "Robot.h"

Robot::Robot(Hamster* a_hamster, LocalizationManager* a_manager, Utils* a_utils){

		srand(time(0));// Initial srand to generate random numbers
		hamster = a_hamster;
		ogrid = hamster->getSLAMMap();



		utils = a_utils;
		gridMap = new Maps(ogrid,hamster , utils);
		manager = a_manager;

		//initial only
		start = std::clock();
		duration = 0;

}

bool Robot::locator()
{

		RandomWalk randWalk(hamster);
		manager->initParticals();

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

				gridMap->drawPraticles(manager->getParticles());

			} catch (const HamsterAPI::HamsterError & message_error) {
				HamsterAPI::Log::i("Client", message_error.what());
				return false;
			}


		}
return true;
}

 Robot::~Robot(){}

