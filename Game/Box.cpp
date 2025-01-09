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

//Rectf Box::ToRectf() const
//{
//	return Rectf {
//		Center[0] - GetWidth() / 2,
//		Center[1] - GetHeight() / 2,
//		GetWidth(),
//		GetHeight() };
//}

bool Box::IsPointInside(const ThreeBlade& point, float extraRadius) const
{
	return (GetDistanceFromLeft(point) > -extraRadius and
			GetDistanceFromRight(point) > -extraRadius and
			GetDistanceFromBottom(point) > -extraRadius and
			GetDistanceFromTop(point) > -extraRadius );
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

jela::Vector2f Box::GetOutsideDistance(const ThreeBlade& point, float extraRadius) const
{
	jela::Vector2f dist{};

	float left	{GetDistanceFromLeft(point) - extraRadius};
	float right	{GetDistanceFromRight(point) - extraRadius};
	float bottom{GetDistanceFromBottom(point) - extraRadius};
	float top	{GetDistanceFromTop(point) - extraRadius};

	if (left < 0.f) dist.x = std::abs(left);
	else if (right < 0.f) dist.x = right;

	if (bottom < 0.f) dist.y = std::abs(bottom);
	else if (top < 0.f) dist.y = top;
	
	return dist;
}

void Box::GetCornerPoints(std::vector<Point2f>& cornerPoints) const
{
	std::vector<ThreeBlade> vec{};
	GetCornerPoints(vec);

	cornerPoints.reserve(vec.size());

	for (const auto& threeBlade : vec)
	{
		cornerPoints.push_back(Point2f{ threeBlade[0], threeBlade[1] });
	}
}
void Box::GetCornerPoints(std::vector<ThreeBlade>& cornerPoints) const
{
	cornerPoints.reserve(4);

	OneBlade screen{ 0,0,0,1 };

	cornerPoints.push_back(TopSide ^ LeftSide ^ screen);
	cornerPoints.push_back(RightSide ^ TopSide ^ screen);
	cornerPoints.push_back(BottomSide ^ RightSide ^ screen);
	cornerPoints.push_back(LeftSide ^ BottomSide ^ screen);

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
