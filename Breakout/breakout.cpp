#include "breakout.h"

Breakout::Breakout(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setFixedWidth(W_WIDTH);
	setFixedHeight(W_HEIGHT);

	setMouseTracking(true);
	qDebug() << hasMouseTracking();
	rack = new Racket();

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(10);

	connect(ui.startButton, SIGNAL(pressed()), this, SLOT(startGame()));
}

Breakout::~Breakout()
{
}

void Breakout::paintEvent(QPaintEvent * e)
{
	QPainter p(this);
	for (int i = 0; i < _blocks.size(); i++)
		_blocks[i]->paint(p);
	rack->paint(p);
}

void Breakout::mouseMoveEvent(QMouseEvent* e)
{
	rack->setPosition(e->x());
	qDebug() << e->x();
}

void Breakout::mousePressEvent(QMouseEvent* e)
{
}

void Breakout::update() //Kollar hitcheck
{
	repaint();
}

void Breakout::startGame() //Placerar ut block
{
	int numX = 10;		//Antal i horisontalled
	int numY = 3;		//Antal i vertikalled	
	int heightAdj = 20; //Pixlar mellan top och högsta
	int spaceingY = 25; //Pixlar mellan block i vertikalled

	if (_blocks.size() == 0)
	{
		//Skapar och placerar ut blocken
		for (int x = 0; x < numX; x++)
		{
			for (int y = 0; y < numY; y++)
			{
				Block* n = new Block((x * W_WIDTH / numX) + ((W_WIDTH / numX) - BLOCK_WIDTH) / 2, (y * spaceingY) + heightAdj);
 				_blocks.push_back(n);
				qDebug() << x << y;
			}
		}
	}
	repaint();
}
