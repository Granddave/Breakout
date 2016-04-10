#include "powerupSpeed.h"


PowerupSpeed::PowerupSpeed(int x, int y)
{
	_pixmap = QPixmap("PowerupSpeed.png");
	_rect = QRect(x, y, 10, 10);
	_vel = 1;
}

PowerupSpeed::~PowerupSpeed()
{
}

void PowerupSpeed::paint(QPainter& painter)
{
	painter.drawPixmap(_rect.left(), _rect.top(), _pixmap);
}

void PowerupSpeed::update()
{
	_rect.moveTop(_rect.top() + _vel);
}
