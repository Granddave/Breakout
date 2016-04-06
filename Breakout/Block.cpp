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

		QPoint top(ballLeft + (ballWidth/2), ballTop);
		QPoint right(ballLeft + ballWidth, ballTop + (ballHeight/2));
		QPoint left(ballLeft, ballTop + (ballHeight/2));
		QPoint bottom(ballLeft + (ballWidth/2), ballTop + ballHeight);

		/* Har vi blocken placerade för nära varandra kan programmet uppfatta att bollen "contains" två stycken blocks.
		Därav ändrade jag avståndet mellan blocken i vertikalled */

		if (_isActive) {
			if (getRect().contains(top)) 
			{
				if ((boll.xvel() > 0) && (boll.yvel() < 0))
				{
					boll.changeyvel(-1);
					_isActive = 0;
				}
				else if ((boll.xvel() < 0) && (boll.yvel() > 0))
				{
					boll.changexvel(-1);
					_isActive = 0;
				}
				else if ((getRect().contains(right)) || (getRect().contains(left)))
				{
					boll.changeyvel(-1);
					_isActive = 0;
				}
				else
				{
					boll.changeyvel(-1);
					_isActive = 0;
				}
			}

			else if (getRect().contains(bottom)) 
			{
				if ((boll.xvel() > 0) && (boll.yvel() < 0))
				{
					boll.changexvel(-1);
					_isActive = 0;
				}
				else if ((boll.xvel() < 0) && (boll.yvel() < 0))
				{
					boll.changexvel(-1);
					_isActive = 0;
				}
				else if ((getRect().contains(right)) || (getRect().contains(left)))
				{
					boll.changeyvel(-1);
					_isActive = 0;
				}
				else
				{
					boll.changeyvel(-1);
					_isActive = 0;
				}
			}

			else if (getRect().contains(right)) 
			{
				if ((boll.xvel() > 0) && (boll.yvel() < 0))
				{
					boll.changexvel(-1);
					_isActive = 0;
				}
				else if ((boll.xvel() < 0) && (boll.yvel() > 0))
				{
					boll.changeyvel(-1);
					_isActive = 0;
				}
				else if ((getRect().contains(top)) || (getRect().contains(bottom)))
				{
					boll.changexvel(-1);
					_isActive = 0;
				}
				else
				{
					boll.changexvel(-1);
					_isActive = 0;
				}
			}

			else if (getRect().contains(left)) 
			{
				if ((boll.xvel() > 0) && (boll.yvel() < 0))
				{
					boll.changeyvel(-1);
					_isActive = 0;
				}
				else if ((boll.xvel() < 0) && (boll.yvel() > 0))
				{
					boll.changexvel(-1);
					_isActive = 0;
				}
				else if ((getRect().contains(top)) || (getRect().contains(bottom)))
				{
					boll.changexvel(-1);
					_isActive = 0;
				}
				else
				{
					boll.changexvel(-1);
					_isActive = 0;
				}
			}
		}
	}
}

QRect Block::getRect() const
{
	return *rect;
}
