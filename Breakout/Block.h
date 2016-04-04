#pragma once

#include <QPainter>
#include "defines.h"
#include "Boll.h"

class Block
{
public:
	Block(int x, int y);
	
	void paint(QPainter& painter) const;
	void hitCheck(Boll& boll);
	void setActive();

	int getRight(){ return _x + _width; }
	int getLeft(){ return _x; }
	int getTop(){ return _y; }
	int getBottom(){ return _y + _height; }


	inline int getWidth() const;
	inline int getHeight() const;


private: 
	int _x;
	int _y;
	int _width;
	int _height;
	
	bool _isActive;
};

