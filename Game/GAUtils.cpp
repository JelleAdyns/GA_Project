#include "GAUtils.h"



ThreeBlade GAUtils::Project(const ThreeBlade& point, const TwoBlade& line)
{
	return ((point | line) * ~line).Normalized().Grade3();
	//return (((point.Normalized() * line.Normalized()).Grade1()) * ~line).Grade3();
}

ThreeBlade GAUtils::Project(const ThreeBlade& point, const OneBlade& plane)
{
	return ((point | plane) * ~plane).Normalized().Grade3();
	//return (((point.Normalized() * plane.Normalized()).Grade2()) * ~plane).Grade3();
}

TwoBlade GAUtils::Project(const TwoBlade& line, const ThreeBlade& point)
{
	return ((line | point) * ~point).Normalized().Grade2();
	//return (((line.Normalized() * point.Normalized()).Grade1()) * ~point).Grade2();
}

TwoBlade GAUtils::Project(const TwoBlade& line, const OneBlade& plane)
{
	return ((line | plane) * ~plane).Normalized().Grade2();
	//return (((line.Normalized() * plane.Normalized()).Grade1()) * ~plane).Grade2();
}

OneBlade GAUtils::Project(const OneBlade& plane, const ThreeBlade& point)
{
	return ((plane | point) * ~point).Normalized().Grade1();
	//return (((plane.Normalized() * point.Normalized()).Grade2()) * ~point).Grade1();
}

OneBlade GAUtils::Project(const OneBlade& point, const TwoBlade& line)
{
	return ((point | line) * ~line).Normalized().Grade1();
	//return (((point.Normalized() * line.Normalized()).Grade1()) * ~line).Grade1();
}

float GAUtils::GetDistance(const ThreeBlade& point, const OneBlade& plane)
{
	return point.Normalized() & plane.Normalized();
}

float GAUtils::GetDistance(const ThreeBlade& point, const TwoBlade& line)
{
	return GetDistance(point, Project(point, line));
}

float GAUtils::GetDistance(const ThreeBlade& point1, const ThreeBlade& point2)
{
	return (point1.Normalized() & point2.Normalized()).Norm();
}

float GAUtils::GetAngle(const TwoBlade& line1, const TwoBlade& line2)
{
	return std::acos(-(line1.Normalized() | line2.Normalized()));
}

void GAUtils::RotatePlane(OneBlade& toRotate, float degrees, const TwoBlade& rotationLine)
{
	MultiVector rot{};
	rot = (-sin(degrees * DEG_TO_RAD / 2) * rotationLine.Normalized());
	rot[0] = cos(degrees * DEG_TO_RAD / 2);

	toRotate = (rot * toRotate * ~rot).Normalized().Grade1();
}