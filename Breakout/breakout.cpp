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
	score = new Score();


	int heightAdj = 21;  //Pixlar mellan top och högsta
	int spaceingY = 35;  //Pixlar mellan block i vertikalled

	if (_blocks.size() == 0)
	{
		//Skapar och placerar ut blocken
		for (int x = 0; x < BLOCKS_NUM_X; x++)
		{
			for (int y = 0; y < BLOCKS_NUM_Y; y++)
			{
				//Block* n = new Block(x * 50, y * 20);
				Block* n = new Block((x * W_WIDTH / BLOCKS_NUM_X) + ((W_WIDTH / BLOCKS_NUM_X) - BLOCK_WIDTH) / 2, (y * spaceingY) + heightAdj);
				_blocks.push_back(n);
				qDebug() << x << y;
			}
		}
	}
	resetGame();

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update()));
	timer->start(16);

	multiscore = new QTimer(this);
	connect(multiscore, SIGNAL(timeout()), this, SLOT(lowMulti()));

	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));
	connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(resetGame()));

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

	if (_powerups.size() > 0)
	{
		for (int i = 0; i < _powerups.size(); i++)
			_powerups[i]->paint(p);
	}

	rack->paint(p);
	boll->paint(p);
	score->paint(p, *score, *boll);
}

void Breakout::mouseMoveEvent(QMouseEvent* e)
{
	rack->setPosition(e->x());
}

void Breakout::mousePressEvent(QMouseEvent* e)
{
}

void Breakout::keyPressEvent(QKeyEvent* e)
{
	if (!isPlaying && !isReset && e->key() == Qt::Key_Space)
	{
		resetGame();
	}
	else if (!isPlaying && isReset && e->key() == Qt::Key_Space)
		startGame();
	else if (e->key() == Qt::Key_R)
		resetGame();
}

void Breakout::update() //hitcheck
{
	srand(time(NULL));
	if (!isReset && boll->getIsOnPlayArea())// && (boll->xvel() != 0 && boll->yvel() != 0))
 		isPlaying = 1;
	else if (!isReset && !boll->getIsOnPlayArea())
		isPlaying = 0;

	if (!isPlaying && isReset)
		boll->setpos(rack->getCenter(), boll->getTop()); // Gör att bollen följer racket 
	if (score->getScore() == NUM_OF_BLOCKS * POINTS_PER_BLOCKS)
	{
		multiscore->stop();
		boll->setxvel(0);
		boll->setyvel(0);
	}

	boll->update(*spelplan, *multiscore);  // Kollar kollision med vägg
	boll->setHasChangedDir(0);
	rack->hitCheck(*boll);	  // Kollar kollision med racket

	for (int i = 0; i < _blocks.size(); i++)
	{
		_blocks[i]->hitCheck(*boll, *score);

		if (_blocks[i]->hasPowerup() && !_blocks[i]->isBlockActive() && !_blocks[i]->isPowerupTaken()) 
		{
			_blocks[i]->setPowerupTaken(1);
			srand(time(NULL));
			int r = rand() % 1; //% n, där n är antalet olika powerups minus en som är implementerade

			if (r == 0)
			{
				Powerup* p = new PowerupSpeed(_blocks[i]->getX(), _blocks[i]->getY());
				_powerups.push_back(p);
			}
			else if (r == 1)
			{
				Powerup* p = new PowerupSpeed(_blocks[i]->getX(), _blocks[i]->getY());
				_powerups.push_back(p);
			}
		}
	}
	
	if (_powerups.size() != 0) 
	{
		for (int i = 0; i < _powerups.size(); i++)
		{
			_powerups[i]->update(); // Flyttar powerup

			if (_powerups[i]->checkCollision(rack->getRect())) // Kollar ev. kollision
			{

				//Ger sin effekt här

				//Tar bort powerup
				delete _powerups[i]; 
				_powerups.erase(_powerups.begin() + i);
			}
		}
	}
	

	//rack->setPosition(boll->getLeft()); //gör att racket följer bollen

	repaint();
}

void Breakout::resetGame() //Placerar ut block
{
	for (int i = 0; i < _blocks.size(); i++)
		_blocks[i]->reset();

	score->scoreReset();
	score->resetMulti();
	rack->reset();
	boll->reset();
	isReset = 1;
	isPlaying = 0;
 	repaint();
}

void Breakout::startGame()
{
	multiscore->start(2000);
	isReset = 0;
	isPlaying = 1;
	boll->startMoving();
	repaint();
}

void Breakout::lowMulti()
{
	score->lowerMulti();
}