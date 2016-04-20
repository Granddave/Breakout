#pragma once

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
	void lowMulti() const { _score->lowerMulti(); }

private:
	Ui::BreakoutClass ui;
	QRect* _spelplan;
	QPixmap* _background;
	QPixmap* _pause;
	QPixmap* _pauseback;
	QTimer* _gameTimer;
	QTimer* _multiscore;
	Score* _score;
	QMediaPlayer* _victory;
	QMediaPlayer* _speed;
	QMediaPlayer* _gameover;

	Racket* _rack;
	Boll* _boll;
	std::vector <Block*> _blocks;
	std::vector <Powerup*> _powerups;

	bool _isPlaying;
	bool _isReset;
	bool _isPaused;
	bool _startInst;
};
