#include "Boll.h"

Boll::Boll(QMediaPlayer* speed, QMediaPlayer* gameover)
{
	_boll = new QPixmap("Bilder/ball.png");
	_rect = new QRect(W_WIDTH / 2, W_HEIGHT - 50, 6, 6);
	_sound = new QMediaPlayer();
	_sound->setMedia(QUrl("Ljud/paddle.wav"));

	_speed = speed;
	_gameover = gameover;
	_vx = 0;
	_vy = 0;
	_baseVel = BOLL_BASESPEED;
	_invisible = 0;
	_gameoverOnce = 1;
}

void Boll::update(QRect spelplan, QTimer& multiscore)
{
	_rect->moveLeft(_rect->x() + _vx * _baseVel);
	_rect->moveTop(_rect->y() + _vy * _baseVel);
	if ((_rect->right() >= spelplan.x() + spelplan.width()) && (_vx > 0))
	{
		_vx = -_vx;
		_sound->play();

	}
	if ((_rect->left() <= spelplan.x()) && (_vx < 0))
	{
		_vx = -_vx;
		_sound->play();
	}
	if ((_rect->y() <= spelplan.y()) && (_vy < 0))
	{
		_vy = -_vy;
		_sound->play();
	}
	if (_rect->y() > W_HEIGHT)
	{
		if (_gameoverOnce)
			playGameover();

		multiscore.stop();
		_speed->stop();
		_vx = 0;
		_vy = 0;
		_gameoverOnce = 0;
	}
}

void Boll::paint(QPainter & painter) const
{
	painter.drawPixmap(_rect->left(), _rect->top(), *_boll);

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
	_rect->moveLeft(W_WIDTH / 2);
	_rect->moveTop(W_HEIGHT - 50);
	_baseVel = BOLL_BASESPEED;
	setInvisible(0);
	_vx = 0;
	_vy = 0;
	_gameoverOnce = 1;
}

void Boll::setPos(float x, float y)
{
	_rect->moveLeft(x);
	_rect->moveTop(y);
}

void Boll::speedUp()
{
	_baseVel = BOLL_POWERUPSPEED;
	_speed->play();
}

void Boll::slowDown()
{
	_speed->stop();
	_baseVel = BOLL_BASESPEED;
}

Boll::~Boll()
{
	delete _boll;
	delete _rect;
	delete _sound;
}