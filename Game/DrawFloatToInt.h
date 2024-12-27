#ifndef DRAWFLOATTOINT_H
#define DRAWFLOATTOINT_H

#include <Engine.h>
#include "structsf.h"

namespace Drawf
{

    void DrawLine(const Point2f& firstPoint, const Point2f& secondPoint, float lineThickness = 1.f) ;
    void DrawLine(float firstX, float firstY, const Point2f& secondPoint, float lineThickness = 1.f) ;
    void DrawLine(const Point2f& firstPoint, float secondX, float secondY, float lineThickness = 1.f) ;
    void DrawLine(float firstX, float firstY, float secondX, float secondY, float lineThickness = 1.f) ;

    void DrawVector(const Point2f& origin, const jela::Vector2f& vector, int headLineLength = 30.f, float lineThickness = 1.f) ;
    void DrawVector(const Point2f& origin, float vectorX, float vectorY, int headLineLength = 30.f, float lineThickness = 1.f) ;
    void DrawVector(float originX, float originY, const jela::Vector2f& vector, int headLineLength = 30.f, float lineThickness = 1.f) ;
    void DrawVector(float originX, float originY, float vectorX, float vectorY, int headLineLength = 30.f, float lineThickness = 1.f) ;

    void DrawRectangle(const Point2f& leftBottom, float width, float height, float lineThickness = 1.f);
    void DrawRectangle(const Rectf& rect, float lineThickness = 1.f);
    void DrawRectangle(float left, float bottom, float width, float height, float lineThickness = 1.f);

    void DrawRoundedRect(const Point2f& leftBottom, float width, float height, float radiusX, float radiusY, float lineThickness = 1.f);
    void DrawRoundedRect(const Rectf& rect, float radiusX, float radiusY, float lineThickness = 1.f);
    void DrawRoundedRect(float left, float bottom, float width, float height, float radiusX, float radiusY, float lineThickness = 1.f);

    void DrawString(const tstring& textToDisplay, const jela::Font& font, const Point2f& leftBottom, float width, float height, bool showRect = false);
    void DrawString(const tstring& textToDisplay, const jela::Font& font, const Rectf& destRect, bool showRect = false);
    void DrawString(const tstring& textToDisplay, const jela::Font& font, float left, float bottom, float width, float height, bool showRect = false);

    //Takes the size of the font as Height of the destination rectangle in order to have a logical position
    void DrawString(const tstring& textToDisplay, const jela::Font& font, const Point2f& leftBottom, float width, bool showRect = false);
    //Takes the size of the font as Height of the destination rectangle in order to have a logical position
    void DrawString(const tstring& textToDisplay, const jela::Font& font, float left, float bottom, float width, bool showRect = false);

    void DrawTexture(const jela::Texture& texture, const Point2f& destLeftBottom = {}, const Rectf& srcRect = {}, float opacity = 1.f);
    void DrawTexture(const jela::Texture& texture, const Rectf& destRect, const Rectf& srcRect = {}, float opacity = 1.f);
    void DrawTexture(const jela::Texture& texture, float destLeft, float destBottom, const Rectf& srcRect = {}, float opacity = 1.f);

    void FillRectangle(const Point2f& leftBottom, float width, float height);
    void FillRectangle(const Rectf& rect);
    void FillRectangle(float left, float bottom, float width, float height);

    void FillRoundedRect(const Point2f& leftBottom, float width, float height, float radiusX, float radiusY);
    void FillRoundedRect(const Rectf& rect, float radiusX, float radiusY);
    void FillRoundedRect(float left, float bottom, float width, float height, float radiusX, float radiusY);

    void DrawPolygon(const std::vector<Point2f>& points, float lineThickness = 1.f, bool closeSegment = false);
    void FillPolygon(const std::vector<Point2f>& points);

    void DrawArc(const Point2f& center, float radiusX, float radiusY, float startAngle, float angle, float lineThickness = 1.f, bool closeSegment = false);
    void DrawArc(float centerX, float centerY, float radiusX, float radiusY, float startAngle, float angle, float lineThickness = 1.f, bool closeSegment = false);

    void FillArc(const Point2f& center, float radiusX, float radiusY, float startAngle, float angle);
    void FillArc(float centerX, float centerY, float radiusX, float radiusY, float startAngle, float angle);

    void DrawEllipse(const Point2f& center, float radiusX, float radiusY, float lineThickness = 1.f);
    void DrawEllipse(const Ellipsef& ellipse, float lineThickness = 1.f);
    void DrawEllipse(float centerX, float centerY, float radiusX, float radiusY, float lineThickness = 1.f);
    
    void FillEllipse(const Point2f& center, float radiusX, float radiusY);
    void FillEllipse(const Ellipsef& ellipse);
    void FillEllipse(float centerX, float centerY, float radiusX, float radiusY);
    
    void DrawCircle(const Circlef& circle, float lineThickness = 1.f);
    
    void FillCircle(const Circlef& circle);
}

#endif // !DRAWFLOATTOINT_H
