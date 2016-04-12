#pragma once
#include <qpainter.h>
#include <QTimer>
#include <string>
#include "defines.h"
#include "Boll.h"

class Powerup
{
public:
	Powerup();
	virtual ~Powerup(){}

	bool checkCollision(QRect* qr)	const { return _rect.intersects(*qr);  } //Hitcheck med racket 
	bool checkIfOutside()			const { return _rect.top() > W_HEIGHT; } //Hitcheck om utanför spelplan
	bool getActive()				const { return active; }
	bool getGivingEffect()			const { return givingEffect; }
	bool isVisible()				const { return visible; }
	void setVisible(bool b)				  { visible = b; }

	QTimer* getTimer()				const { return timer; }

	void update();
	virtual void paint(QPainter & painter) = 0;
	virtual void giveEffect(){} //tar massa parametrar pga arv och polymorfism
	virtual void powerupEnded() = 0;


protected:
	QRect _rect;
	float _vel;
<<<<<<< HEAD
	QPixmap _pixmap;
=======
	Boll* _boll;
	QTimer* timer;
	bool givingEffect;
	bool visible;
	bool active;
>>>>>>> e821792e75e2afed81bfb445c6c77d8a46ee0765
};

