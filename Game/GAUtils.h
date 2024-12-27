#ifndef GAUTILS_H
#define GAUTILS_H

#include "FlyFish.h"

namespace GAUtils
{
	ThreeBlade Project(const ThreeBlade& point, const TwoBlade& line);
	ThreeBlade Project(const ThreeBlade& point, const OneBlade& plane);
	TwoBlade Project(const TwoBlade& line, const ThreeBlade& point);
	TwoBlade Project(const TwoBlade& line, const OneBlade& plane);
	OneBlade Project(const OneBlade& plane, const ThreeBlade& point);
	OneBlade Project(const OneBlade& plane, const TwoBlade& line);

	float GetDistance(const ThreeBlade& point, const OneBlade& plane);
	float GetDistance(const ThreeBlade& point, const TwoBlade& line);
	float GetDistance(const ThreeBlade& point1, const ThreeBlade& point2);

	float GetAngle(const TwoBlade& line1, const TwoBlade& line2);

	void Transform(OneBlade& toTransform, const Motor& transform);
	void Transform(TwoBlade& toTransform, const Motor& transform);
	void Transform(ThreeBlade& toTransform, const Motor& transform);
	
}

#endif // !GAUTILS_H

