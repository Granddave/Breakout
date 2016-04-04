#pragma once

#include "defines.h"	
#include "Boll.h"
#include <QPainter>
#include <QRect>


class Racket 
{
public:
	Racket();

	void paint(QPainter& painter) const;
	void update();

	int getLeft();
	int getRight();
	void hitCheck(Boll& boll);
	void setPosition(int x);
	void reset();

private:
	int _x;
	int _y;
	int _width;
	int _height;
};

