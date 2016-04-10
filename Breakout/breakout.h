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


class Breakout : public QMainWindow
{
	Q_OBJECT

public:
	Breakout(QWidget *parent = 0);
	~Breakout();

	void paintEvent(QPaintEvent * e);
	void mouseMoveEvent(QMouseEvent* e);
	void mousePressEvent(QMouseEvent* e);
	void keyPressEvent(QKeyEvent* e);

private slots:
	void update();
	void resetGame();
	void startGame();
	void lowMulti();

private:
	Ui::BreakoutClass ui;
	std::vector <Block*> _blocks;
	QTimer* timer;
	QTimer* multiscore;
	Racket* rack;
	Boll* boll;
	QRect* spelplan;
	QPixmap* background;
	bool isPlaying;
	bool isReset;
	Score* score;
	std::vector <Powerup*> _powerups;
};

#endif // BREAKOUT_H
