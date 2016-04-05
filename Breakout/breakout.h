#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <QtWidgets/QMainWindow>
#include <qtimer.h>
#include <QMouseEvent>
#include <vector>
#include "ui_breakout.h"

#include "defines.h"
#include "Block.h"
#include "Racket.h"
#include "Boll.h"


class Breakout : public QMainWindow
{
	Q_OBJECT

public:
	Breakout(QWidget *parent = 0);
	~Breakout();

	void paintEvent(QPaintEvent * e);
	void mouseMoveEvent(QMouseEvent* e);
	void mousePressEvent(QMouseEvent* e);

private slots:
	void update();
	void startGame();

private:
	Ui::BreakoutClass ui;
	std::vector <Block*> _blocks;
	QTimer* timer;
	Racket* rack;
	Boll* boll;
	QRect* spelplan;

};

#endif // BREAKOUT_H
