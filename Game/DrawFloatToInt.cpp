#include "DrawFloatToInt.h"

namespace Drawf
{
	void DrawLine(const Point2f& firstPoint, const Point2f& secondPoint, float lineThickness)
	{
		DrawLine(firstPoint.x, firstPoint.y, secondPoint.x, secondPoint.y, lineThickness);
	}
	void DrawLine(float firstX, float firstY, const Point2f& secondPoint, float lineThickness)
	{
		DrawLine(firstX, firstY, secondPoint.x, secondPoint.y, lineThickness);
	}
	void DrawLine(const Point2f& firstPoint, float secondX, float secondY, float lineThickness)
	{
		DrawLine(firstPoint.x, firstPoint.y, secondX, secondY, lineThickness);
	}
	void DrawLine(float firstX, float firstY, float secondX, float secondY, float lineThickness)
	{
		ENGINE.DrawLine(
			static_cast<int>(std::round(firstX)),
			static_cast<int>(std::round(firstY)),
			static_cast<int>(std::round(secondX)),
			static_cast<int>(std::round(secondY)),
			lineThickness);
	}

	void DrawVector(const Point2f& origin, const jela::Vector2f& vector, int headLineLength, float lineThickness)
	{
		DrawVector(origin.x, origin.y, vector.x, vector.y, headLineLength, lineThickness);
	}

	void DrawVector(const Point2f& origin, float vectorX, float vectorY, int headLineLength, float lineThickness)
	{
		DrawVector(origin.x, origin.y, vectorX, vectorY, headLineLength, lineThickness);
	}

	void DrawVector(float originX, float originY, const jela::Vector2f& vector, int headLineLength, float lineThickness)
	{
		DrawVector(originX, originY, vector.x, vector.y, headLineLength, lineThickness);
	}

	void DrawVector(float originX, float originY, float vectorX, float vectorY, int headLineLength, float lineThickness)
	{
		ENGINE.DrawVector(
			static_cast<int>(std::round(originX)), 
			static_cast<int>(std::round(originY)), 
			vectorX, 
			vectorY, 
			headLineLength, 
			lineThickness);
	}

	void DrawRectangle(const Point2f& leftBottom, float width, float height, float lineThickness)
	{
		DrawRectangle(leftBottom.x, leftBottom.y, width, height, lineThickness);
	}

	void DrawRectangle(const Rectf& rect, float lineThickness)
	{
		DrawRectangle(rect.left, rect.bottom, rect.width, rect.height, lineThickness);
	}

	void DrawRectangle(float left, float bottom, float width, float height, float lineThickness)
	{
		ENGINE.DrawRectangle(
			static_cast<int>(std::round(left)),
			static_cast<int>(std::round(bottom)),
			static_cast<int>(std::round(width)),
			static_cast<int>(std::round(height)),
			lineThickness);
	}

	void DrawRoundedRect(const Point2f& leftBottom, float width, float height, float radiusX, float radiusY, float lineThickness)
	{
		DrawRoundedRect(leftBottom.x, leftBottom.y, width, height, radiusX, radiusY, lineThickness);
	}

	void DrawRoundedRect(const Rectf& rect, float radiusX, float radiusY, float lineThickness)
	{
		DrawRoundedRect(rect.left, rect.bottom, rect.width, rect.height, radiusX, radiusY, lineThickness);
	}

	void DrawRoundedRect(float left, float bottom, float width, float height, float radiusX, float radiusY, float lineThickness)
	{
		ENGINE.DrawRoundedRect(
			static_cast<int>(std::round(left)),
			static_cast<int>(std::round(bottom)),
			static_cast<int>(std::round(width)),
			static_cast<int>(std::round(height)),
			radiusX,
			radiusY,
			lineThickness);
	}


	void DrawString(const tstring& textToDisplay, const jela::Font& font, const Point2f& leftBottom, float width, float height, bool showRect)
	{
		DrawString(textToDisplay, font, leftBottom.x, leftBottom.y, width, height, showRect);
	}

	void DrawString(const tstring& textToDisplay, const jela::Font& font, const Rectf& destRect, bool showRect)
	{
		DrawString(textToDisplay, font, destRect.left, destRect.bottom, destRect.width, destRect.height, showRect);
	}

