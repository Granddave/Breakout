#include "Racket.h"

Racket::Racket()
{
	int _width = 100;
	_sound = new QMediaPlayer();
	_sound->setMedia(QUrl("Ljud/paddle.wav"));
	_rect = new QRect((W_WIDTH / 2) - _width / 2, W_HEIGHT - 40, 100, 15);
	_pixL = new QPixmap("Bilder/RacketL.png");
	_pixM = new QPixmap("Bilder/RacketM.png");
	_pixR = new QPixmap("Bilder/RacketR.png");
}

void Racket::hitCheck(Boll& boll) const
{
	QPoint bollCenter = boll.position().center();

	if (_rect->contains(bollCenter)) //Beräknar ny hastighet beroende på var den träffar på racket.
	{
		float MAX_BOUNCE_ANGLE = 4 * (PI / 12);
		float relativeIntersectX = _rect->center().x() - bollCenter.x();
		float normalizedRelativeIntersectionY = (relativeIntersectX / (_rect->width() / 2)) + 1.5;
		float bounceAngle = normalizedRelativeIntersectionY * MAX_BOUNCE_ANGLE;
		boll.setVelX(cos(bounceAngle));
		boll.setVelY(-sin(bounceAngle));
		_sound->play();
	}
}

void Racket::setPosition(int x)
{
	// Om innanför fönstret
	if ((x >= _rect->width() / 2) && (x < W_WIDTH - _rect->width() / 2)) 
		_rect->moveLeft(x - (_rect->width() / 2));
}

void Racket::reset() const
{
	if (_rect->width() == 200)
		_rect->moveLeft((W_WIDTH / 2) - _rect->width() / 4);
	else
		_rect->moveLeft((W_WIDTH / 2) - _rect->width() / 2);
	_rect->setWidth(100);
}

void Racket::paint(QPainter& painter) const
{
	//Storlekarna på pixmapparna
	QRect left(_rect->left(), _rect->top(), 13, _rect->height());
	QRect right(_rect->right() - 13, _rect->top(), 13, _rect->height());
	QRect mid(_rect->left() + 13, _rect->top(), _rect->width() - 13 * 2, _rect->height());

	painter.drawPixmap(left.left(), left.top(), left.width(), left.height(), *_pixL);
	painter.drawPixmap(right.left(), right.top(), right.width(), right.height(), *_pixR);
	painter.drawPixmap(mid.left(), mid.top(), mid.width(), mid.height(), *_pixM);
}

void Racket::sizeUp()
{
	_rect->setWidth(200);
}

void Racket::sizeDown()
{
	_rect->setWidth(100);
}

Racket::~Racket()
{
	delete _sound;
	delete _rect;
	delete _pixL;
	delete _pixM;
	delete _pixR;
}