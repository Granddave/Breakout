#include "Boll.h"

Boll::Boll()
{
	_x = W_WIDTH / 2;
	_y = W_HEIGHT - 50;
	_vx = 0;
	_vy = 0;
	_radius= 5;
}

void Boll::update(QRect qr)
{
	_x += _vx;
	_y += _vy;
	if (_x + 2 * _radius >= qr.x() + qr.width())
		_vx = -_vx;
	if (_x <= qr.x())
		_vx = -_vx;
	if (_y <= qr.y())
		_vy = -_vy;
	if (_y > 500)
	{
		_x = W_WIDTH / 2;
		_y = W_HEIGHT - 50;
		_vx = 0;
		_vy = 0;
	}
}

void Boll::paint(QPainter & painter)
{
	painter.setBrush(Qt::green);
	painter.drawEllipse(_x, _y, _radius * 2, _radius * 2);
}

QRect Boll::position() const
{
	return QRect(_x, _y, _radius * 2, _radius * 2);
}

void Boll::nyRiktning(float vx, float vy)
{
	_vx = vx;
	_vy = vy;
}

void Boll::reset()
{
	_x = W_WIDTH / 2;
	_y = W_HEIGHT - 70;

	srand(time(NULL));
	_vx = 0.5f; 
	_vy = -2;
}

void Boll::setpos(float x, float y)
{
	_x = x;
	_y = y;
}
