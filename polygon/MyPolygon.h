#pragma once  //это декларация компилятору, чтобы заголовки включались единожды
#include "Polygon.h" 
#include "Point.h"

class MyPolygon :
	public Polygon
{
public:
	MyPolygon() : Polygon() {}
	MyPolygon(int len, vector<double>x, vector<double>y) : Polygon(len, x, y) {}
	MyPolygon(const Polygon& tmp) : Polygon(tmp){}
	~MyPolygon() { Polygon::~Polygon(); }

	double perimeter() {
		double l = sqrt(pow(x[1] - x[0], 2) + pow(y[1] - y[0], 2));
		return l * len;
	}

	double square() {
		double l = sqrt(pow(x[1] - x[0], 2) + pow(y[1] - y[0], 2));
		return (this->len * l * l) / (4 * tan(3.14 / this->len));
	} 
};

