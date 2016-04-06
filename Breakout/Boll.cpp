#include "Boll.h"

Boll::Boll()
{
	rect = new QRect(W_WIDTH / 2, W_HEIGHT - 50, 10, 10);
	_vx = 0;
	_vy = 0;
}

void Boll::update(QRect qr)
{
	rect->moveLeft(rect->x() + _vx);
	rect->moveTop(rect->y() + _vy);
	if (rect->right() >= qr.x() + qr.width())
		_vx = -_vx;
	if (rect->x() <= qr.x())
		_vx = -_vx;
	if (rect->y() <= qr.y())
		_vy = -_vy;
	if (rect->y() > W_HEIGHT)
	{
		rect->moveLeft(W_WIDTH / 2);
		rect->moveTop(W_HEIGHT - 50);
		_vx = 0;
		_vy = 0;
	}
}

void Boll::paint(QPainter & painter)
{
	painter.setBrush(Qt::green);
	painter.drawEllipse(rect->x(), rect->y(), rect->width(), rect->width());
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

void Boll::reset()
{
	rect->moveLeft(W_WIDTH / 2);
	rect->moveTop(W_HEIGHT - 70);

	srand(time(NULL));
	_vx = 4; 
	_vy = -3;
	//TODO fixa random start
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
	// set ändrar storleken!
	rect->moveLeft(x);
	rect->moveTop(y);
}
