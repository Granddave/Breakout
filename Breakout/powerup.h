#pragma once
#include <qpainter.h>
#include <string>
#include "defines.h"

class Powerup
{
public:
	Powerup();
	virtual ~Powerup();

	void update() 
	{ _rect.moveTop(_rect.top() + _vel); } //flytt av powerup
	bool checkCollision(QRect* qr) const { return _rect.intersects(*qr) || _rect.top() > W_HEIGHT; } //Hitcheck med racket 
	
	virtual void paint(QPainter & painter) = 0;
	virtual void giveEffect(); //tar massa parametrar pga arv och polymorfism

protected:
	QRect _rect;
	float _vel;
	QPixmap _pixmap;
};

