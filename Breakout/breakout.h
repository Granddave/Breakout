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
	void keyPressEvent(QKeyEvent* e);

	void initBlocks();

private slots:
	void update();
	void resetGame();
	void startGame();
	void lowMulti();

private:
	Ui::BreakoutClass ui;
	QRect* spelplan;
	QPixmap* background;
	QTimer* timer;
	QTimer* multiscore;
	Score* score;

	Racket* rack;
	Boll* boll;
	std::vector <Block*> _blocks;
	std::vector <Powerup*> _powerups;

	bool isPlaying;
	bool isReset;
};

#endif // BREAKOUT_H
