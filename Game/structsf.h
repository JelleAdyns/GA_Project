#ifndef STRUCTSF_H
#define STRUCTSF_H

#include <string>


struct Point2f
{
	Point2f();
	explicit Point2f(float x, float y);

	float x;
	float y;
};

struct Rectf
{
	Rectf();
	explicit Rectf(float left, float bottom, float width, float height);

	float left;
	float bottom;
	float width;
	float height;

};

struct Circlef
{
	Circlef();
	explicit Circlef(const Point2f& center, float radius);
	explicit Circlef(float centerX, float centerY, float radius);

	Point2f center;
	float radius;
};


struct Ellipsef
{
	Ellipsef();
	explicit Ellipsef(const Point2f& center, float radiusX, float radiusY);
	explicit Ellipsef(float centerX, float centerY, float radiusX, float radiusY);

	Point2f center;
	float radiusX;
	float radiusY;
};

#endif // !STRUCTSF_H
