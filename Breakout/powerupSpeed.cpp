#include "powerupSpeed.h"


PowerupSpeed::PowerupSpeed(int x, int y)
{
	_pixmap = QPixmap("PowerupSpeed.png");
	_rect = QRect(x, y, 10, 10);
}

void PowerupSpeed::paint(QPainter& painter)
{
	painter.drawPixmap(_rect.left()+10, _rect.top()+10, _pixmap);
}

void PowerupSpeed::giveEffect()
{
}
