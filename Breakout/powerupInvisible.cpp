#include "powerupInvisible.h"


PowerupInvisible::PowerupInvisible(int x, int y, Boll* boll, Racket* racket)
{
    _pixmap = QPixmap(":/Bilder/invisible.png");
	_rect = QRect(x, y, 10, 10);
	_boll = boll;
	_racket = racket;
	_givingEffect = 0;
}

void PowerupInvisible::paint(QPainter& painter)
{
	if (_visible)
		painter.drawPixmap(_rect.left() + 10, _rect.top() + 10, _pixmap);

#if powerupDB
	QFont font;
	font.setPixelSize(30);
	painter.setFont(font);
	painter.drawText(10, 330, QString("_timer: "));
	if (!_visible)
		painter.drawText(110, 360, QString::number(_timer->remainingTime()));
#endif
}

void PowerupInvisible::giveEffect()
{
	_timer->start(POWERUP_TIME_MS);
	_givingEffect = 1;
	_boll->setInvisible(1);
}

void PowerupInvisible::powerupEnded()
{
	_givingEffect = 0;
	_boll->setInvisible(0);
}
