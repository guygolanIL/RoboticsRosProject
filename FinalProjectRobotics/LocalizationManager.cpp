
#include "LocalizationManager.h"

//Define number of initial particle

#define NUM_OF_PARTICLES 700

LocalizationManager::LocalizationManager(const OccupancyGrid &OccGride,
		Hamster* Hamster, Utils* utils) :
		og(OccGride), hamster(Hamster), utils(utils) {
}

/*
 * This function update particles location according to the movement of the robot(angle and distance)
 * */
void LocalizationManager::update(double radius, double deltaAngle) {
	Location* parLoc;
	int i = 0;
	int j = 0;
	begin = particles.begin();
	while (begin != particles.end()) {
		parLoc = (*begin)->getLocation();

		//updating new location
		parLoc->setX(parLoc->getX() + radius * cos(parLoc->getYaw() * DEG2RAD));
		parLoc->setY(parLoc->getY() + radius * sin(parLoc->getYaw() * DEG2RAD));
		double newYaw = (parLoc->getYaw() + deltaAngle);

		i = utils->fromYToI(parLoc->getY());
		j = utils->fromXToJ(parLoc->getX());
		parLoc->setYaw(newYaw);

		//belief calculation
		(*begin)->setBelief(calculateBelief(*begin));

		//reseting unwanted particles
		if (og.getCell(i, j) != CELL_FREE) {
			if ((*begin)->belief < 0.5) {
				resetParticleLocation(*begin);
			}
		}

		begin++;
	}

	evolutionStep();
}

/*
*Generate new stronger particle instead  of weak particles
*taking the 200 worst particles and reposition them near a random particle
* */
void LocalizationManager::evolutionStep() {
	int k = 0;
	int i, j = 0;
	ParticleSorter comparator;
	sort(particles.begin(), particles.end(), comparator);
	//iterating over 200 worst particles
	for (int m = NUM_OF_PARTICLES - 1; m > NUM_OF_PARTICLES - 200 - 1; m--) {
		int chosenOne = randomizeParticle();
		do {
			int angle = rand() % 360;
			int radius = RADIUS - (rand() % RADIUS * 2);
			j = utils->fromXToJ(particles[chosenOne]->getLocation()->getX())
					+ radius * cos(angle);
			i = utils->fromYToI(particles[chosenOne]->getLocation()->getY())
					+ radius * sin(angle);
		} while (this->og.getCell(i, j) != CELL_FREE);
		//setting m particles to better locations
		particles[k]->getLocation()->setYaw(rand() % 360);
		particles[k]->getLocation()->setX(utils->fromJToX(j));
		particles[k]->getLocation()->setY(utils->fromIToY(i));
		particles[k]->setBelief(calculateBelief(particles[k]));
		k++;
	}
}

/*
 * sets a random new location for a given particle
 * */
void LocalizationManager::resetParticleLocation(Particle* partical) {
	int i, j = 0;

	//randomizing new grid cell
	do {
		j = rand() % og.getWidth();
		i = rand() % og.getHeight();
	} while (og.getCell(i, j) != CELL_FREE);

	partical->setLocation(
			new Location(utils->fromJToX(j), utils->fromIToY(i), rand() % 360));
}

/*
 * initiates NUM_OF_PARTICLES randomly on the map
 * */

void LocalizationManager::initParticals() {
	particles.resize(NUM_OF_PARTICLES);
	for (int i = 0; i < NUM_OF_PARTICLES; i++) {
		particles[i] = new Particle();
		//setting new random location for each particle
		resetParticleLocation(particles[i]);

	}
}

/*
 *  printing all paricles belief
 * */
void LocalizationManager::printPraticlesBelief() {

	begin = particles.begin();
	while (begin != particles.end()) {
		cout << (*begin)->getBelief() << endl;
		begin++;
	}

}

/*
 * calculates the belief of a single particle
 * */
double LocalizationManager::calculateBelief(Particle* par) {
	int hits = 0;
	int misses = 0;
	int pixelX;
	int pixelY;
	unsigned int i;
	LidarScan ld = hamster->getLidarScan();
	double angle;
	double obsX;
	double obsY;
	for (i = 0; i < ld.getScanSize(); i++) {
		angle = ld.getScanAngleIncrement() * i * DEG2RAD;
		if (ld.getDistance(i) < ld.getMaxRange() - 0.001) {
			obsX = par->getLocation()->getX()+ ld.getDistance(i)* cos(angle	+ par->getLocation()->getYaw()* DEG2RAD - 180 * DEG2RAD);
			obsY = par->getLocation()->getY()+ ld.getDistance(i)* sin(angle	+ par->getLocation()->getYaw()* DEG2RAD - 180 * DEG2RAD);
			pixelX = obsX / og.getResolution() + og.getWidth() / 2;
			pixelY = og.getHeight() / 2 - obsY / og.getResolution();

			if (og.getCell(pixelY, pixelX) == CELL_OCCUPIED) {
				hits++;
			} else {
				misses++;
			}
		}
	}
	return ((double) hits/ (hits+ misses)) * 1.3;
}

LocalizationManager::~LocalizationManager() {}

/*
*  selects a random particle
 * */
int LocalizationManager::randomizeParticle() {

	double location = 0;
	double total_weight = 0;
	double curr_sum;
	int index = 0;
	for (int i = 1; i < 5; i++) {
		total_weight += particles[NUM_OF_PARTICLES - i]->belief; //aggregate the total belief of 5 best particles
	}

	location = (double) (rand() / (double) (RAND_MAX)) * total_weight; //randomizing a percentage of the total weight
	index = NUM_OF_PARTICLES - 1;
	curr_sum = particles[index]->belief;

	while (curr_sum < location && index > NUM_OF_PARTICLES - 1 - 5) {
		index--;
		curr_sum = curr_sum + particles[index]->belief;
	}

	return index;

}
