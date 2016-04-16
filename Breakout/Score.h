#pragma once
#include <qpainter.h>
#include <string>
#include <boll.h>
#include "defines.h"

class Score
{
public:
	Score();
	~Score(){}
	
	void paint(QPainter& painter, Score& score, Boll& boll) const;

	void addScore()			{ _score += POINTS_PER_BLOCKS; }
	void resetMulti()		{ _multiplier = 100; }
	void scoreReset()		{ _score = 0; }
	void lowerMulti();
	int getScore()   const	{ return _score; }
	int getMulti()   const	{ return _multiplier; }
	int finalScore() const	{ return _multiplier * _score; }
	void reset() { scoreReset(); resetMulti(); }

private:
	int _score;
	int _multiplier;

};