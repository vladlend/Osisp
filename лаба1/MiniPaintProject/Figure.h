#pragma once
#include <windows.h>
#include <list>
#include <vector>
#include "Resource.h"

using namespace std; 

class Figure
{
public:
	HPEN hPen;
	HBRUSH hBrush;
	vector<POINT> points;
	void virtual draw (HDC &hdc) = 0;
	void pan(int x, int y) {
		for (int i = 0; i < points.size(); i++) {
			points[i].x -= x;
			points[i].y -= y;
		}
	}
};

class LineFigure : public Figure {
public: 
	void Figure::draw(HDC &hdc) 
	{
		SelectObject(hdc, hPen);
		MoveToEx(hdc, points[0].x, points[0].y, NULL);
		LineTo(hdc, points[1].x, points[1].y);
	}
};

class RectangleFigure : public Figure {
public:
	void Figure::draw(HDC &hdc)
	{
		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);
		Rectangle(hdc, points[0].x, points[0].y, points[1].x, points[1].y);
	}
};

class PencilFigure : public Figure {
public:
	void Figure::draw(HDC &hdc)
	{
		SelectObject(hdc, hPen);
		MoveToEx(hdc, points[0].x, points[0].y, NULL);
		for each(POINT point in points) {
			LineTo(hdc, point.x, point.y);
			MoveToEx(hdc, point.x, point.y, NULL);
		}
	}
};

class EllipseFigure : public Figure {
public:
	void Figure::draw(HDC &hdc)
	{
		SelectObject(hdc, hPen);
		SelectObject(hdc, hBrush);
		Ellipse(hdc, points[0].x, points[0].y, points[1].x, points[1].y);
	}
};

class PolygonFigure : public PencilFigure {

};

class TextFigure : public Figure {
public:
	string text;
	void Figure::draw(HDC &hdc) 
	{	
		TextOutA(hdc, points[0].x, points[0].y, text.c_str(), strlen(text.c_str()));
	}
};