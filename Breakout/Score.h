#pragma once
#include <qpainter.h>
#include <string>
#include <boll.h>
#include "defines.h"

class Score
{
public:
	Score();
	~Score();

	void addScore();
	int getScore() const;
	int getMulti() const;
	void resetMulti();
	void paint(QPainter& painter, Score& score, Boll& boll) const;
	void scoreReset();
	void lowerMulti();
	int finalScore();
private:
	int _score;
	int _multiplier;

};