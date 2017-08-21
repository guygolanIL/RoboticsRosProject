
#ifndef UTILS_H_
#define UTILS_H_

#include <HamsterAPIClientCPP/Hamster.h>

class Utils {

	double height;
	double width;
	double resolution;
public:


	Utils(HamsterAPI::Hamster* hamster);

	double fromJToX(double j);

	double fromIToY(double i);

	double fromYToI(double y);

	double fromXToJ(double x);
	virtual ~Utils();


};

#endif /* UTILS_H_ */
