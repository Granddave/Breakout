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

	int getLeft()    const { return rect->left();  }
	int getRight()   const { return rect->right(); }
	int getCenter()  const { return rect->center().x(); }
	QRect* getRect() const { return rect; }

	void sizeUp();
	void sizeDown();
	
	//Kollar om bollen träffar racket och sedan räknar ut nya riktningsvektorn.
	void hitCheck(Boll& boll) const;
	
	//Sätter rackets position om racket är innanför spelplanens kanter
	void setPosition(int x); 

	//Sätter racket till sin startposition
	void reset() const;

private:
	QMediaPlayer* sound;
	QRect* rect;
};

