#include "Racket.h"

Racket::Racket()
{
	_height = 15;
	_width = 100;
	_x = (W_WIDTH / 2) - _width /2;
	_y = W_HEIGHT - 40;
}

void Racket::update()
{
	//Hitcheck
}

void Racket::setPosition(int x)
{
	if ((x >= _width/2) && (x < W_WIDTH - _width/2)) // Om innanför fönstret
		_x = x - _width / 2;
	//qDebug() << _x;
}

void Racket::paint(QPainter& painter) const
{
	painter.setBrush(Qt::blue);
	painter.drawRect(_x, _y, _width, _height);

}
