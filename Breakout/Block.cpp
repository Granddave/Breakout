#include "Block.h"

int times = 0;

Block::Block(int x, int y)
{
	block = new QPixmap("block.png");
	_x = x;
	_y = y;

	HBleft = new QPolygon();
	HBright = new QPolygon();
	HBtop = new QPolygon();
	HBbottom = new QPolygon();

	int left[] = { x, y, x, y + BLOCK_HEIGHT, x + (BLOCK_WIDTH/2), y + (BLOCK_HEIGHT/2) }; 
	HBleft->setPoints(3, left);

	int right[] = { x + BLOCK_WIDTH, y, x + BLOCK_WIDTH, y + BLOCK_HEIGHT, x + (BLOCK_WIDTH/2), y + (BLOCK_HEIGHT/2) };
	HBright->setPoints(3, right);

	int top[] = { x, y, x + BLOCK_WIDTH, y, x + (BLOCK_WIDTH/2), y + (BLOCK_HEIGHT/2) };
	HBtop->setPoints(3, top);

	int bottom[] = { x, y + BLOCK_HEIGHT, x + BLOCK_WIDTH, y + BLOCK_HEIGHT, x + (BLOCK_WIDTH/2), y + (BLOCK_HEIGHT/2) };
	HBbottom->setPoints(3, bottom);

	_isActive = 1;
}

void Block::paint(QPainter& painter) const
{
	if (_isActive)
	{
		painter.drawPixmap(_x, _y, *block);
	}
}

void Block::hitCheck(Boll& boll, Score& score)
{
		int ballLeft = boll.position().left();
		int ballHeight = boll.position().height();
		int ballWidth = boll.position().width();
		int ballTop = boll.position().top();

		QPoint point(ballLeft + (ballWidth/2), ballTop + (ballHeight/2)); //center point i bollen

		
		if (_isActive){

			// Följande 12 if-statements kollar om bollen är exakt i någon av kanterna i blocket och kollar även vilken riktning bollen har
			if (((point.x() == _x) && (point.y() == _y)) && ((boll.xvel() > 0) && (boll.yvel() > 0))) // 1
			{
				boll.changeyvel(-1);
				_isActive = 0; score.addScore(); return;
			}
			if (((point.x() == _x) && (point.y() == _y)) && ((boll.xvel() < 0) && (boll.yvel() > 0))) // 2
			{
				boll.changeyvel(-1);
				_isActive = 0; score.addScore(); return;
			}
			if (((point.x() == (_x + BLOCK_WIDTH)) && (point.y() == _y)) && ((boll.xvel() > 0) && (boll.yvel() > 0))) // 3
			{
				boll.changeyvel(-1);
				_isActive = 0; score.addScore(); return;
			}
			if (((point.x() == (_x + BLOCK_WIDTH)) && (point.y() == _y)) && ((boll.xvel() < 0) && (boll.yvel() > 0))) // 4
			{
				boll.changeyvel(-1);
				_isActive = 0; score.addScore(); return;
			}
			if (((point.x() == (_x + BLOCK_WIDTH)) && (point.y() == _y)) && ((boll.xvel() < 0) && (boll.yvel() < 0))) // 5
			{
				boll.changexvel(-1);
				_isActive = 0; score.addScore(); return;
			}
			if (((point.x() == (_x + BLOCK_WIDTH)) && (point.y() == (_y + BLOCK_HEIGHT))) && ((boll.xvel() < 0) && (boll.yvel() > 0))) // 6
			{
				boll.changexvel(-1);
				_isActive = 0; score.addScore(); return;
			}
			if (((point.x() == (_x + BLOCK_WIDTH)) && (point.y() == (_y + BLOCK_HEIGHT))) && ((boll.xvel() < 0) && (boll.yvel() < 0))) // 7
			{
				boll.changeyvel(-1);
				_isActive = 0; score.addScore(); return;
			}
			if (((point.x() == (_x + BLOCK_WIDTH)) && (point.y() == (_y + BLOCK_HEIGHT))) && ((boll.xvel() > 0) && (boll.yvel() < 0))) // 8
			{
				boll.changeyvel(-1);
				_isActive = 0; score.addScore(); return;
			}
			if (((point.x() == _x) && (point.y() == (_y + BLOCK_HEIGHT))) && ((boll.xvel() < 0) && (boll.yvel() < 0))) // 9
			{
				boll.changeyvel(-1);
				_isActive = 0; score.addScore(); return;
			}
			if (((point.x() == _x) && (point.y() == (_y + BLOCK_HEIGHT))) && ((boll.xvel() > 0) && (boll.yvel() < 0))) // 10
			{
				boll.changeyvel(-1);
				_isActive = 0; score.addScore(); return;
			}
			if (((point.x() == _x) && (point.y() == (_y + BLOCK_HEIGHT))) && ((boll.xvel() > 0) && (boll.yvel() > 0))) // 11
			{
				boll.changexvel(-1);
				_isActive = 0; score.addScore(); return;
			}
			if (((point.x() == _x) && (point.y() == _y)) && ((boll.xvel() > 0) && (boll.yvel() < 0))) // 12
			{
				boll.changexvel(-1);
				_isActive = 0; score.addScore(); return;
			}
			///////////////////////////////////////////////////
 			if (getHBbottom().containsPoint(point, Qt::OddEvenFill)) // osäker vad man ska skriva i andra fältet där OddEvenFill står...
			{
				if ((boll.xvel() > 0) && (boll.yvel() > 0)) // 11
				{
					boll.changexvel(-1);
					_isActive = 0; score.addScore(); return;
				}
				if ((boll.xvel() < 0) && (boll.yvel() > 0)) // 6
				{
					boll.changexvel(-1);
					_isActive = 0; score.addScore(); return;
				}
				boll.changeyvel(-1);
				_isActive = 0; score.addScore(); return;
			}

			else if (getHBtop().containsPoint(point, Qt::OddEvenFill)) 
			{
				if ((boll.xvel() > 0) && (boll.yvel() < 0)) // 12
				{
					boll.changexvel(-1);
					_isActive = 0; score.addScore(); return;
				}
				if ((boll.xvel() < 0) && (boll.yvel() < 0)) // 5
				{
					boll.changexvel(-1);
					_isActive = 0; score.addScore(); return;
				}
				boll.changeyvel(-1);
				_isActive = 0; score.addScore(); return;
			}

			else if (getHBleft().containsPoint(point, Qt::OddEvenFill))
			{
				if ((boll.xvel() < 0) && (boll.yvel() < 0)) // 9
				{
					boll.changeyvel(-1);
					_isActive = 0; score.addScore(); return;
				}
				if ((boll.xvel() < 0) && (boll.yvel() > 0)) // 2
				{
					boll.changeyvel(-1);
					_isActive = 0; score.addScore(); return;
				}
				boll.changexvel(-1);
				_isActive = 0; score.addScore(); return;
			}

			else if (getHBright().containsPoint(point, Qt::OddEvenFill))
			{
				if ((boll.xvel() > 0) && (boll.yvel() < 0)) // 8
				{
					boll.changeyvel(-1);
					_isActive = 0; score.addScore(); return;
				}
				if ((boll.xvel() > 0) && (boll.yvel() > 0)) // 3
				{
					boll.changeyvel(-1);
					_isActive = 0; score.addScore(); return;
				}
				boll.changexvel(-1);
				_isActive = 0; score.addScore(); return;
			}

		}
}