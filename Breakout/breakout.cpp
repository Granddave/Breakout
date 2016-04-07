#include "breakout.h"

Breakout::Breakout(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setFixedWidth(W_WIDTH);
	setFixedHeight(W_HEIGHT);

	setMouseTracking(true);
	qDebug() << "HasMouseTracking:" << hasMouseTracking();
	rack = new Racket();
	boll = new Boll();
	spelplan = new QRect(0, 21, W_WIDTH, W_HEIGHT- 21);
	background = new QPixmap("background.png");

	int numX = 10;		//Antal i horisontalled
	int numY = 4
		;		//Antal i vertikalled	
	int heightAdj = 21; //Pixlar mellan top och h�gsta
	int spaceingY = 35; //Pixlar mellan block i vertikalled

	if (_blocks.size() == 0)
	{
		//Skapar och placerar ut blocken
		for (int x = 0; x < numX; x++)
		{
			for (int y = 0; y < numY; y++)
			{
				//Block* n = new Block(x * 50, y * 20);
				Block* n = new Block((x * W_WIDTH / numX) + ((W_WIDTH / numX) - BLOCK_WIDTH) / 2, (y * spaceingY) + heightAdj);
				_blocks.push_back(n);
				qDebug() << x << y;
			}
		}
	}

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(16);

	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));
	connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(startGame()));
}

Breakout::~Breakout()
{
	delete rack;
	delete spelplan;
	delete timer;
	for (int i = 0; i < _blocks.size(); i++)
		delete _blocks[i];
}

void Breakout::paintEvent(QPaintEvent * e)
{
	QPainter p(this);

	p.drawPixmap(0, 0, *background); //bakgrund

	for (int i = 0; i < _blocks.size(); i++)
		_blocks[i]->paint(p);
	rack->paint(p);
	boll->paint(p);
}

void Breakout::mouseMoveEvent(QMouseEvent* e)
{
	rack->setPosition(e->x());
}

void Breakout::mousePressEvent(QMouseEvent* e)
{
}

void Breakout::update() //hitcheck
{
	boll->setHasChangedDir(0);
	boll->update(*spelplan);
	rack->hitCheck(*boll);

	for (int i = 0; i < _blocks.size(); i++)
	{
		_blocks[i]->hitCheck(*boll);
	}

	rack->setPosition(boll->getLeft());

	repaint();
}

void Breakout::startGame() //Placerar ut block
{
	for (int i = 0; i < _blocks.size(); i++)
		_blocks[i]->setActive();

	boll->reset();
	rack->reset();
	repaint();
}
