#include "Block.h"

Block::Block(int x, int y)
{
	rect = new QRect(x, y, BLOCK_WIDTH, BLOCK_HEIGHT);
	_isActive = 1;
}

void Block::paint(QPainter& painter) const
{
	if (_isActive)
	{
		painter.setBrush(Qt::lightGray);
		painter.drawRect(*rect);
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

		QPoint pointRight(ballLeft + ballWidth + 1, ballTop);
		QPoint pointLeft(ballLeft - 1, ballTop);
		QPoint pointTop(ballLeft, ballTop - 1);
		QPoint pointBottom(ballLeft, ballTop + ballHeight + 1);

		if (_isActive) {
			if (getRect().contains(pointRight)) {
				boll.setxvel(-1);
			}

			else if (getRect().contains(pointLeft)) {
				boll.setxvel(1);
			}

			if (getRect().contains(pointTop)) {
				boll.setyvel(1);
			}

			else if (getRect().contains(pointBottom)) {
				boll.setyvel(-1);
			}
		}
		_isActive = 0;
	}
}

QRect Block::getRect() const
{
	return *rect;
}
