#include "Block.h"

Block::Block(int x, int y)
{
	rect = new QRect(x, y, BLOCK_WIDTH, BLOCK_HEIGHT);
	HBleft = new QRect(x, y + 4, 4, 12);
	HBright = new QRect(x + BLOCK_WIDTH - 4, y + 4, 4, 12);
	HBtop = new QRect(x, y, BLOCK_WIDTH, 4);
	HBbottom = new QRect(x, y + BLOCK_HEIGHT - 4, BLOCK_WIDTH, 4);

	_isActive = 1;
}

void Block::paint(QPainter& painter) const
{
	if (_isActive)
	{
		painter.setBrush(Qt::lightGray);
		painter.drawRect(*rect);
		
#if 0
		//Ritar ut hitboxar
		painter.setBrush(Qt::red);
		painter.drawRect(*HBbottom);
		painter.drawRect(*HBleft);
		painter.drawRect(*HBright);
		painter.drawRect(*HBtop);
#endif
	}
}

void Block::hitCheck(Boll& boll)
{
	//if (((boll.getRight() > getLeft()) && (boll.getTop() < getBottom())) && // Left bottom  
	//	((boll.getLeft() < getRight()) && (boll.getBottom() > getTop())))   // Right top  
	//{
	//	_isActive = 0;
	//}
	if (boll.getHasChangedDir())
		return;

	if ((boll.position()).intersects(getRect())) {

		int ballLeft = boll.position().left();
		int ballHeight = boll.position().height();
		int ballWidth = boll.position().width();
		int ballTop = boll.position().top();

		QPoint point(ballLeft + (ballWidth/2), ballTop + (ballHeight/2)); //center point i bollen

		/* Har vi blocken placerade för nära varandra kan programmet uppfatta att bollen "contains" två stycken blocks.
		Därav ändrade jag avståndet mellan blocken i vertikalled */

		if (_isActive) {
			if (getHBbottom().contains(point)) 
			{
				if (((boll.xvel() > 0) && (boll.yvel() > 0)) && (point.x() > getHBbottom().left()))       // syd-öst
				else if (((boll.xvel() < 0) && (boll.yvel() > 0)) && (point.x() < getHBbottom().right())) // syd-väst
				else if (((boll.xvel() > 0) && (boll.yvel() < 0)) && (point.x() < getHBbottom().right())) // nord-öst
				else if (((boll.xvel() < 0) && (boll.yvel() < 0)) && (point.x() < getHBbottom().right())) // nord-väst
                else if ((boll.xvel() > 0) && (boll.yvel() < 0)) // nord-öst
				else if ((boll.xvel() < 0) && (boll.yvel() < 0)) // nord-väst
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