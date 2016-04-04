#pragma once

#include "defines.h"
#include <stdlib.h>
#include <ctime>
#include <QPainter>

class Boll
{
public: 
	Boll();

	void update(QRect qr);
	void paint(QPainter & painter);
	float xvel(){ return _vx; }
	float yvel(){ return _vy; }
	float getRadius(){ return _radius; }

	int getRight()	{ return _x + _radius * 2; }
	int getLeft()	{ return _x; }
	int getTop()	{ return _y; }
	int getBottom()	{ return _y + _radius * 2; }

	void setxvel(float x){ _vx = x; }
	void setyvel(float y){ _vy = y; }
	void setpos(float x, float y);
	QRect position() const;
	void nyRiktning(float vx, float vy);
	void reset();


private:
	float _x, _y, _vx, _vy;
	int _radius;

};

