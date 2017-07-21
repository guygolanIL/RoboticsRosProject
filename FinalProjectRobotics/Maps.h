
#ifndef MAPS_H_
#define MAPS_H_

#include <HamsterAPIClientCPP/Hamster.h>
#include <iostream>
#include <vector>
#include "Particle.h"
#include "Utils.h"
using namespace std;
using namespace HamsterAPI;
#define MIN_BLUE_BELIEF 0.5
#define TOP_PARTICALES 5

/*
 * utils - object which do conversions between matrix values and and slam map values
 * og - Occupancy grid object
 * width - map's width
 * height - map's height
 * worldMat - a cv::Mat object, this object will display the slam map and the particles
 * hamster - Hamster Object
 *
 * */

class Maps {

private:
	Utils* utils;
	OccupancyGrid og;
	int width;
	int height;
	cv::Mat matrix;
	Hamster* hamster;

public:

	Maps(OccupancyGrid og,Hamster* hamster ,  Utils* utils);


	void buildMap();


	void showMap();


	bool drawPraticles(vector<Particle*> par);


	void fillBlueParticle(int i,int j);


	void fillGreenParticle(int i,int j);


	void fillRedParticle(int i,int j);


	void paintBlueParticle(int i,int j);


	void paintGreenParticle(int i,int j);


	void paintRedParticle(int i,int j);


	virtual ~Maps();
};

#endif /* MAPS_H_ */
