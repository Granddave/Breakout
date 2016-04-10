#pragma once
#include <qpainter.h>
#include <string>
#include "defines.h"

class Powerup
{
public:
	Powerup();
	virtual ~Powerup();

	bool update(QRect* qr) const; //Hitcheck med racket
	virtual void paint(QPainter & painter) = 0;
	QRect position() const;

protected:
	QRect _rect;
	float _vel;

};