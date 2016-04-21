#pragma once
#include <qpainter.h>
#include <boll.h>
#include "defines.h"

class Score
{
public:
	Score();
	~Score();
	
	void paint(QPainter& painter, Score& score, Boll& boll) const;

	void addScore()			{ _score += POINTS_PER_BLOCKS; }
	void lowerMulti();
	void reset();
	int finalScore() const	{ return _multiplier * _score; }
	int getScore()   const	{ return _score; }
	int getMulti()   const	{ return _multiplier; }

private:
	int _score;
	int _multiplier;
	QPixmap* _finalScoreboard;
};