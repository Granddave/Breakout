#include "powerup.h"

Powerup::Powerup()
{
}

Powerup::~Powerup()
{
}

bool Powerup::update(QRect* qr) const
{
	return _rect.intersects(*qr);
}

QRect Powerup::position() const
{
	return _rect;
}
