

#ifndef LOCALIZATIONMANAGER_H_
#define LOCALIZATIONMANAGER_H_

#include <HamsterAPIClientCPP/Hamster.h>
#include <iostream>

#include "Particle.h"
#include "Maps.h"
#include <vector>
#include "Utils.h"
#include <algorithm>
#include "ParticleSorter.h"
#define MAX_TH  0.002
#define MIN_TH  0.002
#define NUM_OF_CHILD 20
#define MAX_RANGE 50



using namespace std;
using namespace HamsterAPI;

#define RADIUS 7


/*
 * @param utils
 * @param particles - A vector of particles
 * @param begin  - An Iterator on the particles vector
 * @param occGride
 * @param hamster
 * */

class LocalizationManager {

private:
	Utils* utils;
	vector<Particle*> particles;
	vector<Particle*>::iterator begin;
	const OccupancyGrid & occGride;
	Hamster* hamster;


public:

	/*
	 * Constructor for Location manager class
	 * */
	LocalizationManager(const OccupancyGrid & OccGrid, Hamster* Hamster,Utils* utils);

	/*
	 * This function update particles location according to the movement of the robot(angle and distance)
	 * */
	void update(double radius, double deltaAngle);

	/*
	 *This function generate single random particle
	 * */
	void setRandomPartical(Particle* partical);

	/*
	 * This function initiate NUM_OF_PARTICLES randomly on the map
	 * */
	void initParticals();

	/*
	 * This function it a service function printing all paticles belif
	 * */
	void drawPraticls();

	/*
	 * This function calculate the belif of a single particle
	 * */
	double calculateBelif(Particle* par);

	/*
	 *
	 * */
	virtual ~LocalizationManager();

	/*
	 * This function select a random particle using a Roulette  wheel selection algorithm
	 * */
	int selectParticleUsingRouletteWheel();

	/*
	 *Generate new stronger particle instead  of weak particle
	 * */
	void getRandomGoodParticles();

	/*
	 * getter of particles vector
	 * */
	 vector<Particle*> getParticles()  {
		return particles;
	}

	 /*
	  * setter of particles vector
	  * */
	void setParticles( vector<Particle*>& particles) {
		this->particles = particles;
	}


};

#endif /* LOCALIZATIONMANAGER_H_ */
