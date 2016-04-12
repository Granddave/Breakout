#pragma once
#include <qpainter.h>
#include "defines.h"
#include "powerup.h"
#include "Boll.h"

class PowerupSpeed: public Powerup
{
public:
	PowerupSpeed(int x, int y, Boll* boll);
	~PowerupSpeed(){}

	void paint(QPainter & painter) override;
	void giveEffect() override; //tar massa parametrar pga arv och polymorfism
	void powerupEnded() override;


private:
	QPixmap _pixmap;
};