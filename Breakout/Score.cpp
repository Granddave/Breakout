#include "Score.h"

Score::Score()
{
	reset();
    _finalScoreboard = new QPixmap(":/Bilder/instructions.png");
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

	if (boll.position().top() > W_HEIGHT || score.getScore() == NUM_OF_BLOCKS * POINTS_PER_BLOCKS)
	{
		painter.drawPixmap(QRect(155, 100, 300, 200), *_finalScoreboard);
		QFont font;
		font.setPixelSize(30);
		painter.setFont(font);
		QPen penHText(QColor("#ffffff"));
		painter.setPen(penHText);
		painter.drawText(170, 255, QString("Press R to restart"));
		font.setPixelSize(60);
		painter.drawText(170, 225, QString("Final Score: "));
		painter.drawText(220, 155, QString("GAME OVER!"));

		if (!(score.getScore() == NUM_OF_BLOCKS * POINTS_PER_BLOCKS))
		{
			painter.drawText(330, 225, QString::number(score.getScore()));
			return;
		}
		painter.drawText(330, 225, QString::number(score.finalScore()));
	}
}

void Score::lowerMulti()
{
	if (_multiplier > 1)
		_multiplier--;
}

void Score::reset()
{	
	_multiplier = 100;
	_score = 0;
}

Score::~Score()
{
	delete _finalScoreboard;
}
