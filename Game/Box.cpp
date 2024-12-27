#include "Box.h"
#include "GAUtils.h"

Box::Box(const Rectf& rect):
	Box{ rect.left + rect.width / 2 , rect.bottom + rect.height / 2, rect.width, rect.height }
{
}

Box::Box(const Point2f& center, float width, float height):
	Box{center.x, center.y, width, height }
{
}

Box::Box(float centerX, float centerY, float width, float height):
	Center{centerX, centerY, 0},
	LeftSide{ -(centerX - width / 2), 1,0,0 },
	RightSide{ (centerX + width / 2), -1,0,0 },
	BottomSide{ -(centerY - height / 2), 0,1,0 },
	TopSide{ (centerY + height / 2), 0,-1,0 }
{
}

bool Box::IsPointInside(const ThreeBlade& point) const
{
	return (GetDistanceFromLeft(point) > 0.f and
			GetDistanceFromRight(point) > 0.f and
			GetDistanceFromBottom(point) > 0.f and
			GetDistanceFromTop(point) > 0.f );
}

float Box::GetWidth() const
{
	return GetDistanceFromLeft(Center) * 2;
}

float Box::GetHeight() const
{
	return GetDistanceFromTop(Center) * 2;
}

float Box::GetDistanceFromLeft(const ThreeBlade& point) const
{
	return GAUtils::GetDistance(point, LeftSide);
}

float Box::GetDistanceFromRight(const ThreeBlade& point) const
{
	return GAUtils::GetDistance(point, RightSide);
}

float Box::GetDistanceFromBottom(const ThreeBlade& point) const
{
	return GAUtils::GetDistance(point, BottomSide);
}

float Box::GetDistanceFromTop(const ThreeBlade& point) const
{
	return GAUtils::GetDistance(point, TopSide);
}

jela::Vector2f Box::GetOutsideDistance(const ThreeBlade& point) const
{
	jela::Vector2f dist{};

	float left	{GetDistanceFromLeft(point)};
	float right	{GetDistanceFromRight(point)};
	float bottom{GetDistanceFromBottom(point)};
	float top	{GetDistanceFromTop(point)};

	if (left < 0.f) dist.x = std::abs(left);
	else if (right < 0.f) dist.x = right;

	if (bottom < 0.f) dist.y = std::abs(bottom);
	else if (top < 0.f) dist.y = top;
	
	return dist;
}

void Box::Rotate(const Motor& rotation, bool rotateSides)
{
	GAUtils::Transform(Center, rotation);
	if (rotateSides)
	{
		GAUtils::Transform(LeftSide, rotation);
		GAUtils::Transform(RightSide, rotation);
		GAUtils::Transform(BottomSide, rotation);
		GAUtils::Transform(TopSide, rotation);
	}
}

void Box::Translate(const Motor& translation)
{
	GAUtils::Transform(Center, translation);

	GAUtils::Transform(LeftSide, translation);
	GAUtils::Transform(RightSide, translation);
	GAUtils::Transform(BottomSide, translation);
	GAUtils::Transform(TopSide, translation);
}
