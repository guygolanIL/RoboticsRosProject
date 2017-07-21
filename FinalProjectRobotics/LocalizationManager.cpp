

#include "LocalizationManager.h"

//Define number of initial particle

#define NUM_OF_PARTICALS 500



LocalizationManager::LocalizationManager(const OccupancyGrid &OccGride, Hamster* Hamster,Utils* utils) :occGride(OccGride),hamster(Hamster),utils(utils){


}

void LocalizationManager::update(double radius, double deltaAngle){
	Location* parLoc;
	int i = 0;
	int j = 0;
	begin = particles.begin();
	while(begin != particles.end()){
		parLoc = (*begin)->getLocation();
//		double radius = sqrt(deltaX*deltaX + deltaY*deltaY);
		parLoc->setX(parLoc->getX() + radius*cos(parLoc->getYaw() * DEG2RAD));
		parLoc->setY(parLoc->getY() + radius*sin(parLoc->getYaw() * DEG2RAD));
		double newYaw =(parLoc->getYaw()+deltaAngle);

		i = utils->fromYToI(parLoc->getY());
		j = utils->fromXToJ(parLoc->getX());
		parLoc->setYaw(newYaw);
		(*begin)->setBel(calculateBelif(*begin));

		if(occGride.getCell(i, j) != CELL_FREE) {
			if ((*begin)->belief < 0.5 ) {
				setRandomPartical(*begin);
			}
		}

		begin++;
	}
	getRandomGoodParticles();
}

void LocalizationManager::getRandomGoodParticles(){
	int k=0;
	int i,j=0;
	ParticleSorter comparator;
	sort(particles.begin(), particles.end(), comparator);
	for(int m = NUM_OF_PARTICALS-1; m > NUM_OF_PARTICALS - 200 - 1 ;m--){
		int whell = selectParticleUsingRouletteWheel();
		do{
			int angle = rand() % 360;
			int radius = RADIUS - (rand() % RADIUS*2);
			j = utils->fromXToJ(particles[whell]->getLocation()->getX()) + radius* cos(angle);
			i = utils->fromYToI(particles[whell]->getLocation()->getY()) + radius* sin(angle);
		}while(this->occGride.getCell(i,j) != CELL_FREE);
		particles[k]->getLocation()->setYaw(rand() % 360);
		particles[k]->getLocation()->setX(utils->fromJToX(j));
		particles[k]->getLocation()->setY(utils->fromIToY(i));
		particles[k]->setBel(calculateBelif(particles[k]));
		k++;
	}
}
/*
 * This function create a random partical (according to the CELL FREE) in the SLAM Map
 * */


void LocalizationManager:: setRandomPartical(Particle* partical){
	int i,j = 0;
	do{

		/* J == occupancy grid width  */
		j = rand() % occGride.getWidth();

		/* I == occupancy grid hieght */
		i = rand() % occGride.getHeight();
	}while(occGride.getCell(i , j) != CELL_FREE);
	//while(occGride.getCell(j , i) != CELL_FREE);
	partical->setParLocation(new Location(utils->fromJToX(j),utils->fromIToY(i),rand() % 360));
}

/**
 * Set new NUM_OF_PARTICALS
 */

void LocalizationManager:: initParticals(){
	particles.resize(NUM_OF_PARTICALS);
	for(int i =0 ; i <NUM_OF_PARTICALS ; i++){
		particles[i] = new Particle();
		setRandomPartical(particles[i]);

	}
}
void LocalizationManager::drawPraticls(){

	begin = particles.begin();
	while(begin != particles.end()){
		cout << (*begin)->getBel() <<endl ;
		begin++;
	}
	//sleep(100);
}

double LocalizationManager::calculateBelif(Particle* par){
	int stirkes = 0;
	int failures = 0;
	int pixelX;
	int pixelY;
	unsigned int i;
	LidarScan ld = hamster->getLidarScan();
	double angle;
	double obsX;
	double obsY;
	for(i=0; i < ld.getScanSize(); i++){
		angle = ld.getScanAngleIncrement() * i * DEG2RAD;
		if(ld.getDistance(i) < ld.getMaxRange() - 0.001){
			obsX = par->getLocation()->getX() + ld.getDistance(i) * cos(angle +par->getLocation()->getYaw() * DEG2RAD -180 * DEG2RAD);
			obsY = par->getLocation()->getY() + ld.getDistance(i) * sin(angle +par->getLocation()->getYaw() * DEG2RAD -180 * DEG2RAD);
			pixelX = obsX / occGride.getResolution() + occGride.getWidth() / 2 ;
			pixelY = occGride.getHeight() /2 - obsY / occGride.getResolution();

			if(occGride.getCell(pixelY,pixelX) == CELL_OCCUPIED){
				stirkes++;
			}else{
				failures++;
			}
		}
	}
	return ((double)stirkes / (stirkes +failures )) * 1.3;
}

LocalizationManager::~LocalizationManager() {
}

int LocalizationManager:: selectParticleUsingRouletteWheel(){

	double wheel_location =0;
	double total_weight=0;
	double curr_sum;
	int index=0;
	for (int i = 1 ; i<5 ; i++) {
		total_weight += particles[NUM_OF_PARTICALS-i]->belief;
	}

	wheel_location = (double) (rand() / (double) (RAND_MAX)) *total_weight;
	index=NUM_OF_PARTICALS-1;
	curr_sum = particles[index]->belief;

	while (curr_sum < wheel_location && index > NUM_OF_PARTICALS - 1 - 5 ) {
		index--;
		curr_sum = curr_sum + particles[index]->belief;
	}

	return index;

}
