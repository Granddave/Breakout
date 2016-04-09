#include "Score.h"

Score::Score()
{
	_score = 0;
}

Score::~Score()
{

}
void Score::addScore()
{
	_score += 100;
}

int Score::getScore() const
{
	return _score;
}

void Score::paint(QPainter& painter, Score& score) const
{
	QFont font;
	font.setPixelSize(30);
	painter.setFont(font);
	painter.drawText(10, 390, QString("Score: "));
	painter.drawText(110, 390, QString::number(score.getScore()));
}

void Score::scoreReset()
{
	_score = 0;
}