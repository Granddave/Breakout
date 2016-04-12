#pragma once

#include <QPainter>
#include <stdlib.h>
#include <ctime>
#include "defines.h"
#include "Boll.h"
#include "Score.h"
#include <QPixmap>

class Block
{
public:
	Block(int x, int y);
	
	void paint(QPainter& painter) const;
	void hitCheck(Boll& boll, Score& score);
	void reset();
	void setActive()				{ _isActive = 1; }
	void setPowerupTaken(bool b)	{ _powerupTaken = b; }

	bool isBlockActive() const		{ return _isActive; }
	bool isPowerupTaken() const		{ return _powerupTaken; }
	bool hasPowerup() const			{ return _hasPowerup; }
	int getX() const				{ return _x; }
	int getY() const				{ return _y; }
	QPolygon getHBleft() const		{ return *HBleft; };
	QPolygon getHBright() const		{ return *HBright; };
	QPolygon getHBtop() const		{ return *HBtop; };
	QPolygon getHBbottom() const	{ return *HBbottom; };

private:
	int _x, _y;
	QPolygon* HBleft;
	QPolygon* HBright;
	QPolygon* HBtop;
	QPolygon* HBbottom;
	QPixmap* block;

	bool _isActive;
	bool _hasPowerup;
	bool _powerupTaken;
};

