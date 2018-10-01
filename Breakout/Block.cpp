#include "Block.h"

Block::Block(int x, int y)
{
    _block = new QPixmap(":/Bilder/block.png");
	_x = x;
	_y = y;

	_hasPowerup = 0;
 	_isActive = 1;

	_sound = new QMediaPlayer();
    _sound->setMedia(QUrl("qrc:/Ljud/Bricksound.wav"));

	//Skapar de fyra hitboxpolygonerna
	_HBleft	 = new QPolygon();
	_HBright	 = new QPolygon();
    _HBtop	 = new QPolygon();
	_HBbottom = new QPolygon();

	int left[] = { x, y, x, y + BLOCK_HEIGHT, x + (BLOCK_WIDTH/2), y + (BLOCK_HEIGHT/2) }; 
	_HBleft->setPoints(3, left);

	int right[] = { x + BLOCK_WIDTH, y, x + BLOCK_WIDTH, y + BLOCK_HEIGHT, x + (BLOCK_WIDTH/2), y + (BLOCK_HEIGHT/2) };
	_HBright->setPoints(3, right);

	int top[] = { x, y, x + BLOCK_WIDTH, y, x + (BLOCK_WIDTH/2), y + (BLOCK_HEIGHT/2) };
	_HBtop->setPoints(3, top);

	int bottom[] = { x, y + BLOCK_HEIGHT, x + BLOCK_WIDTH, y + BLOCK_HEIGHT, x + (BLOCK_WIDTH/2), y + (BLOCK_HEIGHT/2) };
	_HBbottom->setPoints(3, bottom);
}

//Målar de block som är aktiva
void Block::paint(QPainter& painter) const 
{
	if (_isActive)
		painter.drawPixmap(_x, _y, *_block);
}

//Kollar om _boll träffar block
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
			// För illustration, se Breakout/Breakout/Bilder/Hitboxexplain.jpg
			if (((point.x() == _x) && (point.y() == _y)) && ((boll.velX() > 0) && (boll.velY() > 0))) // 1
			{
				boll.changeyvel(-1);
				breakBlock(score); return;
			}
			if (((point.x() == _x) && (point.y() == _y)) && ((boll.velX() < 0) && (boll.velY() > 0))) // 2
			{
				boll.changeyvel(-1);
				breakBlock(score); return;
			}
			if (((point.x() == (_x + BLOCK_WIDTH)) && (point.y() == _y)) && ((boll.velX() > 0) && (boll.velY() > 0))) // 3
			{
				boll.changeyvel(-1);
				breakBlock(score); return;
			}
			if (((point.x() == (_x + BLOCK_WIDTH)) && (point.y() == _y)) && ((boll.velX() < 0) && (boll.velY() > 0))) // 4
			{
				boll.changeyvel(-1);
				breakBlock(score); return;
			}
			if (((point.x() == (_x + BLOCK_WIDTH)) && (point.y() == _y)) && ((boll.velX() < 0) && (boll.velY() < 0))) // 5
			{
				boll.changexvel(-1);
				breakBlock(score); return;
			}
			if (((point.x() == (_x + BLOCK_WIDTH)) && (point.y() == (_y + BLOCK_HEIGHT))) && ((boll.velX() < 0) && (boll.velY() > 0))) // 6
			{
				boll.changexvel(-1);
				breakBlock(score); return;
			}
			if (((point.x() == (_x + BLOCK_WIDTH)) && (point.y() == (_y + BLOCK_HEIGHT))) && ((boll.velX() < 0) && (boll.velY() < 0))) // 7
			{
				boll.changeyvel(-1);
				breakBlock(score); return;
			}
			if (((point.x() == (_x + BLOCK_WIDTH)) && (point.y() == (_y + BLOCK_HEIGHT))) && ((boll.velX() > 0) && (boll.velY() < 0))) // 8
			{
				boll.changeyvel(-1);
				breakBlock(score); return;
			}
			if (((point.x() == _x) && (point.y() == (_y + BLOCK_HEIGHT))) && ((boll.velX() < 0) && (boll.velY() < 0))) // 9
			{
				boll.changeyvel(-1);
				breakBlock(score); return;
			}
			if (((point.x() == _x) && (point.y() == (_y + BLOCK_HEIGHT))) && ((boll.velX() > 0) && (boll.velY() < 0))) // 10
			{
				boll.changeyvel(-1);
				breakBlock(score); return;
			}
			if (((point.x() == _x) && (point.y() == (_y + BLOCK_HEIGHT))) && ((boll.velX() > 0) && (boll.velY() > 0))) // 11
			{
				boll.changexvel(-1);
				breakBlock(score); return;
			}
			if (((point.x() == _x) && (point.y() == _y)) && ((boll.velX() > 0) && (boll.velY() < 0))) // 12
			{
				boll.changexvel(-1);
				breakBlock(score); return;
			}
			
			///////////////////////////////////////////////////
 			if (getHBbottom().containsPoint(point, Qt::OddEvenFill))
			{
				if ((boll.velX() > 0) && (boll.velY() > 0)) // 11
				{
					boll.changexvel(-1);
					breakBlock(score); return;
				}
				if ((boll.velX() < 0) && (boll.velY() > 0)) // 6
				{
					boll.changexvel(-1);
					breakBlock(score); return;
				}
				boll.changeyvel(-1);
				breakBlock(score); return;
			}

			else if (getHBtop().containsPoint(point, Qt::OddEvenFill)) 
			{
				if ((boll.velX() > 0) && (boll.velY() < 0)) // 12
				{
					boll.changexvel(-1);
					breakBlock(score); return;
				}
				if ((boll.velX() < 0) && (boll.velY() < 0)) // 5
				{
					boll.changexvel(-1);
					breakBlock(score); return;
				}
				boll.changeyvel(-1);
				breakBlock(score); return;
			}

			else if (getHBleft().containsPoint(point, Qt::OddEvenFill))
			{
				if ((boll.velX() == 0) && (boll.velY() < 0))
				{
					boll.changeyvel(-1);
					breakBlock(score); return;
				}
				else if ((boll.velX() == 0) && (boll.velY() > 0))
				{
					boll.changeyvel(-1);
					breakBlock(score); return;
				}
				if ((boll.velX() < 0) && (boll.velY() < 0)) // 9
				{
					boll.changeyvel(-1);
					breakBlock(score); return;
				}
				if ((boll.velX() < 0) && (boll.velY() > 0)) // 2
				{
					boll.changeyvel(-1);
					breakBlock(score); return;
				}
				boll.changexvel(-1);
				breakBlock(score); return;
			}

			else if (getHBright().containsPoint(point, Qt::OddEvenFill))
			{
				if ((boll.velX() == 0) && (boll.velY() < 0))
				{
					boll.changeyvel(-1);
					breakBlock(score); return;
				}
				else if ((boll.velX() == 0) && (boll.velY() > 0))
				{
					boll.changeyvel(-1);
					breakBlock(score); return;
				}
				if ((boll.velX() > 0) && (boll.velY() < 0)) // 8
				{
					boll.changeyvel(-1);
					breakBlock(score); return;
				}
				if ((boll.velX() > 0) && (boll.velY() > 0)) // 3
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
	_sound->play();
}

Block::~Block()
{
	delete _block;
	delete _sound;
	delete _HBleft;
	delete _HBright;
	delete _HBtop;
	delete _HBbottom;
}
