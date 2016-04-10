#include "Boll.h"

Boll::Boll()
{
	boll = new QPixmap("ball.png");
	rect = new QRect(W_WIDTH / 2, W_HEIGHT - 50, 6, 6);
	_vx = 0;
	_vy = 0;
	_baseVel = 6;
}

void Boll::update(QRect qr, QTimer& multiscore)
{
	rect->moveLeft(rect->x() + _vx);
	rect->moveTop(rect->y() + _vy);
	if (rect->right() >= qr.x() + qr.width())
	{
		//rect->setRight(qr.width()-1);
		_vx = -_vx;
	}
	if (rect->x() <= qr.x())
	{
		//rect->setLeft(1);
		_vx = -_vx;
	}
	if (rect->y() <= qr.y())
	{
		//rect->setTop(22);
		_vy = -_vy;
	}
	if (rect->y() > W_HEIGHT)
	{
		multiscore.stop();
		_vx = 0;
		_vy = 0;
	}
}

void Boll::paint(QPainter & painter)
{
	painter.drawPixmap(rect->left(), rect->top(), *boll);
}

QRect Boll::position() const
{
	return *rect;
}

void Boll::nyRiktning(float vx, float vy)
{
	_vx = vx;
	_vy = vy;
}

void Boll::setHasChangedDir(bool b)
{
	hasChangedDir = b;
}

bool Boll::getIsOnPlayArea()
{
	return (rect->top() < W_HEIGHT);
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
	
	_vx = 0;
	_vy = 0;
}

void Boll::changexvel(float x)
{
	_vx *= x;
	setHasChangedDir(1);
}

void Boll::changeyvel(float y)
{
	_vy *= y;
	setHasChangedDir(1);
}

void Boll::setpos(float x, float y)
{
	// Använd moveLeft eller moveTop istället för setX och setY.
	// setX/Y ändrar storleken!
	rect->moveLeft(x);
	rect->moveTop(y);
}
