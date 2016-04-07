#pragma once

#include "defines.h"	
#include "Boll.h"
#include <QPainter>
#include <QRect>


class Racket 
{
public:
	Racket();
	~Racket();

	void paint(QPainter& painter) const;
	void update();

	int getLeft() const;
	int getRight() const;
	int getCenter() const { return rect->center().x(); }
	void hitCheck(Boll& boll);
	void setPosition(int x);
	void reset();

private:
	QRect* rect;
};

