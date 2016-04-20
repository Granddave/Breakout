#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <QtWidgets/QMainWindow>
#include <qtimer.h>
#include <QMouseEvent>
#include <QKeyEvent>
#include <vector>
#include "ui_breakout.h"

#include "defines.h"
#include "Block.h"
#include "Racket.h"
#include "Boll.h"
#include "Score.h"
#include "powerup.h"
#include "powerupSpeed.h"
#include "powerupInvisible.h"
#include "powerupRacket.h"


class Breakout : public QMainWindow
{
	Q_OBJECT

public:
	Breakout(QWidget *parent = 0);
	~Breakout();

	void paintEvent(QPaintEvent * e);
	void mouseMoveEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent* e);
	void pauseGame();

	void initBlocks();

private slots:
	void update();
	void resetGame();
	void startGame();
	void lowMulti() const { score->lowerMulti(); }

private:
	Ui::BreakoutClass ui;
	QRect* spelplan;
	QPixmap* background;
	QPixmap* pause;
	QPixmap* pauseback;
	QTimer* gameTimer;
	QTimer* multiscore;
	Score* score;
	QMediaPlayer* victory;
	QMediaPlayer* speed;
	QMediaPlayer* gameover;

	Racket* rack;
	Boll* boll;
	std::vector <Block*> _blocks;
	std::vector <Powerup*> _powerups;

	bool isPlaying;
	bool isReset;
	bool isPaused;
	bool startInst;
};

#endif // BREAKOUT_H
