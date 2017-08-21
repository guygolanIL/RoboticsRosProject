
#include <HamsterAPIClientCPP/Hamster.h>
#include <iostream>
#include "LocalizationManager.h"
#include "Robot.h"
#include "RandomWalk.h"
#include "Utils.h"
#include <time.h>

#include "Entities/Maps.h"
using namespace std;
using namespace HamsterAPI;
HamsterAPI::Hamster * hamster;

int main() {
	try {

		hamster = new HamsterAPI::Hamster(1);
		sleep(2);
		Utils* utils = new Utils(hamster);
		LocalizationManager* manager = new LocalizationManager(hamster,utils);
		Robot * robot = new Robot(hamster,manager,utils);
		robot->locator();


	} catch (const HamsterAPI::HamsterError & connection_error) {
		HamsterAPI::Log::i("Client", connection_error.what());
	}

	return 0;

}

