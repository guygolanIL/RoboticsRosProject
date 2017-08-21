
#ifndef ENTITIES_PARTICLESORTER_H_
#define ENTITIES_PARTICLESORTER_H_
#include "Particle.h"
class ParticleSorter {
public:
	ParticleSorter();
	virtual ~ParticleSorter();
	/*
	 * Object function of the particle class (enable to compare between two particals by their belif )
	 * */
	bool operator() (const Particle*  p1,const  Particle* p2){
		return p1->getBel() < p2->getBel();
	}
};

#endif /* ENTITIES_PARTICLESORTER_H_ */
