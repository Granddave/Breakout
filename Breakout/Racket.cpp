#include "Racket.h"

Racket::Racket()
{
	int _width = 100;
	sound = new QMediaPlayer();
	sound->setMedia(QUrl("Ljud/paddle.wav"));
	rect = new QRect((W_WIDTH / 2) - _width / 2, W_HEIGHT - 40, 100, 15);
	pixL = new QPixmap("Bilder/RacketL.png");
	pixM = new QPixmap("Bilder/RacketM.png");
	pixR = new QPixmap("Bilder/RacketR.png");
}

Racket::~Racket()
{
	delete rect;
}

void Racket::hitCheck(Boll& boll) const
{
	QPoint bollCenter = boll.position().center();

	if (rect->contains(bollCenter)) //Beräknar ny hastighet beroende på var den träffar på racket.
	{
		float MAX_BOUNCE_ANGLE = 4 * (PI / 12);
		float relativeIntersectX = rect->center().x() - bollCenter.x();
		float normalizedRelativeIntersectionY = (relativeIntersectX / (rect->width() / 2)) + 1.5;
		float bounceAngle = normalizedRelativeIntersectionY * MAX_BOUNCE_ANGLE;
		boll.setxvel(cos(bounceAngle));
		boll.setyvel(-sin(bounceAngle));
		sound->play();
	}
}

void Racket::setPosition(int x)
{
	// Om innanför fönstret
	if ((x >= rect->width() / 2) && (x < W_WIDTH - rect->width() / 2)) 
		rect->moveLeft(x - (rect->width() / 2));
}

void Racket::reset() const
{
	if (rect->width() == 200)
		rect->moveLeft((W_WIDTH / 2) - rect->width() / 4);
	else
		rect->moveLeft((W_WIDTH / 2) - rect->width() / 2);
	rect->setWidth(100);
}

void Racket::paint(QPainter& painter) const
{
	//Storlekarna på pixmapparna
	QRect left(rect->left(), rect->top(), 13, rect->height());
	QRect right(rect->right() - 13, rect->top(), 13, rect->height());
	QRect mid(rect->left() + 13, rect->top(), rect->width() - 13 * 2, rect->height());

	painter.drawPixmap(left.left(), left.top(), left.width(), left.height(), *pixL);
	painter.drawPixmap(right.left(), right.top(), right.width(), right.height(), *pixR);
	painter.drawPixmap(mid.left(), mid.top(), mid.width(), mid.height(), *pixM);
}

void Racket::sizeUp()
{
	rect->setWidth(200);
}

void Racket::sizeDown()
{
	rect->setWidth(100);
}