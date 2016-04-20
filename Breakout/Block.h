#pragma once

#include <QPainter>
#include <stdlib.h>
#include <ctime>
#include "defines.h"
#include "Boll.h"
#include "Score.h"
#include <QPixmap>
#include <QMediaPlayer>

class Block
{
public:
	Block(int x, int y);
	
	void paint(QPainter& painter) const;
	void hitCheck(Boll& boll, Score& score);
	void reset();
	void setPowerupTaken(bool b)	{ _powerupTaken = b; }
	void breakBlock(Score& score);

	bool isBlockActive() const		{ return _isActive; }
	bool isPowerupTaken() const		{ return _powerupTaken; }
	bool hasPowerup() const			{ return _hasPowerup; }
	int getX() const				{ return _x; }
	int getY() const				{ return _y; }
	QPolygon getHBleft() const		{ return *_HBleft; };
	QPolygon getHBright() const		{ return *_HBright; };
	QPolygon getHBtop() const		{ return *_HBtop; };
	QPolygon getHBbottom() const	{ return *_HBbottom; };

private:
	int _x, _y;
	QPolygon* _HBleft, *_HBright, *_HBtop, *_HBbottom;
	QPixmap* _block;
	QMediaPlayer* _sound;

	bool _isActive;
	bool _hasPowerup;
	bool _powerupTaken;
};

