#pragma once

#include "defines.h"
#include <stdlib.h>
#include <ctime>
#include <QPainter>
#include <qtimer.h>
#include <qmediaplayer.h>

class Boll
{
public:
	Boll(QMediaPlayer* speed, QMediaPlayer* gameover);

	void update(QRect qr, QTimer& multiscore);
	void paint(QPainter & painter) const;

	float xvel()				{ return _vx; }
	float yvel()				{ return _vy; }
	float baseVel()				{ return _baseVel; }
	QRect position() const		{ return *rect; }
	bool getIsOnPlayArea() const{ return (rect->top() < W_HEIGHT); }

	void changexvel(float x)	{ _vx *= x; }
	void changeyvel(float y)	{ _vy *= y; }

	void setxvel(float x)		{ _vx = x; }
	void setyvel(float y)		{ _vy = y; }
	void setBaseVel(float vel)	{ _baseVel = vel; }
	void setpos(float x, float y);
	void speedUp();
	void slowDown();
	void startMoving();
	void reset();
	bool isInvisible() const;
	void setInvisible(bool b);
	void stopSound();

private:
	float _vx, _vy;			//Riktningen på bollen
	float _vxInit, _vyInit; //Starthastigheten
	float _baseVel;			//Bashastigheten
	QRect* rect;  
	QPixmap* boll;
	bool _invisible;
	QMediaPlayer* _speed;
	QMediaPlayer* _gameover;
};

