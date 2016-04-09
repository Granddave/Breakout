#pragma once
#include <qpainter.h>
#include <string>

class Score
{
public:
	Score();
	~Score();
	void addScore();
	int getScore() const;
	void paint(QPainter& painter, Score& score) const;
	void scoreReset();
private:
	int _score;

};