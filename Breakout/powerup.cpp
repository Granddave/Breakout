#include "powerup.h"

Powerup::Powerup()
{
	_timer = new QTimer();
	_timer->setSingleShot(1);
	_vel = 3; //Hastighet nedåt
	_visible = 1;
}

Powerup::~Powerup()
{
	delete _timer;
}

void Powerup::update()
{
	_rect.moveTop(_rect.top() + _vel);
}
