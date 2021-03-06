#pragma once

#include "defines.h"	
#include "Boll.h"
#include <QPainter>
#include <QRect>
#include <qmediaplayer.h>


class Racket 
{
public:
	Racket();
	~Racket();

	void paint(QPainter& painter) const;

	int getCenter()  const { return _rect->center().x(); }
	QRect* getRect() const { return _rect; }

	void sizeUp();
	void sizeDown();
	
	//Kollar om bollen tr�ffar racket och sedan r�knar ut nya riktningsvektorn.
	void hitCheck(Boll& boll) const;
	
	//S�tter rackets position om racket �r innanf�r spelplanens kanter
	void setPosition(int x); 

	//S�tter racket till sin startposition
	void reset() const;

private:
	QMediaPlayer* _sound;
	QRect* _rect;
	QPixmap* _pixL, *_pixM, *_pixR;
};

