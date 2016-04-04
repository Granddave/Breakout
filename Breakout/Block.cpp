#include "Block.h"

Block::Block(int x, int y) : _x(x), _y(y)
{
	_width = 50;
	_height = 20;
}

void Block::paint(QPainter& painter) const
{
	painter.setBrush(Qt::red);
	painter.drawRect(_x, _y, _width, _height);
}

int Block::getWidth() const
{
	return _width;
}

int Block::getHeight() const
{
	return _height;
}
