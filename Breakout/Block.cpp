#include "Block.h"

Block::Block(int x, int y) : _x(x), _y(y)
{
	_width = BLOCK_WIDTH;
	_height = BLOCK_HEIGHT;
	_isActive = 1;
}

void Block::paint(QPainter& painter) const
{
	if (_isActive)
		painter.setBrush(Qt::lightGray);
	else
		painter.setBrush(Qt::red);
	painter.drawRect(_x, _y, _width, _height);
}

void Block::hitCheck(Boll& boll)
{
	if (((boll.getRight() > getLeft()) && (boll.getTop() < getBottom())) && // Left bottom  
	    ((boll.getLeft() < getRight()) && (boll.getBottom() > getTop())))   // Right top  
		_isActive = 0;
}

void Block::setActive()
{
	_isActive = 1;
}

int Block::getWidth() const
{
	return _width;
}

int Block::getHeight() const
{
	return _height;
}
