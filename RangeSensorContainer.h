#ifndef RANGESENSORCONTAINER_H
#define RANGESENSORCONTAINER_H

#include "RangeSensor.h"

enum Direction {
	left = 0,
	front = 1,
	right = 2,
	back = 3
};


class RangeSensorContainer {
	private:
		bool saved_left_ = true;
		bool saved_right_ = true;
	
	public:
		RangeSensorContainer();
		RangeSensor diagLeftSensor, diagRightSensor;
		RangeSensor frontLeftSensor, frontRightSensor;

		void updateReadings(int n);
		void updateReadings();
		bool isWall(Direction wallToCheck); //Maybe directly return error for pid 
		void saveIsWall();
		bool savedIsWall(Direction wallToCheck);
    	float errorFromCenter();

};

extern RangeSensorContainer RangeSensors;

#endif
