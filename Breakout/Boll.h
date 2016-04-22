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
	~Boll();

	void update(QRect qr, QTimer& multiscore);
	void paint(QPainter & painter) const;

	float velX()				{ return _vx; }
	float velY()				{ return _vy; }
	QRect position() const		{ return *_rect; }
	bool getIsOnPlayArea() const{ return (_rect->top() < W_HEIGHT); }

	void changexvel(float x)	{ _vx *= x; }
	void changeyvel(float y)	{ _vy *= y; }

	void setVelX(float x)		{ _vx = x; }
	void setVelY(float y)		{ _vy = y; }
	void setPos(float x, float y);
	void speedUp();
	void slowDown();
	void startMoving();
	void reset();
	bool isInvisible() const	{ return _invisible; }
	void setInvisible(bool b)	{ _invisible = b; }
	void playGameover() const	{ _gameover->play(); }

private:
	float _vx, _vy;			//Riktningen på bollen
	float _baseVel;			//Bashastigheten

	QRect* _rect;			//Position samt storlek
	QPixmap* _boll;
	QMediaPlayer* _sound, *_speed, *_gameover;

	bool _invisible;		//Om true åker den igenom blocken utan att studsa
	bool _gameoverOnce;
};


