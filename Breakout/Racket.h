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

	int getLeft()    const { return rect->left();  }
	int getRight()   const { return rect->right(); }
	int getCenter()  const { return rect->center().x(); }
	QRect* getRect() const { return rect; }
	
	//Kollar om bollen tr�ffar racket och sedan r�knar ut nya riktningsvektorn.
	void hitCheck(Boll& boll) const;
	
	//S�tter rackets position om racket �r innanf�r spelplanens kanter
	void setPosition(int x); 

	//S�tter racket till sin startposition
	void reset() const;

private:
	QRect* rect;
};