	void DrawString(const tstring& textToDisplay, const jela::Font& font, float left, float bottom, float width, float height, bool showRect)
	{
		ENGINE.DrawString(
			textToDisplay,
			font,
			static_cast<int>(std::round(left)),
			static_cast<int>(std::round(bottom)),
			static_cast<int>(std::round(width)),
			static_cast<int>(std::round(height)),
			showRect
		);
	}

	
	

	void DrawString(const tstring& textToDisplay, const jela::Font& font, const Point2f& leftBottom, float width, bool showRect)
	{
		DrawString(textToDisplay, font, leftBottom.x, leftBottom.y, width, showRect);
	}

	void DrawString(const tstring& textToDisplay, const jela::Font& font, float left, float bottom, float width, bool showRect)
	{
		ENGINE.DrawString(
			textToDisplay,
			font,
			static_cast<int>(std::round(left)),
			static_cast<int>(std::round(bottom)),
			static_cast<int>(std::round(width)),
			showRect
		);
	}

	void DrawTexture(const jela::Texture& texture, const Point2f& destLeftBottom, const Rectf& srcRect, float opacity)
	{
		ENGINE.DrawTexture(
			texture,
			jela::Point2Int{ 
				static_cast<int>(std::round(destLeftBottom.x)),
				static_cast<int>(std::round(destLeftBottom.y))
			},
			jela::RectInt{
				static_cast<int>(std::round(srcRect.left)),
				static_cast<int>(std::round(srcRect.bottom)),
				static_cast<int>(std::round(srcRect.width)),
				static_cast<int>(std::round(srcRect.height)) 
			},
			opacity
		);
	}

	void DrawTexture(const jela::Texture& texture, const Rectf& destRect, const Rectf& srcRect, float opacity)
	{
		ENGINE.DrawTexture(
			texture,
			jela::RectInt{
				static_cast<int>(std::round(destRect.left)),
				static_cast<int>(std::round(destRect.bottom)),
				static_cast<int>(std::round(destRect.width)), 
				static_cast<int>(std::round(destRect.height))
			},
			jela::RectInt{ 
				static_cast<int>(std::round(srcRect.left)), 
				static_cast<int>(std::round(srcRect.bottom)), 
				static_cast<int>(std::round(srcRect.width)),
				static_cast<int>(std::round(srcRect.height)) },
			opacity
		);
	}

	void DrawTexture(const jela::Texture& texture, float destLeft, float destBottom, const Rectf& srcRect, float opacity)
	{
		ENGINE.DrawTexture(
			texture,
			static_cast<int>(std::round(destLeft)),
			static_cast<int>(std::round(destBottom)),
			jela::RectInt{
				static_cast<int>(std::round(srcRect.left)), 
				static_cast<int>(std::round(srcRect.bottom)), 
				static_cast<int>(std::round(srcRect.width)),
				static_cast<int>(std::round(srcRect.height)) },
			opacity
		);
	}

	void FillRectangle(const Point2f& leftBottom, float width, float height)
	{
		FillRectangle(leftBottom.x, leftBottom.y, width, height);
	}

	void FillRectangle(const Rectf& rect)
	{
		FillRectangle(rect.left, rect.bottom, rect.width, rect.height);
	}

	void FillRectangle(float left, float bottom, float width, float height)
	{
		ENGINE.FillRectangle(
			static_cast<int>(std::round(left)),
			static_cast<int>(std::round(bottom)),
			static_cast<int>(std::round(width)),
			static_cast<int>(std::round(height))
		);
	}

	void FillRoundedRect(const Point2f& leftBottom, float width, float height, float radiusX, float radiusY)
	{
		FillRoundedRect(leftBottom.x, leftBottom.y, width, height, radiusX, radiusY);
	}

	void FillRoundedRect(const Rectf& rect, float radiusX, float radiusY)
	{
		FillRoundedRect(rect.left, rect.bottom, rect.width, rect.height, radiusX, radiusY);
	}

