#include "Racket.h"

Racket::Racket()
{
	int _width = 100;
	rect = new QRect((W_WIDTH / 2) - _width / 2, W_HEIGHT - 40, 100, 15);
}

Racket::~Racket()
{
	delete rect;
}

void Racket::update()
{
	//Hitcheck
}

int Racket::getLeft() const
{ 
	return rect->left();
}

int Racket::getRight() const
{
	return rect->right();
}

void Racket::hitCheck(Boll& boll)
{
	int ballLeft = boll.position().left();
	int ballHeight = boll.position().height();
	int ballWidth = boll.position().width();
	int ballTop = boll.position().top();


	QPoint point(ballLeft + (ballWidth / 2), ballTop + (ballHeight / 2)); //center point i bollen

	if (rect->contains(point)) //Beräknar ny hastighet beroende på var den träffar på racket.
	{
		float MAX_BOUNCE_ANGLE = 4 * (PI / 12);
		float BASESPEED = boll.baseVel();
		float relativeIntersectX = rect->center().x() - boll.position().center().x();
		float normalizedRelativeIntersectionY = (relativeIntersectX / (rect->width() / 2)) + 1.5;
		float bounceAngle = normalizedRelativeIntersectionY * MAX_BOUNCE_ANGLE;
		boll.setxvel(boll.baseVel() * cos(bounceAngle));
		boll.setyvel(boll.baseVel() * -sin(bounceAngle));
		int x = 0;
	}
}

void Racket::setPosition(int x)
{
	if ((x >= rect->width() / 2) && (x < W_WIDTH - rect->width() / 2)) // Om innanför fönstret
		rect->moveLeft(x - (rect->width() / 2));
}

void Racket::reset()
{
	rect->moveLeft((W_WIDTH / 2) - rect->width() / 2);
}

void Racket::paint(QPainter& painter) const
{
	painter.setBrush(Qt::blue);
	painter.drawRect(rect->x(), rect->y(), rect->width(), rect->height());
}
