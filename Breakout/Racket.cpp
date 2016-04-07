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
	/*
	int yDist = rect->top() - boll.position().bottom();
	//qDebug() << yDist;
	if (yDist <= 0 && yDist < rect->top() - rect->height() && (boll.getLeft() < getRight() && boll.getRight() > getLeft()))
 		boll.setyvel(-1 * boll.yvel());
	else if (yDist <= 0 && yDist < rect->height() * -1) //om i samma höjdled som racket
	{
		if (boll.getLeft() < getRight() && boll.getRight() > getLeft()) //om den nuddar racket
		{
			boll.setxvel(-1 * boll.xvel());
		}
	}
	*/
	
	if ((boll.position()).intersects(*rect)) {

		int ballLeft = boll.position().left();
		int ballHeight = boll.position().height();
		int ballWidth = boll.position().width();
		int ballTop = boll.position().top();

		QPoint top(ballLeft + (ballWidth / 2), ballTop);
		QPoint right(ballLeft + ballWidth, ballTop + (ballHeight / 2));
		QPoint left(ballLeft, ballTop + (ballHeight / 2));
		QPoint bottom(ballLeft + (ballWidth / 2), ballTop + ballHeight);

		/* Har vi blocken placerade för nära varandra kan programmet uppfatta att bollen "contains" två stycken blocks.
		Därav ändrade jag avståndet mellan blocken i vertikalled */

		if (rect->contains(top)) {
			if ((rect->contains(right)) || (rect->contains(left))){
				boll.changeyvel(-1);
			}
			else{
				boll.changeyvel(-1);
			}
		}

		else if (rect->contains(bottom)) {
			if ((rect->contains(right)) || (rect->contains(left))){
				boll.changeyvel(-1);
			}
			else{
				boll.changeyvel(-1);
			}
		}

		else if (rect->contains(right)) {
			if ((rect->contains(top)) || (rect->contains(bottom))){
				boll.changexvel(-1);
			}
			else{
				boll.changexvel(-1);
			}
		}

		else if (rect->contains(left)) {
			if ((rect->contains(top)) || (rect->contains(bottom))){
				boll.changexvel(-1);
			}
			else{
				boll.changexvel(-1);
			}
		}
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
