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
	float yDist = rect->y() - boll.position().bottom();
	//qDebug() << yDist;
	if (yDist <= 0 && (boll.getLeft() < getRight() && boll.getRight() > getLeft()))
 		boll.setyvel(-1 * boll.yvel());
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
