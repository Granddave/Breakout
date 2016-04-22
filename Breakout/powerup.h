#pragma once
#include <qpainter.h>
#include <QTimer>
#include <string>
#include "defines.h"
#include "Boll.h"
#include "Racket.h"

class Powerup
{
public:
	Powerup();
	virtual ~Powerup();

	bool checkCollision(QRect* qr)	const { return _rect.intersects(*qr);  } //Hitcheck med racket 
	bool checkIfOutside()			const { return _rect.top() > W_HEIGHT; } //Hitcheck om utanf�r spelplan
	bool isVisible()				const { return _visible; }
	void setVisible(bool b)				  { _visible = b; }

	QTimer* getTimer()				const { return _timer; }

	void update();
	virtual void paint(QPainter & painter) = 0;
	virtual void giveEffect(){} //tar massa parametrar pga arv och polymorfism
	virtual void powerupEnded() = 0;

protected:
	float _vel; //Hastighet ned�t
	
	QRect _rect;
	QPixmap _pixmap;
	QTimer* _timer;

	Boll* _boll;
	Racket* _racket;

	bool _givingEffect;
	bool _visible;
};

