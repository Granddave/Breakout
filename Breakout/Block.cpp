#include "Block.h"

Block::Block(int x, int y) : _x(x), _y(y)
{
	_width = BLOCK_WIDTH;
	_height = BLOCK_HEIGHT;
	_isActive = 1;
	rect = new QRect(x, y, _width, _height);
}

void Block::paint(QPainter& painter) const
{
	if (_isActive)
	{
		painter.setBrush(Qt::lightGray);
		painter.drawRect(_x, _y, _width, _height);
	}
}

void Block::hitCheck(Boll& boll)
{
	//if (((boll.getRight() > getLeft()) && (boll.getTop() < getBottom())) && // Left bottom  
	//	((boll.getLeft() < getRight()) && (boll.getBottom() > getTop())))   // Right top  
	//{
	//	_isActive = 0;
	//}

	if ((boll.position()).intersects(getRect())) {

		int ballLeft = boll.position().left();
		int ballHeight = boll.position().height();
		int ballWidth = boll.position().width();
		int ballTop = boll.position().top();

		QPoint topLeft(ballLeft, ballTop);
		QPoint topRight(ballLeft + ballWidth, ballTop);
		QPoint bottomLeft(ballLeft, ballTop - ballHeight);
		QPoint bottomRight(ballLeft + ballWidth, ballTop - ballHeight);

		if (_isActive) {
			if (getRect().contains(topRight)) {
				boll.setxvel(-1);
			}

			else if (getRect().contains(bottomLeft)) {
				boll.setxvel(1);
			}

			if (getRect().contains(topLeft)) {
				boll.setyvel(1);
			}

			else if (getRect().contains(bottomRight)) {
				boll.setyvel(-1);
			}
		}
		_isActive = 0;
	}
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

QRect Block::getRect()
{
	return *rect;
}
