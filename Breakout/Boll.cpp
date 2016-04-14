#include "Boll.h"

Boll::Boll()
{
	boll = new QPixmap("ball.png");
	rect = new QRect(W_WIDTH / 2, W_HEIGHT - 50, 6, 6);
	_vx = 0;
	_vy = 0;
	_baseVel = BOLL_BASESPEED;
	_invisible = 0;
}

void Boll::update(QRect qr, QTimer& multiscore)
{
	rect->moveLeft(rect->x() + _vx);
	rect->moveTop(rect->y() + _vy);
	if ((rect->right() >= qr.x() + qr.width()) && (_vx > 0))
	{
		_vx = -_vx;
	}
	if ((rect->x() <= qr.x()) && (_vx < 0))
	{
		_vx = -_vx;
	}
	if ((rect->y() <= qr.y()) && (_vy < 0))
	{
		_vy = -_vy;
	}
	if (rect->y() > W_HEIGHT)
	{
		multiscore.stop();
		_vx = 0;
		_vy = 0;
	}
}

void Boll::paint(QPainter & painter) const
{
	painter.drawPixmap(rect->left(), rect->top(), *boll);

#if powerupDB
	QFont font;
	font.setPixelSize(30);
	painter.setFont(font);
	painter.drawText(10, 300, QString("Speed: "));
	painter.drawText(110, 300, QString::number(_baseVel));
#endif
}

void Boll::startMoving()
{
	_vx = 0;
	_vy = -_baseVel;
}

void Boll::reset()
{
	rect->moveLeft(W_WIDTH / 2);
	rect->moveTop(W_HEIGHT - 50);
	_baseVel = BOLL_BASESPEED;
	setInvisible(0);
	_vx = 0;
	_vy = 0;
}

bool Boll::isInvisible() const
{
	return _invisible;
}

void Boll::setInvisible(bool b)
{
	_invisible = b;
}

void Boll::setpos(float x, float y)
{
	// Använd moveLeft eller moveTop istället för setX och setY.
	// setX/Y ändrar storleken!
	rect->moveLeft(x);
	rect->moveTop(y);
}

void Boll::speedUp()
{
	_baseVel = 8;
	//if (_baseVel <= 8)
	//	_baseVel += 1;
}

void Boll::slowDown()
{
	_baseVel = 4;
	//if (_baseVel > 4)
	//	_baseVel -= 1;
}

