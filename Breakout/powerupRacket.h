#pragma once
#include <qpainter.h>
#include "defines.h"
#include "powerup.h"
#include "Boll.h"
#include "Racket.h"

class PowerupRacket : public Powerup
{
public:
	PowerupRacket(int x, int y, Boll* boll, Racket* racket);
	~PowerupRacket(){}

	void paint(QPainter & painter) override;
	void giveEffect() override; //tar massa parametrar pga arv och polymorfism
	void powerupEnded() override;
};