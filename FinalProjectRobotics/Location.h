
#ifndef LOCATION_H_
#define LOCATION_H_


/*
 * x - x value
 * y - y value
 * yaw  - yaw value
 *
 * */
class Location {
private:
	double x;
	double y;
	double yaw;
public:
	Location(double x, double y,double yaw);

	virtual ~Location();

	double getYaw() ;

	void setYaw(double yaw);

	double getX() ;

	void setX(double x);

	double getY() ;

	void setY(double y);
};

#endif /* LOCATION_H_ */
