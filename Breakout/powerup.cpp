#include "powerup.h"

Powerup::Powerup()
{
	timer = new QTimer();
	_vel = 3;
	visible = 1;
}


void Powerup::update()
{
	_rect.moveTop(_rect.top() + _vel);
	active = timer->isActive();
}
