#include "powerupInvisible.h"


PowerupInvisible::PowerupInvisible(int x, int y, Boll* boll)
{
	_pixmap = QPixmap("invisible.png");
	_rect = QRect(x, y, 10, 10);
	_boll = boll;
	givingEffect = 0;
}

void PowerupInvisible::paint(QPainter& painter)
{
	if (visible)
		painter.drawPixmap(_rect.left() + 10, _rect.top() + 10, _pixmap);

#if powerupDB
	QFont font;
	font.setPixelSize(30);
	painter.setFont(font);
	painter.drawText(10, 330, QString("timer: "));
	if (!visible)
		painter.drawText(110, 360, QString::number(timer->remainingTime()));
#endif
}

void PowerupInvisible::giveEffect()
{
	timer->start(POWERUP_TIME_MS);
	givingEffect = 1;
	_boll->setInvisible(1);
}

void PowerupInvisible::powerupEnded()
{
	givingEffect = 0;
	_boll->setInvisible(0);
}