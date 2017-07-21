/*
 * ParticleSorter.h
 *
 *  Created on: Mar 7, 2017
 *      Author: user
 */

#ifndef PARTICLESORTER_H_
#define PARTICLESORTER_H_
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

#endif /* PARTICLESORTER_H_ */
