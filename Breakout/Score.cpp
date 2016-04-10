#include "Score.h"

Score::Score()
{
	_score = 0;
	_multiplier = 100;
}

Score::~Score()
{

}
void Score::addScore()
{
	_score += POINTS_PER_BLOCKS;
}

int Score::getScore() const
{
	return _score;
}

int Score::getMulti() const
{
	return _multiplier;
}

void Score::resetMulti()
{
	_multiplier = 100;
}

void Score::paint(QPainter& painter, Score& score, Boll& boll) const
{
	QFont font;
	font.setPixelSize(30);
	painter.setFont(font);
	painter.drawText(10, 390, QString("Score: "));
	painter.drawText(400, 390, QString("Multiplier: "));
	painter.drawText(540, 390, QString::number(score.getMulti()));
	painter.drawText(110, 390, QString::number(score.getScore()));

	if (boll.getBottom() > W_HEIGHT || score.getScore() == NUM_OF_BLOCKS * POINTS_PER_BLOCKS)
	{
		font.setPixelSize(60);
		painter.drawText(200, 190, QString("Final Score: "));
		if (!(score.getScore() == NUM_OF_BLOCKS * POINTS_PER_BLOCKS))
		{
			painter.drawText(370, 190, QString::number(score.getScore()));
			return;
		}
		painter.drawText(370, 190, QString::number(score.finalScore()));
	}
}

void Score::scoreReset()
{
	_score = 0;
}

void Score::lowerMulti()
{
	if (_multiplier > 1)
		_multiplier--;
}

int Score::finalScore()
{
	return (_multiplier * _score);
}