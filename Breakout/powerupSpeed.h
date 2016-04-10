#pragma once
#include <qpainter.h>
#include "defines.h"
#include "powerup.h"

class PowerupSpeed: public Powerup
{
public:
	PowerupSpeed(int x, int y);
	~PowerupSpeed();

	void paint(QPainter & painter) override;

private:
	QPixmap _pixmap;
};