#include "Boll.h"

Boll::Boll(QMediaPlayer* speed, QMediaPlayer* gameover)
{
	boll = new QPixmap("Bilder/ball.png");
	rect = new QRect(W_WIDTH / 2, W_HEIGHT - 50, 6, 6);
	_sound = new QMediaPlayer();
	_sound->setMedia(QUrl("Ljud/paddle.wav"));

	_speed = speed;
	_gameover = gameover;
	_vx = 0;
	_vy = 0;
	_baseVel = BOLL_BASESPEED;
	_invisible = 0;
	_times = 1;
}

void Boll::update(QRect spelplan, QTimer& multiscore)
{
	rect->moveLeft(rect->x() + _vx * _baseVel);
	rect->moveTop(rect->y() + _vy * _baseVel);
	if ((rect->right() >= spelplan.x() + spelplan.width()) && (_vx > 0))
	{
		_vx = -_vx;
		_sound->play();

	}
	if ((rect->left() <= spelplan.x()) && (_vx < 0))
	{
		_vx = -_vx;
		_sound->play();
	}
	if ((rect->y() <= spelplan.y()) && (_vy < 0))
	{
		_vy = -_vy;
		_sound->play();
	}
	if (rect->y() > W_HEIGHT)
	{
		if (_times)
			stopSound();

		multiscore.stop();
		_speed->stop();
		_vx = 0;
		_vy = 0;
		_times = 0;
	}
}

void Boll::paint(QPainter & painter) const
{
	painter.drawPixmap(rect->left(), rect->top(), *boll);

#if powerupDB
	QFont font;
	font.setPixelSize(30);
	painter.setFont(font);
	painter.drawText(10, 300, QString("Speed: "));
	painter.drawText(110, 300, QString::number(_baseVel));
#endif
}

void Boll::startMoving()
{
	_vx = 0;
	_vy = -1;
}

void Boll::reset()
{
	rect->moveLeft(W_WIDTH / 2);
	rect->moveTop(W_HEIGHT - 50);
	_baseVel = BOLL_BASESPEED;
	setInvisible(0);
	_vx = 0;
	_vy = 0;
	_times = 1;
}

bool Boll::isInvisible() const
{
	return _invisible;
}

void Boll::setInvisible(bool b)
{
	_invisible = b;
}

void Boll::setpos(float x, float y)
{
	// Använd moveLeft eller moveTop istället för setX och setY.
	// setX/Y ändrar storleken!
	rect->moveLeft(x);
	rect->moveTop(y);
}

void Boll::speedUp()
{
	_baseVel = 8;
	_speed->play();
	//if (_baseVel <= 8)
	//	_baseVel += 1;
}

void Boll::slowDown()
{
	_speed->stop();
	_baseVel = BOLL_BASESPEED;
	//if (_baseVel > 4)
	//	_baseVel -= 1;
}

void Boll::stopSound()
{
	_gameover->play();
}