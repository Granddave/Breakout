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
	void setActive() { _isActive = 1; }
	void setPowerupTaken(bool b) { _powerupTaken = b; }
	bool isBlockActive() { return _isActive; }
	bool hasPowerup() { return _hasPowerup; }
	bool isPowerupTaken() { return _powerupTaken; }

	QPolygon getHBleft() const { return *HBleft; };
	QPolygon getHBright() const { return *HBright; };
	QPolygon getHBtop() const { return *HBtop; };
	QPolygon getHBbottom() const { return *HBbottom; };

	int getX() const { return _x; }
	int getY() const { return _y; }

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

