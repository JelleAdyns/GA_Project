#include "GAUtils.h"



ThreeBlade GAUtils::Project(const ThreeBlade& point, const TwoBlade& line)
{
	return ((point | line) * ~line).Normalized().Grade3();
}

ThreeBlade GAUtils::Project(const ThreeBlade& point, const OneBlade& plane)
{
	return ((point | plane) * ~plane).Normalized().Grade3();
}

TwoBlade GAUtils::Project(const TwoBlade& line, const ThreeBlade& point)
{
	return ((line | point) * ~point).Normalized().Grade2();
}

TwoBlade GAUtils::Project(const TwoBlade& line, const OneBlade& plane)
{
	return ((line | plane) * ~plane).Normalized().Grade2();
}

OneBlade GAUtils::Project(const OneBlade& plane, const ThreeBlade& point)
{
	return ((plane | point) * ~point).Normalized().Grade1();
}

OneBlade GAUtils::Project(const OneBlade& point, const TwoBlade& line)
{
	return ((point | line) * ~line).Normalized().Grade1();
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

void GAUtils::Transform(OneBlade& toTransform, const Motor& transform)
{
	toTransform = (transform * toTransform * ~transform).Normalized().Grade1();
}

void GAUtils::Transform(TwoBlade& toTransform, const Motor& transform)
{
	toTransform = (transform * toTransform * ~transform).Normalized().Grade2();
}

void GAUtils::Transform(ThreeBlade& toTransform, const Motor& transform)
{
	toTransform = (transform * toTransform * ~transform).Normalized().Grade3();
}
