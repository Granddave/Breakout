#include "Boll.h"

Boll::Boll()
{
	boll = new QPixmap("ball.png");
	rect = new QRect(W_WIDTH / 2, W_HEIGHT - 50, 6, 6);
	_vx = 0;
	_vy = 0;
	_BaseVel = 6;
}

void Boll::update(QRect qr, QTimer& multiscore)
{
	rect->moveLeft(rect->x() + _vx);
	rect->moveTop(rect->y() + _vy);
	if (rect->right() >= qr.x() + qr.width())
	{
		//rect->setRight(qr.width()-1);
		_vx = -_vx;
	}
	if (rect->x() <= qr.x())
	{
		//rect->setLeft(1);
		_vx = -_vx;
	}
	if (rect->y() <= qr.y())
	{
		//rect->setTop(22);
		_vy = -_vy;
	}
	if (rect->y() > W_HEIGHT)
	{
		multiscore.stop();
		_vx = 0;
		_vy = 0;
	}
}

void Boll::paint(QPainter & painter)
{
	painter.drawPixmap(rect->left(), rect->top(), *boll);
}

QRect Boll::position() const
{
	return *rect;
}

void Boll::nyRiktning(float vx, float vy)
{
	_vx = vx;
	_vy = vy;
}

void Boll::setHasChangedDir(bool b)
{
	hasChangedDir = b;
}

bool Boll::getIsOnPlayArea()
{
	return (rect->top() < W_HEIGHT);
}

void Boll::startMoving()
{
	_vx = _vxInit;
	_vy = _vyInit;
}

void Boll::reset()
{
	rect->moveLeft(W_WIDTH / 2);
	rect->moveTop(W_HEIGHT - 50);
	
	_vx = 0;
	_vy = 0;

	srand(time(NULL)); 
	_vxInit =  0; //starthastighet
	_vyInit = _BaseVel;
	//TODO fixa random start
}

void Boll::changexvel(float x)
{
	_vx *= x;
	setHasChangedDir(1);
}

void Boll::changeyvel(float y)
{
	_vy *= y;
	setHasChangedDir(1);
}

void Boll::setpos(float x, float y)
{
	// Anv�nd moveLeft eller moveTop ist�llet f�r setX och setY.
	// setX/Y �ndrar storleken!
	rect->moveLeft(x);
	rect->moveTop(y);
}
