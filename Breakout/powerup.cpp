#include "powerup.h"

Powerup::Powerup()
{
	timer = new QTimer();
	timer->setSingleShot(1);
	_vel = 3; //Hastighet nedåt
	visible = 1;
}


void Powerup::update()
{
	_rect.moveTop(_rect.top() + _vel);
}
