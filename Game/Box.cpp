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
	m_LeftSide{ -(centerX - width / 2), 1,0,0 },
	m_RightSide{ (centerX + width / 2), -1,0,0 },
	m_BottomSide{ -(centerY - height / 2), 0,1,0 },
	m_TopSide{ (centerY + height / 2), 0,-1,0 }
{
}

bool Box::IsPointInside(const ThreeBlade& point) const
{
	return (GetDistanceFromLeft(point) > 0.f and
			GetDistanceFromRight(point) > 0.f and
			GetDistanceFromBottom(point) > 0.f and
			GetDistanceFromTop(point) > 0.f );
}

float Box::GetDistanceFromLeft(const ThreeBlade& point) const
{
	return GAUtils::GetDistance(point, m_LeftSide);
}

float Box::GetDistanceFromRight(const ThreeBlade& point) const
{
	return GAUtils::GetDistance(point, m_RightSide);
}

float Box::GetDistanceFromBottom(const ThreeBlade& point) const
{
	return GAUtils::GetDistance(point, m_BottomSide);
}

float Box::GetDistanceFromTop(const ThreeBlade& point) const
{
	return GAUtils::GetDistance(point, m_TopSide);
}

Point2f Box::GetOutsideDistance(const ThreeBlade& point) const
{
	Point2f dist{};

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
