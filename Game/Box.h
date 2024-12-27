#ifndef BOX_H
#define BOX_H

#include "FlyFish.h"
#include "structsf.h"

struct Box
{
	Box(const Rectf& rect);
	Box(const Point2f& center, float width, float height);
	Box(float centerX, float centerY, float width, float height);

	~Box() = default;

	Box(const Box& other) = delete;
	Box(Box&& other) noexcept = delete;
	Box& operator=(const Box& other) = delete;
	Box& operator=(Box&& other) noexcept = delete;

	bool IsPointInside(const ThreeBlade& point) const;

	float GetWidth() const;
	float GetHeight() const;

	float GetDistanceFromLeft(const ThreeBlade& point) const;
	float GetDistanceFromRight(const ThreeBlade& point) const;
	float GetDistanceFromBottom(const ThreeBlade& point) const;
	float GetDistanceFromTop(const ThreeBlade& point) const;

	jela::Vector2f GetOutsideDistance(const ThreeBlade& point) const;
	void Rotate(const Motor& rotation, bool rotateSides);
	void Translate(const Motor& translation);

	ThreeBlade Center;

	OneBlade LeftSide;
	OneBlade RightSide;
	OneBlade BottomSide;
	OneBlade TopSide;
};

#endif // !BOX_H
