/*
 * utils.h
 *
 *  Created on: Mar 7, 2017
 *      Author: user
 */

#ifndef UTILS_H_
#define UTILS_H_

class Utils {

	double height;
	double width;
	double resolution;
public:


	Utils(int height, int width, double resolution);

	double fromJToX(double j);

	double fromIToY(double i);

	double fromYToI(double y);

	double fromXToJ(double x);
	virtual ~Utils();


};

#endif /* UTILS_H_ */
