
#ifndef Particle_H_
#define Particle_H_
#include <HamsterAPIClientCPP/Hamster.h>
#include <iostream>
#include "Location.h"

#define NUM_OF_CHILD 20
#define MAX_RANGE 50

using namespace std;
using namespace HamsterAPI;



/*
 * location - particle location
 * belief - particle belief
 * */


class Particle {

private:
	Location* location;


public:

	double belief;

	Particle();

	Particle(double x, double y,double bel,double angle);

	double getBelief() const {return belief;}

	Particle* createSon(double x, double y,double bel,double angle);

	double getBel() const;

	void setBel(double bel);

	Location* getLocation() ;

	void setParLocation( Location* parLocation);

	virtual ~Particle();


};

#endif /* Particle_H_ */
