#pragma once
#include <qpainter.h>
#include <string>
#include "defines.h"
#include "powerup.h"

class PowerupSpeed: public Powerup
{
public:
	PowerupSpeed(int x, int y);
	~PowerupSpeed();

	void paint(QPainter & painter) override;
	void update();

private:
	QRect _rect;
	QPixmap _pixmap;
};