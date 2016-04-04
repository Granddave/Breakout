#pragma once

#include <QPainter>
#include "defines.h"

class Block
{
public:
	Block(int x, int y);
	void paint(QPainter& painter) const;

	inline int getWidth() const;
	inline int getHeight() const;

private: 
	int _x;
	int _y;
	int _width;
	int _height;
	
	bool _isWhole;
};

