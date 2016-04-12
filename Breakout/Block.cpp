#include "Block.h"

Block::Block(int x, int y)
{
	block = new QPixmap("block.png");
	_x = x;
	_y = y;

	//Skapar de fyra hitboxpolygonerna
	HBleft	 = new QPolygon();
	HBright	 = new QPolygon();
	HBtop	 = new QPolygon();
	HBbottom = new QPolygon();

	int left[] = { x, y, x, y + BLOCK_HEIGHT, x + (BLOCK_WIDTH/2), y + (BLOCK_HEIGHT/2) }; 
	HBleft->setPoints(3, left);

	int right[] = { x + BLOCK_WIDTH, y, x + BLOCK_WIDTH, y + BLOCK_HEIGHT, x + (BLOCK_WIDTH/2), y + (BLOCK_HEIGHT/2) };
	HBright->setPoints(3, right);

	int top[] = { x, y, x + BLOCK_WIDTH, y, x + (BLOCK_WIDTH/2), y + (BLOCK_HEIGHT/2) };
	HBtop->setPoints(3, top);

	int bottom[] = { x, y + BLOCK_HEIGHT, x + BLOCK_WIDTH, y + BLOCK_HEIGHT, x + (BLOCK_WIDTH/2), y + (BLOCK_HEIGHT/2) };
	HBbottom->setPoints(3, bottom);

	_hasPowerup = 0;
 	_isActive = 1;
}

//M�lar de block som �r aktiva
void Block::paint(QPainter& painter) const 
{
	if (_isActive)
	{
		painter.drawPixmap(_x, _y, *block);
	}
}

//Kollar om boll tr�ffar block
void Block::hitCheck(Boll& boll, Score& score)
{
	QPoint point = boll.position().center();

		if (_isActive){

			if (boll.isInvisible() 
				&& (getHBleft().containsPoint(point, Qt::OddEvenFill) 
				|| getHBbottom().containsPoint(point, Qt::OddEvenFill) 
				|| getHBtop().containsPoint(point, Qt::OddEvenFill) 
				|| getHBright().containsPoint(point, Qt::OddEvenFill)))
			{
				_isActive = 0; score.addScore(); return;
			}
			
			// F�ljande 12 if-statements kollar om bollen �r exakt i n�gon av kanterna i blocket och kollar �ven vilken riktning bollen har
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
 			if (getHBbottom().containsPoint(point, Qt::OddEvenFill)) // os�ker vad man ska skriva i andra f�ltet d�r OddEvenFill st�r...
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
				if ((boll.xvel() == 0) && (boll.yvel() < 0))
				{
					boll.changeyvel(-1);
					_isActive = 0; score.addScore(); return;
				}
				else if ((boll.xvel() == 0) && (boll.yvel() > 0))
				{
					boll.changeyvel(-1);
					_isActive = 0; score.addScore(); return;
				}
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
				if ((boll.xvel() == 0) && (boll.yvel() < 0))
				{
					boll.changeyvel(-1);
					_isActive = 0; score.addScore(); return;
				}
				else if ((boll.xvel() == 0) && (boll.yvel() > 0))
				{
					boll.changeyvel(-1);
					_isActive = 0; score.addScore(); return;
				}
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

//Aktiverar blocken och randomiserar powerups
void Block::reset()
{
	int r = rand() % 6;
 	if (r == 0)
		_hasPowerup = 1;
	else
		_hasPowerup = 0;

	_isActive = 1;
	_powerupTaken = 0;
}