	void FillRoundedRect(float left, float bottom, float width, float height, float radiusX, float radiusY)
	{
		ENGINE.FillRoundedRect(
			static_cast<int>(std::round(left)),
			static_cast<int>(std::round(bottom)),
			static_cast<int>(std::round(width)),
			static_cast<int>(std::round(height)),
			radiusX,
			radiusY
		);
	}

	void DrawPolygon(const std::vector<Point2f>& points, float lineThickness, bool closeSegment)
	{
		std::vector<jela::Point2Int> vP(points.size());
		for (size_t i = 0; i < points.size(); i++)
		{
			vP[i] = jela::Point2Int{ static_cast<int>(std::round(points[i].x)),static_cast<int>(std::round(points[i].y)) };
		}
		ENGINE.DrawPolygon(vP, lineThickness, closeSegment);
	}

	void FillPolygon(const std::vector<Point2f>& points)
	{
		std::vector<jela::Point2Int> vP(points.size());
		for (size_t i = 0; i < points.size(); i++)
		{
			vP[i] = jela::Point2Int{ static_cast<int>(std::round(points[i].x)),static_cast<int>(std::round(points[i].y)) };
		}
		ENGINE.FillPolygon(vP);
	}

	void DrawArc(const Point2f& center, float radiusX, float radiusY, float startAngle, float angle, float lineThickness, bool closeSegment)
	{
		DrawArc(center.x, center.y, radiusX, radiusY, startAngle, angle, lineThickness, closeSegment);
	}

	void DrawArc(float centerX, float centerY, float radiusX, float radiusY, float startAngle, float angle, float lineThickness, bool closeSegment)
	{
		ENGINE.DrawArc(
			static_cast<int>(std::round(centerX)),
			static_cast<int>(std::round(centerY)),
			radiusX,
			radiusY,
			startAngle,
			angle,
			lineThickness,
			closeSegment
		);
	}

	void FillArc(const Point2f& center, float radiusX, float radiusY, float startAngle, float angle)
	{
		FillArc(center.x, center.y, radiusX, radiusY, startAngle, angle);
	}

	void FillArc(float centerX, float centerY, float radiusX, float radiusY, float startAngle, float angle)
	{
		ENGINE.FillArc(
			static_cast<int>(std::round(centerX)),
			static_cast<int>(std::round(centerY)),
			radiusX,
			radiusY,
			startAngle,
			angle
		);
	}

	void DrawEllipse(const Point2f& center, float radiusX, float radiusY, float lineThickness)
	{
		DrawEllipse(center.x, center.y, radiusX, radiusY, lineThickness);
	}

	void DrawEllipse(const Ellipsef& ellipse, float lineThickness)
	{
		DrawEllipse(ellipse.center.x, ellipse.center.y, ellipse.radiusX, ellipse.radiusY, lineThickness);
	}

	void DrawEllipse(float centerX, float centerY, float radiusX, float radiusY, float lineThickness)
	{
		ENGINE.DrawEllipse(
			static_cast<int>(std::round(centerX)),
			static_cast<int>(std::round(centerY)),
			radiusX,
			radiusY,
			lineThickness
		);
	}

	void FillEllipse(const Point2f& center, float radiusX, float radiusY)
	{
		FillEllipse(center.x, center.y, radiusX, radiusY);
	}

	void FillEllipse(const Ellipsef& ellipse)
	{
		FillEllipse(ellipse.center.x, ellipse.center.y, ellipse.radiusX, ellipse.radiusY);
	}

	void FillEllipse(float centerX, float centerY, float radiusX, float radiusY)
	{
		ENGINE.FillEllipse(
			static_cast<int>(std::round(centerX)),
			static_cast<int>(std::round(centerY)),
			radiusX,
			radiusY
		);
	}

	void DrawCircle(const Circlef& circle, float lineThickness)
	{
		ENGINE.DrawCircle(
			jela::CircleInt{
				static_cast<int>(std::round(circle.center.x)),
				static_cast<int>(std::round(circle.center.y)),
				circle.radius
			},
			lineThickness);
	}
	void FillCircle(const Circlef& circle)
	{
		ENGINE.FillCircle(jela::CircleInt{ 
			static_cast<int>(std::round(circle.center.x)),
			static_cast<int>(std::round(circle.center.y)),
			circle.radius 
			});
	}
	
}
