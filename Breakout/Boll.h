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

	int getRight()	{ return rect->x() + rect->width() * 2; }
	int getLeft()	{ return rect->x(); }
	int getTop()	{ return rect->y(); }
	int getBottom()	{ return rect->y() + rect->width() * 2; }
	bool intersects(QRect* obj) { return rect->intersects(*obj); }

	void changexvel(float x);
	void changeyvel(float y);

	void setxvel(float x){ _vx = x; }
	void setyvel(float y){ _vy = y; }
	void setpos(float x, float y);
	QRect position() const;
	void nyRiktning(float vx, float vy);
	void setHasChangedDir(bool b);
	bool getHasChangedDir(){ return hasChangedDir; }
	void reset();

private:
	float _vx, _vy;
	QRect* rect;
	QPixmap* boll;
	bool hasChangedDir;
};

