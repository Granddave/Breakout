#pragma once
#include <qpainter.h>
#include "defines.h"
#include "powerup.h"
#include "Boll.h"

class PowerupInvisible : public Powerup
{
public:
	PowerupInvisible(int x, int y, Boll* boll);
	~PowerupInvisible(){}

	void paint(QPainter & painter) override;
	void giveEffect() override; //tar massa parametrar pga arv och polymorfism
	void powerupEnded() override;


private:
};