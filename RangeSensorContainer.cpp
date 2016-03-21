#include "RangeSensorContainer.h"
#include "conf.h"

RangeSensorContainer RangeSensors;

RangeSensorContainer::RangeSensorContainer() 
	: diagLeftSensor(RANGE_DIAG_LEFT_PIN, DIAG_LEFT_LOW_THRESHOLD, DIAG_LEFT_HIGH_THRESHOLD),
    diagRightSensor(RANGE_DIAG_RIGHT_PIN, DIAG_RIGHT_LOW_THRESHOLD, DIAG_RIGHT_HIGH_THRESHOLD),
    frontLeftSensor(RANGE_FRONT_LEFT_PIN, FRONT_LEFT_LOW_THRESHOLD, FRONT_LEFT_HIGH_THRESHOLD),
    frontRightSensor(RANGE_FRONT_RIGHT_PIN, FRONT_RIGHT_LOW_THRESHOLD, FRONT_RIGHT_HIGH_THRESHOLD)
{
}

void RangeSensorContainer::updateReadings(int n) {
	switch (n) {
	case 1:
    diagLeftSensor.updateRange();
    break;

	case 2:
    diagRightSensor.updateRange();
    break;

	case 3:
    frontLeftSensor.updateRange();
    break;

	case 4:
    frontRightSensor.updateRange();
    break;
	}

  delayMicroseconds(60*3);
}

void RangeSensorContainer::updateReadings() {}

bool RangeSensorContainer::isWall(Direction wallToCheck) {
	
	switch (wallToCheck) {
	case left:
		return diagLeftSensor.isWall();
		break;
	case front:
		return frontLeftSensor.isWall();
		break;
	case right:
		return diagRightSensor.isWall();
		break;
	case back:
		return false;
		break;
	}

	return false;
}

void RangeSensorContainer::saveIsWall()
{
  saved_left_ = diagLeftSensor.isWall();
  saved_right_ = diagRightSensor.isWall();
}

bool RangeSensorContainer::savedIsWall(Direction wallToCheck) {

	switch (wallToCheck) {
	case left:
		return saved_left_;
		break;
	case front:
		return frontLeftSensor.isWall();
		break;
	case right:
		return saved_right_;
		break;
	case back:
		return false;
		break;
	}

	return false;
}

float RangeSensorContainer::errorFromCenter() {
  float errorCenter;
	if (isWall(left) && isWall(right)) {
		errorCenter = .5 * (diagLeftSensor.getRange(1) - diagRightSensor.getRange(1));
	}
	else if (isWall(left)) {
		errorCenter = (diagLeftSensor.getRange(1) - RANGE_DIAG_LEFT_MIDDLE);
	}
	else if (isWall(right)) {
		errorCenter = (RANGE_DIAG_RIGHT_MIDDLE - diagRightSensor.getRange(1));
	}
	else {
		errorCenter = 0;
	}

  return errorCenter;
}
