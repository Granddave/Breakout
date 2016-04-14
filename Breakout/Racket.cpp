#include "Racket.h"

Racket::Racket()
{
	int _width = 100;
	sound = new QMediaPlayer();
	sound->setMedia(QUrl("rackethit.wav"));
	rect = new QRect((W_WIDTH / 2) - _width / 2, W_HEIGHT - 40, 100, 15);
}

Racket::~Racket()
{
	delete rect;
}

void Racket::hitCheck(Boll& boll) const
{
	QPoint bollCenter = boll.position().center();

	if (rect->contains(bollCenter)) //Ber�knar ny hastighet beroende p� var den tr�ffar p� racket.
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
	// Om innanf�r f�nstret
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
	painter.setBrush(Qt::blue);
	painter.drawRect(rect->x(), rect->y(), rect->width(), rect->height());
}

void Racket::sizeUp()
{
	rect->setWidth(200);
}

void Racket::sizeDown()
{
	rect->setWidth(100);
}