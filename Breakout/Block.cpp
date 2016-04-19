#include "Block.h"

Block::Block(int x, int y)
{
	block = new QPixmap("Bilder/block.png");
	_x = x;
	_y = y;

	sound = new QMediaPlayer();
	sound->setMedia(QUrl("Ljud/Bricksound.wav"));

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

//Målar de block som är aktiva
void Block::paint(QPainter& painter) const 
{
	if (_isActive)
	{
		painter.drawPixmap(_x, _y, *block);
	}
}

//Kollar om boll träffar block
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
				breakBlock(score); return;
			}
			
			// Följande 12 if-statements kollar om bollen är exakt i någon av kanterna i blocket och kollar även vilken riktning bollen har
			if (((point.x() == _x) && (point.y() == _y)) && ((boll.xvel() > 0) && (boll.yvel() > 0))) // 1
			{
				boll.changeyvel(-1);
				breakBlock(score); return;
			}
			if (((point.x() == _x) && (point.y() == _y)) && ((boll.xvel() < 0) && (boll.yvel() > 0))) // 2
			{
				boll.changeyvel(-1);
				breakBlock(score); return;
			}
			if (((point.x() == (_x + BLOCK_WIDTH)) && (point.y() == _y)) && ((boll.xvel() > 0) && (boll.yvel() > 0))) // 3
			{
				boll.changeyvel(-1);
				breakBlock(score); return;
			}
			if (((point.x() == (_x + BLOCK_WIDTH)) && (point.y() == _y)) && ((boll.xvel() < 0) && (boll.yvel() > 0))) // 4
			{
				boll.changeyvel(-1);
				breakBlock(score); return;
			}
			if (((point.x() == (_x + BLOCK_WIDTH)) && (point.y() == _y)) && ((boll.xvel() < 0) && (boll.yvel() < 0))) // 5
			{
				boll.changexvel(-1);
				breakBlock(score); return;
			}
			if (((point.x() == (_x + BLOCK_WIDTH)) && (point.y() == (_y + BLOCK_HEIGHT))) && ((boll.xvel() < 0) && (boll.yvel() > 0))) // 6
			{
				boll.changexvel(-1);
				breakBlock(score); return;
			}
			if (((point.x() == (_x + BLOCK_WIDTH)) && (point.y() == (_y + BLOCK_HEIGHT))) && ((boll.xvel() < 0) && (boll.yvel() < 0))) // 7
			{
				boll.changeyvel(-1);
				breakBlock(score); return;
			}
			if (((point.x() == (_x + BLOCK_WIDTH)) && (point.y() == (_y + BLOCK_HEIGHT))) && ((boll.xvel() > 0) && (boll.yvel() < 0))) // 8
			{
				boll.changeyvel(-1);
				breakBlock(score); return;
			}
			if (((point.x() == _x) && (point.y() == (_y + BLOCK_HEIGHT))) && ((boll.xvel() < 0) && (boll.yvel() < 0))) // 9
			{
				boll.changeyvel(-1);
				breakBlock(score); return;
			}
			if (((point.x() == _x) && (point.y() == (_y + BLOCK_HEIGHT))) && ((boll.xvel() > 0) && (boll.yvel() < 0))) // 10
			{
				boll.changeyvel(-1);
				breakBlock(score); return;
			}
			if (((point.x() == _x) && (point.y() == (_y + BLOCK_HEIGHT))) && ((boll.xvel() > 0) && (boll.yvel() > 0))) // 11
			{
				boll.changexvel(-1);
				breakBlock(score); return;
			}
			if (((point.x() == _x) && (point.y() == _y)) && ((boll.xvel() > 0) && (boll.yvel() < 0))) // 12
			{
				boll.changexvel(-1);
				breakBlock(score); return;
			}
			
			///////////////////////////////////////////////////
 			if (getHBbottom().containsPoint(point, Qt::OddEvenFill)) // osäker vad man ska skriva i andra fältet där OddEvenFill står...
			{
				if ((boll.xvel() > 0) && (boll.yvel() > 0)) // 11
				{
					boll.changexvel(-1);
					breakBlock(score); return;
				}
				if ((boll.xvel() < 0) && (boll.yvel() > 0)) // 6
				{
					boll.changexvel(-1);
					breakBlock(score); return;
				}
				boll.changeyvel(-1);
				breakBlock(score); return;
			}

			else if (getHBtop().containsPoint(point, Qt::OddEvenFill)) 
			{
				if ((boll.xvel() > 0) && (boll.yvel() < 0)) // 12
				{
					boll.changexvel(-1);
					breakBlock(score); return;
				}
				if ((boll.xvel() < 0) && (boll.yvel() < 0)) // 5
				{
					boll.changexvel(-1);
					breakBlock(score); return;
				}
				boll.changeyvel(-1);
				breakBlock(score); return;
			}

			else if (getHBleft().containsPoint(point, Qt::OddEvenFill))
			{
				if ((boll.xvel() == 0) && (boll.yvel() < 0))
				{
					boll.changeyvel(-1);
					breakBlock(score); return;
				}
				else if ((boll.xvel() == 0) && (boll.yvel() > 0))
				{
					boll.changeyvel(-1);
					breakBlock(score); return;
				}
				if ((boll.xvel() < 0) && (boll.yvel() < 0)) // 9
				{
					boll.changeyvel(-1);
					breakBlock(score); return;
				}
				if ((boll.xvel() < 0) && (boll.yvel() > 0)) // 2
				{
					boll.changeyvel(-1);
					breakBlock(score); return;
				}
				boll.changexvel(-1);
				breakBlock(score); return;
			}

			else if (getHBright().containsPoint(point, Qt::OddEvenFill))
			{
				if ((boll.xvel() == 0) && (boll.yvel() < 0))
				{
					boll.changeyvel(-1);
					breakBlock(score); return;
				}
				else if ((boll.xvel() == 0) && (boll.yvel() > 0))
				{
					boll.changeyvel(-1);
					breakBlock(score); return;
				}
				if ((boll.xvel() > 0) && (boll.yvel() < 0)) // 8
				{
					boll.changeyvel(-1);
					breakBlock(score); return;
				}
				if ((boll.xvel() > 0) && (boll.yvel() > 0)) // 3
				{
					boll.changeyvel(-1);
					breakBlock(score); return;
				}
				boll.changexvel(-1);
				breakBlock(score); return;
			}

		}
}

//Aktiverar blocken och randomiserar powerups
void Block::reset()
{
	int r = rand() % 8;
 	if (r == 0)
		_hasPowerup = 1;
	else
		_hasPowerup = 0;

	_isActive = 1;
	_powerupTaken = 0;
}

void Block::breakBlock(Score& score)
{
	_isActive = 0; 
	score.addScore();
	sound->play();
}
