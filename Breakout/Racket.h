#pragma once

#include "defines.h"	
#include <QPainter>
#include <QRect>


class Racket 
{
public:
	Racket();

	void paint(QPainter& painter) const;
	void update();

	void setPosition(int x);

private:
	int _x;
	int _y;
	int _width;
	int _height;
};

