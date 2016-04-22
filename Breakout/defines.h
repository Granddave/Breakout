#include <QtDebug>
#include <math.h>

#define PI					(3.14159265359)
#define W_WIDTH				600 //Ändra i QT-creator först 
#define W_HEIGHT			400 //och justera sedan här, de är ej länkade
#define BLOCK_WIDTH			50
#define BLOCK_HEIGHT		20
#define BLOCKS_NUM_X		10
#define BLOCKS_NUM_Y		4
#define NUM_OF_BLOCKS		(BLOCKS_NUM_X * BLOCKS_NUM_Y)
#define POINTS_PER_BLOCKS	100

#define BOLL_BASESPEED		4
#define BOLL_POWERUPSPEED	6
#define POWERUP_TIME_MS		10000
#define MULTI_COUNTDOWN     2000

#define powerupDB			0
#define AUTOPLAY			0 //Racket följer boll