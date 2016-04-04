#include "breakout.h"

Breakout::Breakout(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.startButton, SIGNAL(pressed()), this, SLOT(startGame()));
}

Breakout::~Breakout()
{

}

void Breakout::paintEvent()
{
	QPainter p;
	for (int i = 0; i < _blocks.size(); i++)
		_blocks[i]->paint(p);
}

void Breakout::startGame()
{
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 2; y++)
		{
			Block* n = new Block((x * 50) + 10, (y * 20) + 10);
			_blocks.push_back(n);
		}
	}
	repaint();
}
