#include "breakout.h"

Breakout::Breakout(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//Sätter fast fönsterstorlek
	setFixedWidth(W_WIDTH);
	setFixedHeight(W_HEIGHT);

	rack = new Racket();
	boll = new Boll();
	spelplan = new QRect(0, 21, W_WIDTH, W_HEIGHT- 21);
	background = new QPixmap("background.png");
	score = new Score();

	initBlocks();
	resetGame();

	//Uppdateringstimer
	gameTimer = new QTimer(this);
	connect(gameTimer, SIGNAL(timeout()), this, SLOT(update()));
	gameTimer->start(16);

	//Timer för multiscore
	multiscore = new QTimer(this);
	connect(multiscore, SIGNAL(timeout()), this, SLOT(lowMulti()));

	//Menyknapper
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));
	connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(resetGame()));
}

Breakout::~Breakout() //städar upp
{
	delete spelplan;
	delete background;
	delete gameTimer;
	delete multiscore;
	delete score;
	delete rack;
	delete boll;
	for (int i = 0; i < _blocks.size(); i++)
		delete _blocks[i];
	for (int i = 0; i < _powerups.size(); i++)
		delete _powerups[i];
}

void Breakout::paintEvent(QPaintEvent * e)
{
	QPainter p(this);

	//bakgrund
	p.drawPixmap(0, 0, *background); 

	//Målar block 
	for (int i = 0; i < _blocks.size(); i++)
		_blocks[i]->paint(p);

	//Målar powerups
	if (_powerups.size() > 0)
		for (int i = 0; i < _powerups.size(); i++)
			_powerups[i]->paint(p);


	rack->paint(p);
	boll->paint(p);
	score->paint(p, *score, *boll);
}

void Breakout::mouseMoveEvent(QMouseEvent* e)
{
	rack->setPosition(e->x());
}

void Breakout::keyPressEvent(QKeyEvent* e)
{
	if (!isPlaying && !isReset && e->key() == Qt::Key_Space)
		resetGame();
	else if (e->key() == Qt::Key_R)
		resetGame();
	else if (!isPlaying && isReset && e->key() == Qt::Key_Space)
		startGame();
}


//Sätter ut blocken första gången. 
//Körs endast när spelet startas första gången 
void Breakout::initBlocks() 
{
	int heightAdj = 25;					//Pixlar mellan spelplanens top och högsta blocket
	int spaceingY = BLOCK_HEIGHT + 15;  //Pixlar mellan block i vertikalled

	if (_blocks.size() == 0)
	{
		//Skapar och placerar ut blocken
		for (int x = 0; x < BLOCKS_NUM_X; x++)
		{
			for (int y = 0; y < BLOCKS_NUM_Y; y++)
			{
				//Skapar och sätter ut blocken, sedan lägger till i blockarrayen
				Block* n = new Block((x * W_WIDTH / BLOCKS_NUM_X) + ((W_WIDTH / BLOCKS_NUM_X) - BLOCK_WIDTH) / 2, (y * spaceingY) + heightAdj);
				_blocks.push_back(n);
				qDebug() << x << y;
			}
		}
	}
}

//Körs när uppdateringstimern get timeout.
void Breakout::update()
{
	srand(time(NULL));

	// Kollar om spelet är igång
	if (!isReset && boll->getIsOnPlayArea())
 		isPlaying = 1;
	else if (!isReset && !boll->getIsOnPlayArea())
		isPlaying = 0;

	// Inväntar start, låter spelaren välja startposition
	if (!isPlaying && isReset)
		boll->setpos(rack->getCenter(), boll->position().y()); // Gör att bollen följer racket 

	// Stanna boll och multiscore om alla block är sönder
	if (score->getScore() == NUM_OF_BLOCKS * POINTS_PER_BLOCKS)
	{
		multiscore->stop();
		boll->setxvel(0);
		boll->setyvel(0);
	}


	// Kollar kollisioner
	boll->update(*spelplan, *multiscore);	//Vägg 
	rack->hitCheck(*boll);					//Racket
	
	//Blockhitcheck samt skapar ev powerups
	for (int i = 0; i < _blocks.size(); i++)
	{
		//Kollar block- och bollkollision samt adderar till score om träff
		_blocks[i]->hitCheck(*boll, *score);

		//Om blocket har powerup, inte är aktivt och har kvar sin powerup
		if (_blocks[i]->hasPowerup() && !_blocks[i]->isBlockActive() && !_blocks[i]->isPowerupTaken()) 
		{
			_blocks[i]->setPowerupTaken(1);
			srand(time(NULL));

			//Skapar powerup
			int r = rand() % 1; //% n, där n är antalet olika powerups minus en som är implementerade

			if (r == 0)
			{
				Powerup* p = new PowerupSpeed(_blocks[i]->getX(), _blocks[i]->getY(), boll);
				_powerups.push_back(p);
			}
			else if (r == 1)
			{
				Powerup* p = new PowerupSpeed(_blocks[i]->getX(), _blocks[i]->getY(), boll);
				_powerups.push_back(p);
			}
		}
	}

	//Uppdaterar powerups och ger effekt
	if (_powerups.size() != 0) 
	{
		for (int i = 0; i < _powerups.size(); i++)
		{
			//Flyttar powerup nedåt
			_powerups[i]->update(); 
			

			//Kollar ev. kollision med racket 
			if (_powerups[i]->checkCollision(rack->getRect()) && _powerups[i]->isVisible())
			{
				_powerups[i]->setVisible(0);
				_powerups[i]->giveEffect();
			}
			//Kollar ev. kollision med spelplanens nedre kant
			else if (_powerups[i]->checkIfOutside() && _powerups[i]->isVisible())
			{
				//Tar bort poweupen från minnet samt vektor (den har inte gett någon effekt)
				delete _powerups[i];
				_powerups.erase(_powerups.begin() + i);
			}
			//Om timern har tickat klart
			else if (_powerups[i]->getTimer()->remainingTime() == -1 && !_powerups[i]->isVisible())
			{
				//Återställ den effekt den tidigare orsakat och radera från minne samt vektor
				_powerups[i]->powerupEnded();
				delete _powerups[i];
				_powerups.erase(_powerups.begin() + i);
			}
		}
	}
	

	//gör att racket följer bollen för debug
#if AUTOPLAY //Ändra i defines.h för att aktivera
	rack->setPosition(boll->getLeft()); 
#endif
	repaint();
}

//Återställer hela spelplanen
void Breakout::resetGame() 
{
	//Återställer alla block
	for (int i = 0; i < _blocks.size(); i++) 
		_blocks[i]->reset();

	//Återställer ev. powerups
	if (_powerups.size() > 0)
		for (int i = 0; i < _powerups.size(); i++)
		{
			delete _powerups[i];
			_powerups.erase(_powerups.begin() + i);
		}

	score->scoreReset();
	score->resetMulti();
	rack->reset();
	boll->reset();

	isReset = 1;
	isPlaying = 0;
 	repaint();
}

//Startar spelet
void Breakout::startGame() 
{
	multiscore->start(2000); //Startar timern för multiscore
	isReset = 0;
	isPlaying = 1;
	boll->startMoving();
	repaint();
}

