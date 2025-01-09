#ifndef BOX_H
#define BOX_H

#include <Structs.h>
#include "FlyFish.h"
#include "structsf.h"

struct Box final
{
	Box(const Rectf& rect);
	Box(const Point2f& center, float width, float height);
	Box(float centerX, float centerY, float width, float height);

	//Rectf ToRectf() const;

	bool IsPointInside(const ThreeBlade& point, float extraRadius = 0.f) const;

	float GetWidth() const;
	float GetHeight() const;

	float GetDistanceFromLeft(const ThreeBlade& point) const;
	float GetDistanceFromRight(const ThreeBlade& point) const;
	float GetDistanceFromBottom(const ThreeBlade& point) const;
	float GetDistanceFromTop(const ThreeBlade& point) const;

	jela::Vector2f GetOutsideDistance(const ThreeBlade& point, float extraRadius = 0.f) const;

	void GetCornerPoints(std::vector<ThreeBlade>& cornerPoints) const;
	void GetCornerPoints(std::vector<Point2f>& cornerPoints) const;
	
	void Rotate(const Motor& rotation, bool rotateSides);
	void Translate(const Motor& translation);


	ThreeBlade Center;

	OneBlade LeftSide;
	OneBlade RightSide;
	OneBlade BottomSide;
	OneBlade TopSide;
};

#endif // !BOX_H
