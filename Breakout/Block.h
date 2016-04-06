#pragma once

#include <QPainter>
#include "defines.h"
#include "Boll.h"

class Block
{
public:
	Block(int x, int y);
	
	void paint(QPainter& painter) const;
	void hitCheck(Boll& boll);
	void setActive() { _isActive = 1; }
	bool isBlockActive() { return _isActive; }

	//QRect getRect() const{ return *rect; };
	QPolygon getHBleft() const { return *HBleft; };
	QPolygon getHBright() const { return *HBright; };
	QPolygon getHBtop() const { return *HBtop; };
	QPolygon getHBbottom() const { return *HBbottom; };
	//int getRight()	const { return rect->right(); }
	//int getLeft()	const { return rect->left(); }
	//int getTop()	const { return rect->top(); }
	//int getBottom() const { return rect->bottom(); }
	//int getWidth()	const { return rect->width(); }
	//int getHeight() const { return rect->height(); }

private: 
	//QRect* rect;
	QPolygon* HBleft;
	QPolygon* HBright;
	QPolygon* HBtop;
	QPolygon* HBbottom;

	bool _isActive;
};

