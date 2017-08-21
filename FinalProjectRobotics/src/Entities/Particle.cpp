

#include "Particle.h"

Particle:: Particle(){
	location = NULL;
	belief = 0;
}

/*
*Constructor for particle class must initialize with all the particle vars
* */
Particle::Particle(double x, double y ,double bel, double angle) {
	this->location = new Location(x,y,angle);
	this->belief = bel;

}

/*
 * create new particle and return pointer to it
 * */
Particle* Particle::createSon(double x, double y,double bel,double angle){

	return new Particle(x,y,bel,angle);
}


double Particle::getBel() const {
	return belief;
}

void Particle::setBelief(double bel) {
	this->belief = bel;
}

 Location* Particle::getLocation()  {
	return location;
}

void Particle::setLocation( Location* particleLocation) {
	this->location = particleLocation;
}

Particle::~Particle() {}



