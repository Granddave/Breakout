#include "powerupRacket.h"


PowerupRacket::PowerupRacket(int x, int y, Boll* boll, Racket* racket)
{
	_pixmap = QPixmap("Bilder/Plus.png");
	_rect = QRect(x, y, 10, 10);
	_boll = boll;
	_racket = racket;
	givingEffect = 0;
}

void PowerupRacket::paint(QPainter& painter)
{
	if (visible)
		painter.drawPixmap(_rect.left() + 10, _rect.top() + 10, _pixmap);

#if powerupDB
	QFont font;
	font.setPixelSize(30);
	painter.setFont(font);
	painter.drawText(10, 330, QString("timer: "));
	if (!visible)
		painter.drawText(110, 330, QString::number(timer->remainingTime()));
#endif
}

void PowerupRacket::giveEffect()
{
	timer->start(POWERUP_TIME_MS);
	givingEffect = 1;
	_racket->sizeUp();
}

void PowerupRacket::powerupEnded()
{
	_racket->sizeDown();
	givingEffect = 0;
}
