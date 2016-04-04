#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <QtWidgets/QMainWindow>
#include "ui_breakout.h"
#include <vector>
#include "Block.h"

class Breakout : public QMainWindow
{
	Q_OBJECT

public:
	Breakout(QWidget *parent = 0);
	~Breakout();

	void paintEvent();

private slots:
	void startGame();

private:
	Ui::BreakoutClass ui;
	std::vector <Block*> _blocks;
};

#endif // BREAKOUT_H
