/*******************************************************************************
*    Stefano Mantini    W12020151
*
*    Small Embedded Systems "TiltSnake"
*
*******************************************************************************/
#include "includes.h"
#include <math.h>

//*********************DEFINE CONSTANTS AND BOUNDARIES FOR GAME*****************

int SCORE;
int SNKLENGTH;
int LIVESLEFT;
int MGAMERUNNING;
int SNAKESPEED;
int FOODX;
int FOODY;

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

#define STARTXVALUE 64
#define STARTYVALUE 64

//
#define OBSTX0 45
#define OBSTY0 30
#define OBSTX1 80
#define OBSTY1 60


typedef struct {
	int x;
	int y;
}
snakeSegment;
snakeSegment snake[200];


/******************************************************************************
 * Function Name: Dly100us
 * Parameters: void *arg
 * Return: void
 * Description: implements the cpu clock at 100microseconds
 *		
 *****************************************************************************/
void Dly100us(void *arg) {
	volatile Int32U Dly = (Int32U)arg, Dly100;
	for (;Dly;Dly--)
	    for (Dly100 = 250; Dly100; Dly100--);
}


//***************************METHODS FOR THE SNAKE*****************************

/******************************************************************************
 * Function Name: initSnake
 * Parameters: none
 * Return: none
 * Description: The snake is initialised in this function
 *
 *****************************************************************************/
void initSnake () {
	snake[0].x = STARTXVALUE;
	snake[0].y = STARTYVALUE;
        
	int i ;
	for (i = 1; i <= SNKLENGTH ; i++ ) {
		snake[i].x= snake[i-1].x + 1;
		snake[i].y= snake[i-1].y;
	}
}


/*****************************************************************************
 * Function Name: renderSnake
 * Parameters:
 * Return: none
 * Description: draws the actual pixels of the snake the Snake
 *
 *************************************************************************/
void renderSnake() {

	int i;
	LCDDrawFilledRectangle(snake[0].x + 1,snake[0].y + 1,snake[0].x - 1,snake[0].y - 1,BLACK);
	for (i = 1; i<= SNKLENGTH; i++) {
		LCDDrawPixel(snake[i].x, snake[i].y, BLUE);
	}
	LCDDrawFilledRectangle(OBSTX0,OBSTY0,OBSTX1,OBSTY1,GREEN);
	//Draws the Obstacle
	LCDDrawRectangle(OBSTX0,OBSTY0,OBSTX1,OBSTY1,BLACK);
	//Draws the Obstacle
}


/*************************************************************************
 * Function Name: directionSignal
 * Parameters: 
 * Return: none
 * Description: Reads the signal from accelerometer so it can be read as UDLR
 *
 *************************************************************************/
int directionSignal(int CURRENTSIGNAL) {
	int accXValue = accelerometerRead(X_CHANNEL);
	int accYValue = accelerometerRead(Y_CHANNEL);
	if (accXValue < 490  || buttonRead(JS_LEFT)){
          return  2;
        }
	if (  accXValue > 540|| buttonRead(JS_RIGHT)){
	            return  3;
        }
	if (accYValue > 540 || buttonRead(JS_DOWN)){
	            return 1;
        }
	if (accYValue < 490 || buttonRead(JS_UP)){
	            return 0; 
        }
        else
        return CURRENTSIGNAL;
}


/*****************************************************************************
 * Function Name: clearScreen()
 * Parameters: 
 * Return: none
 * Description: when the game has executed, this resets the game and clears 
 * the screen ready for another game
 *
 ****************************************************************************/
void clearScreen() {
	printf( "\f" );
	LCDDrawRectangle(3,1,130,128,BLACK);
	LCDDrawLine( 17,1,17,131,BLACK);
	LCDTextSetPos(1,1);
	printf("Snakes:%d", LIVESLEFT);
	LCDTextSetPos(12,1);
	printf("SCORE:%d", SCORE);
}


/*****************************************************************************
 * Function Name: collisionDetection()
 * Parameters: 
 * Return: none
 * Description: Self Collisions
 * detects collisions of the snake with its self by comparing the
 * array with its self and deducts a life if it detects a collision
 * Description: Obstacle Collisions
 * uses OBSTX0/1, OBSTY0/1 as coordinates to check if the head of the snake 
 * has collided
 * Description: Boundary Collisions
 * 
 ****************************************************************************/
void collisionDetection() {
	int i;
	int j;
	for (i = 1; i<=SNKLENGTH; i++) {
		if (snake[0].x == snake[i].x && snake[0].y == snake[i].y) {
			LIVESLEFT -= 1;
			MGAMERUNNING = 0; 
		} //detects if there are any self collisions
	}
	for (j = OBSTX0 ; j<=OBSTX1; j++) {
		if ((snake[0].y == OBSTY1 && snake[0].x == j) || 
                    (snake[0].y == OBSTY0 && snake[0].x == j) ) {
			LIVESLEFT -= 1;
			MGAMERUNNING = 0;
		} //detects along the x axis of the object
	}
	for (j = OBSTY0 ; j<= OBSTY1; j++) {
		if ((snake[0].y == j && snake[0].x == OBSTX1) || 
                    (snake[0].y == j && snake[0].x == OBSTX0) ) {
			LIVESLEFT -= 1;
			MGAMERUNNING = 0;
		}
	}
}

//***************************Other methods************************************

/*****************************************************************************
 * Function Name: buttonPoll()
 * Parameters: 
 * Return: none
 * Description: polls BUT_1 pending on the user to start the game
 *
 *****************************************************************************/
void buttonPoll() {
	bool start = false;
	while (start == false) {
		if (buttonRead(BUT_1))
		      start = true;
	}
}


