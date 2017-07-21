

#include "Maps.h"
#include <HamsterAPIClientCPP/Hamster.h>
#include "Robot.h"

/*
 * Constructor for map class must initialize with Occupancy grip , Hamster and utils object
 * */
Maps::Maps(OccupancyGrid og,Hamster* Hamster , Utils* utils): hamster(Hamster){
	cv::namedWindow("OccupancyGrid");
	this->utils = utils;
	this->og = og;
	width = og.getWidth();
	height = og.getHeight();
}

/*
* build the first map according the Slam map
* */
void Maps::buildMap(){
	unsigned char pixel;
	matrix = cv::Mat(width-176, height-176, CV_8UC3);
	for (int i = 250; i < height - 350; i++) {
		for (int j = 250; j < width - 350; j++) {
			if (og.getCell(i, j) == CELL_FREE)
				pixel = 255;
			else if (og.getCell(i, j) == CELL_OCCUPIED)
				pixel = 0;
			else if (og.getCell(i, j) == CELL_UNKNOWN)
				pixel = 128;
			//painting the map to desired zoom
			matrix.at<cv::Vec3b>(2*(i-250),2*(j-250))[0]= pixel;
			matrix.at<cv::Vec3b>(2*(i-250),2*(j-250))[1]= pixel;
			matrix.at<cv::Vec3b>(2*(i-250),2*(j-250))[2]= pixel;
			matrix.at<cv::Vec3b>(2*(i-250)+1,2*(j-250))[0]= pixel;
			matrix.at<cv::Vec3b>(2*(i-250)+1,2*(j-250))[1]= pixel;
			matrix.at<cv::Vec3b>(2*(i-250)+1,2*(j-250))[2]= pixel;
			matrix.at<cv::Vec3b>(2*(i-250),2*(j-250)+1)[0]= pixel;
			matrix.at<cv::Vec3b>(2*(i-250),2*(j-250)+1)[1]= pixel;
			matrix.at<cv::Vec3b>(2*(i-250),2*(j-250)+1)[2]= pixel;
			matrix.at<cv::Vec3b>(2*(i-250)+1,2*(j-250)+1)[0]= pixel;
			matrix.at<cv::Vec3b>(2*(i-250)+1,2*(j-250)+1)[1]= pixel;
			matrix.at<cv::Vec3b>(2*(i-250)+1,2*(j-250)+1)[2]= pixel;
		}
	}
}

/*
* display the main window
 * */
void Maps::showMap(){
	cv::imshow("OccupancyGrid-view",matrix);
	cv::waitKey(1);
}

/*
* Draws the particles on the window according their location
 * */
bool Maps::drawPraticles(vector<Particle*> par){
	buildMap();
	unsigned int size = par.size();
	Location* location;
	double parI;
	double parJ;
	bool isStop = false;
	bool paintBlue = false;
	if((par[size - size*0.10])->getBel() > MIN_BLUE_BELIEF) {
		paintBlue = true;
	}
	for (unsigned int i = 0; i < size; i++) {
		location = par[i]->getLocation();
		parJ = utils->fromXToJ(location->getX());
		parI = utils->fromYToI(location->getY());

		if (paintBlue){ //final particles
			fillBlueParticle(2*(parI-250),2*(parJ-250));
			fillBlueParticle(2*(parI-250)+1,2*(parJ-250));
			fillBlueParticle(2*(parI-250),2*(parJ-250)+1);
			fillBlueParticle(2*(parI-250)+1,2*(parJ-250)+1);
			isStop = true;

		} else if(i >= (par.size() - TOP_PARTICALES)) { //top particles
			fillGreenParticle(2*(parI-250),2*(parJ-250));
			fillGreenParticle(2*(parI-250)+1,2*(parJ-250));
			fillGreenParticle(2*(parI-250),2*(parJ-250)+1);
			fillGreenParticle(2*(parI-250)+1,2*(parJ-250)+1);
		} else { //regular particles
			fillRedParticle(2*(parI-250),2*(parJ-250));
			fillRedParticle(2*(parI-250)+1,2*(parJ-250));
			fillRedParticle(2*(parI-250),2*(parJ-250)+1);
			fillRedParticle(2*(parI-250)+1,2*(parJ-250)+1);
		}

	}
	showMap();
	return isStop;
}

/*
* fill the near cells of the particle
 * */
void Maps::fillBlueParticle(int i,int j) {
	paintBlueParticle(i,j);
	paintBlueParticle(i-1,j);
	paintBlueParticle(i+1,j);
	paintBlueParticle(i,j-1);
	paintBlueParticle(i,j+1);
}

/*
* fill the near cells of the particle
 * */
void Maps::fillGreenParticle(int i,int j) {
	paintGreenParticle(i,j);
	paintGreenParticle(i-1,j);
	paintGreenParticle(i+1,j);
	paintGreenParticle(i,j-1);
	paintGreenParticle(i,j+1);
}
/*
* fill the near cells of the particle
 * */
void Maps::fillRedParticle(int i,int j) {
	paintRedParticle(i,j);
	paintRedParticle(i-1,j);
	paintRedParticle(i+1,j);
	paintRedParticle(i,j-1);
	paintRedParticle(i,j+1);
}

/*
* Draws blue particles for final position candidates
 * */
void Maps::paintBlueParticle(int i,int j) {
	matrix.at<cv::Vec3b>(i,j)[0] = 255;
	matrix.at<cv::Vec3b>(i,j)[1] = 0;
	matrix.at<cv::Vec3b>(i,j)[2] = 0;
}

/*
* Draws green particles as top belief
* */
void Maps::paintGreenParticle(int i,int j) {
	matrix.at<cv::Vec3b>(i,j)[0] = 0;
	matrix.at<cv::Vec3b>(i,j)[1] = 255;
	matrix.at<cv::Vec3b>(i,j)[2] = 0;
}

/*
* Draws Red particles - regular particle
 * */
void Maps::paintRedParticle(int i,int j) {
	matrix.at<cv::Vec3b>(i,j)[0] = 0;
	matrix.at<cv::Vec3b>(i,j)[1] = 0;
	matrix.at<cv::Vec3b>(i,j)[2] = 255;
}

Maps::~Maps() {}

