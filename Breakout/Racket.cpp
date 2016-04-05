#include "Racket.h"

Racket::Racket()
{
	int _width = 100;
	rect = new QRect((W_WIDTH / 2) - _width / 2, W_HEIGHT - 40, 15, 100);
}

void Racket::update()
{
	//Hitcheck
}

int Racket::getLeft()
{ 
	return rect->left();
}

int Racket::getRight()
{
	return rect->right();
}

void Racket::hitCheck(Boll& boll)
{
	float yDist = rect->y() - boll.position().bottom();
	//qDebug() << yDist;
	if (yDist <= 0 && (boll.position().center().x() - boll.getRadius() < getRight() && boll.position().center().x() + boll.getRadius() > getLeft()))
 		boll.setyvel(-1 * boll.yvel());
}

void Racket::setPosition(int x)
{
	if ((x >= rect->width() / 2) && (x < W_WIDTH - rect->width() / 2)) // Om innanför fönstret
		rect->setX( rect->x() - rect->width() / 2);
	//qDebug() << _x;
}

void Racket::reset()
{
	rect->setX((W_WIDTH / 2) - rect->width() / 2);
}

void Racket::paint(QPainter& painter) const
{
	painter.setBrush(Qt::blue);
	painter.drawRect(rect->x(), rect->y(), rect->width(), rect->height());

}