/******************************************************************************
 * Function Name: snakeSpeedChange()
 * Parameters: 
 * Return: none
 * Description: Makes the snake's speed proportionate to the value of the POT
 *
 *****************************************************************************/
void snakeSpeedChange() {
	SNAKESPEED = potentiometerRead();
}


/******************************************************************************
 * Function Name: spawnFood()
 * Parameters: 
 * Return: none
 * Description: Places food to a valid position on the screen
 *
 *****************************************************************************/
void spawnFood() {
	FOODX =  (rand() % 128);
	FOODY =  (rand() % 128);
	LCDDrawFilledRectangle(FOODX + 1,FOODY + 1,FOODX- 1,FOODY - 1,RED);
}


/******************************************************************************
 * Function Name: eatFood()
 * Parameters: 
 * Return: none
 * Description: sorts the actual eating as well as incrementing snakelength,
 * score and spawning the next food
 *
 *****************************************************************************/
void eatFood() {
	if (snake[0].x == FOODX && snake[0].y == FOODY ) {
		SCORE += 5;
		SNKLENGTH += 30;
		LCDTextSetPos(12,1);
		printf("SCORE:%d", SCORE);
		spawnFood();
	}
}


/******************************************************************************
 * Function Name: moveSnake
 * Parameters: int x, int y, int length, char CURRENTSIGNAL
 * Return: none
 *
 * Description: Moves the last pixel of the snake and places it in front, 
 * moving the snake
 *
 *****************************************************************************/
void moveSnake(int direction) {
	LCDDrawPixel(snake[SNKLENGTH].x, snake[SNKLENGTH].y, WHITE);
	LCDDrawPixel(snake[SNKLENGTH -1].x, snake[SNKLENGTH - 1].y, WHITE);

	int s;

	LCDDrawFilledRectangle(snake[0].x + 1,snake[0].y + 1,
                               snake[0].x - 1,snake[0].y - 1,WHITE);
        
        for (s = SNKLENGTH - 1; s>=1; s--) {
	snake[s].x= snake[s-1].x;
	snake[s].y= snake[s-1].y;
        
	}
        
	if (direction == 0 && snake[0].x >=19) {
		snake[0].x --;
		if (snake[0].x ==19) {
			LIVESLEFT -= 1;
			MGAMERUNNING = 0;
		}
	}
	if (direction == 1 && snake[0].x <= 128) {
		snake[0].x ++;
		if (snake[0].x ==128) {
			LIVESLEFT -= 1;
			MGAMERUNNING = 0;
		}
	}
	if (direction == 2 && snake[0].y >=3) {
		snake[0].y --;
		if (snake[0].y ==3) {
			LIVESLEFT -= 1;
			MGAMERUNNING = 0;
		}
	}
	if (direction == 3 && snake[0].y <=127) {
		snake[0].y ++;
		if (snake[0].y ==127) {
			LIVESLEFT -= 1;
			MGAMERUNNING = 0;
		}
	}
	LCDDrawFilledRectangle(snake[0].x + 1,snake[0].y + 1,
                               snake[0].x - 1,snake[0].y - 1,BLACK);
	LCDDrawPixel(snake[2].x, snake[2].y, BLUE);
	LCDDrawPixel(snake[3].x, snake[3].y, BLUE);
	Dly100us((void*)SNAKESPEED);
}


/*************************************************************************
 * Function Name: endGame()
 * Parameters: 
 * Return: none
 *
 * Description: Creates an overlay to indicate the player ran out of lives, 
 * displays the score and gives instructions of how to play again
 *
 *************************************************************************/
void endGame() {
	LCDDrawRectangle(4,21,128,125,WHITE);
	LCDTextSetPos(1,1);
	printf("Snakes:%d ", 0);
	LCDTextSetPos(1,5);
	printf("You ran out of lives");
	LCDTextSetPos(1,7);
	printf("Total score: %d", SCORE);
	LCDTextSetPos(1,9);
	printf("BUT_1 to Try again");
	buttonPoll();
	LIVESLEFT = 5;
}


/*************************************************************************
 *
 * Function Name: main
 * Parameters: none
 * Return: none
* Description: Main Method
 *************************************************************************/
int main(void) {
	LIVESLEFT = 5;
	int NEWSIGNAL;
	int CURRENTSIGNAL;
        
	while(true) {
		InitClock();
		GPIOInit();
		buttonsInit();
		accelerometerInit();
		potentiometerInit();
		LCDPowerUpInit((pInt8U)IAR_Logo.pPicStream);
		LCDSetBacklight(BACKLIGHT_ON);
		Dly100us((void*)5000);
		LCDSetFont( &Terminal_6_8_6, BLACK, WHITE );
		LCDSetWindow( 0, 0, 131, 131 );
		printf( "\f" );
		LCDDrawRectangle(3,1,130,128,BLACK);
		LCDDrawLine( 17,1,17,131,BLACK);
		LCDTextSetPos(1,1);
		printf("SNAKES:%d", LIVESLEFT);
		LCDTextSetPos(12,1);
		printf("SCORE:%d", SCORE);
                
		while (LIVESLEFT >= 0) {
			SNKLENGTH = 20;
			initSnake();
			renderSnake();
			buttonPoll();
			NEWSIGNAL = 0;
			MGAMERUNNING = 1;
			CURRENTSIGNAL = UP;
			spawnFood();
			while(MGAMERUNNING) {
				NEWSIGNAL = directionSignal(CURRENTSIGNAL);
				CURRENTSIGNAL = NEWSIGNAL;
				moveSnake(CURRENTSIGNAL);
				snakeSpeedChange();
				eatFood();
				collisionDetection();
			}
			clearScreen();
		}
		endGame();
	}
}