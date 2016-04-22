#include "breakout.h"

Breakout::Breakout(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	// Start instruktioner
	_startInst = 1;

	//Sätter fast fönsterstorlek
	setFixedWidth(W_WIDTH);
	setFixedHeight(W_HEIGHT);

	//Ljud
	_victory = new QMediaPlayer();
	_victory->setMedia(QUrl("Ljud/victory.mp3"));
	_speed = new QMediaPlayer();
	_speed->setMedia(QUrl("Ljud/starman.wav"));
	_gameover = new QMediaPlayer();
	_gameover->setMedia(QUrl("Ljud/gameover.wav"));

	//Objekt
	_rack = new Racket();
	_boll = new Boll(_speed, _gameover);
	_spelplan = new QRect(0, 21, W_WIDTH, W_HEIGHT- 21);
	_score = new Score();
	
	//Bilder
	_background = new QPixmap("Bilder/background.png");
	_pause = new QPixmap("Bilder/pause.png");
	_pauseback = new QPixmap("Bilder/pauseback.png");
	_instructions = new QPixmap("Bilder/instructions.png");


	//Uppdateringstimer
	_gameTimer = new QTimer(this);
	connect(_gameTimer, SIGNAL(timeout()), this, SLOT(update()));
	_gameTimer->start(16);

	//Timer för multiscore
	_multiscore = new QTimer(this);
	connect(_multiscore, SIGNAL(timeout()), this, SLOT(lowMulti()));

	//Menyknapper
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));
	connect(ui.actionNew, SIGNAL(triggered()), this, SLOT(resetGame()));

	initBlocks();
	resetGame();
}

Breakout::~Breakout() //städar upp
{
	delete _rack;
	delete _boll;
	delete _spelplan;
	delete _background;
	delete _pause;
	delete _pauseback;
	delete _instructions;
	delete _score;
	delete _gameTimer;
	delete _multiscore;
	delete _victory;
	delete _speed;
	delete _gameover;
	for (int i = 0; i < _blocks.size(); i++)
		delete _blocks[i];
	for (int i = 0; i < _powerups.size(); i++)
		delete _powerups[i];
}

void Breakout::paintEvent(QPaintEvent * e)
{
	QPainter p(this);

	//Bakgrund
	p.drawPixmap(0, 0, *_background); 

	//Block 
	for (int i = 0; i < _blocks.size(); i++)
		_blocks[i]->paint(p);

	//Powerups
	if (_powerups.size() > 0)
		for (int i = 0; i < _powerups.size(); i++)
			_powerups[i]->paint(p);


	_rack->paint(p);
	_boll->paint(p);
	_score->paint(p, *_score, *_boll);

	//Pause
	if (_isPaused)
	{
		p.drawPixmap(0, 0, *_pauseback);
		p.drawPixmap(QRect(200, 100, 200, 200), *_pause);
	}

	//Instruktioner
	if (_startInst)
	{
		p.drawPixmap(QRect(155,100,300,200), *_instructions);
		QFont font;
		font.setPixelSize(30);
		p.setFont(font);
		QPen penHText(QColor("#ffffff"));
		p.setPen(penHText);		
		p.drawText(170, 130, QString("Press SPACE to start"));
		p.drawText(190, 170, QString("Press P to pause"));
		p.drawText(185, 210, QString("Press R to restart"));
		p.drawText(170, 250, QString("Hold left mouseBTN"));
		p.drawText(200, 290, QString("to move paddle"));

	}
}

//Sätter racket
void Breakout::mouseMoveEvent(QMouseEvent* e)
{
	_rack->setPosition(e->x());
}

void Breakout::keyPressEvent(QKeyEvent* e)
{
	if (e->key() == Qt::Key_P && _isPaused == 0)
	{
		_victory->stop();
		_isPaused = 1;
		repaint();
		pauseGame();
	}
	else if (e->key() == Qt::Key_P && _isPaused == 1)
	{
		_victory->stop();
		_gameTimer->start(16);
		_multiscore->start(MULTI_COUNTDOWN);
		_isPaused = 0;
		return;
	}

	if (!_isPlaying && !_isReset && e->key() == Qt::Key_Space)
		resetGame();
	else if (e->key() == Qt::Key_R)
	{
		resetGame();
	}
	else if (!_isPlaying && _isReset && e->key() == Qt::Key_Space)
	{
		startGame();
		_startInst = 0;
	}
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
	if (!_isReset && _boll->getIsOnPlayArea())
 		_isPlaying = 1;
	else if (!_isReset && !_boll->getIsOnPlayArea())
		_isPlaying = 0;

	// Inväntar start, låter spelaren välja startposition
	if (!_isPlaying && _isReset)
		_boll->setPos(_rack->getCenter(), _boll->position().y()); // Gör att bollen följer racket 

	// Stanna boll och multiscore om alla block är sönder
	if (_score->getScore() == NUM_OF_BLOCKS * POINTS_PER_BLOCKS)
	{
		_speed->stop();
		_victory->play();
		_multiscore->stop();
		_boll->setVelX(0);
		_boll->setVelY(0);
	}


	// Kollar kollisioner
	_boll->update(*_spelplan, *_multiscore);	//Vägg 
	_rack->hitCheck(*_boll);					//Racket
	
	//Blockhitcheck samt skapar ev powerups
	for (int i = 0; i < _blocks.size(); i++)
	{
		//Kollar block- och bollkollision samt adderar till score om träff
		_blocks[i]->hitCheck(*_boll, *_score);

		//Om blocket har powerup, inte är aktivt och har kvar sin powerup
		if (_blocks[i]->hasPowerup() && !_blocks[i]->isBlockActive() && !_blocks[i]->isPowerupTaken()) 
		{
			_blocks[i]->setPowerupTaken(1);
			srand(time(NULL));

			//Skapar powerup
			int r = rand() % 4; //% n, där n är antalet olika powerups minus en som är implementerade

			if (r == 0 || r == 1)
			{
				Powerup* p = new PowerupSpeed(_blocks[i]->getX(), _blocks[i]->getY(), _boll, _rack);
				_powerups.push_back(p);
			}
			else if (r == 2)
			{
				Powerup* p = new PowerupInvisible(_blocks[i]->getX(), _blocks[i]->getY(), _boll, _rack);
				_powerups.push_back(p);
			}
			else if (r == 3)
			{
				Powerup* p = new PowerupRacket(_blocks[i]->getX(), _blocks[i]->getY(), _boll, _rack);
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
			if (_powerups[i]->checkCollision(_rack->getRect()) && _powerups[i]->isVisible())
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
	_rack->setPosition(_boll->getLeft()); 
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

	_score->reset();
	_rack->reset();
	_boll->reset();
	_speed->stop();
	_victory->stop();
	_gameover->stop();
	_multiscore->stop();

	_isPaused = 0;
	_isReset = 1;
	_isPlaying = 0;
 	repaint();
}

//Startar spelet
void Breakout::startGame() 
{
	_multiscore->start(MULTI_COUNTDOWN); //Startar timern för multiscore
	_isReset = 0;
	_isPlaying = 1;
	_boll->startMoving();
	repaint();
}

void Breakout::pauseGame()
{
	_gameTimer->stop();
	_multiscore->stop();
}