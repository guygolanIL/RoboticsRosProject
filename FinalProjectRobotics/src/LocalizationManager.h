

#ifndef LOCALIZATIONMANAGER_H_
#define LOCALIZATIONMANAGER_H_

#include <HamsterAPIClientCPP/Hamster.h>
#include <iostream>

#include <vector>
#include "Utils.h"
#include <algorithm>

#include "Entities/Maps.h"
#include "Entities/Particle.h"
#include "Entities/ParticleSorter.h"
#define MAX_TH  0.002
#define MIN_TH  0.002
#define NUM_OF_CHILD 20
#define MAX_RANGE 50



using namespace std;
using namespace HamsterAPI;

#define RADIUS 7


class LocalizationManager {


private:
	Utils* utils;
	vector<Particle*> particles;
	vector<Particle*>::iterator begin;
	OccupancyGrid og;
	Hamster* hamster;


public:

	LocalizationManager(Hamster* Hamster,Utils* utils);

	void update(double radius, double deltaAngle);

	void resetParticleLocation(Particle* partical);

	void initParticals();

	void printPraticlesBelief();

	double calculateBelief(Particle* par);

	virtual ~LocalizationManager();

	int randomizeParticle();


	void evolutionStep();

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
