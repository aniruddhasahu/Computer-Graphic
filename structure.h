/***************** CS360 : Project *******************
 ******** Group 40 : Aniruddha Kumar Sahu (10092) ****
 *****************************************************/
#ifndef STRUCTURE_H
#define STRUCTURE_H

// OpenGL includes..
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

//Other Libs
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include <malloc.h>
#include <string.h>

#include <vector>

//Using Namespace
using std::vector;
using std::string;

//Game Levels
#define LEVEL0 0
#define LEVEL1 1
#define LEVEL2 2
#define LEVEL3 3
#define LEVEL4 4

//Wall-Bubble-Player Collision
#define FROM_RIGHT      1 
#define FROM_LEFT       2 
#define FROM_TOP        3 
#define FROM_BOTTOM     4

//Bubble-Bubble Collision cases
#define MOVE_L      1
#define MOVE_R      2
#define MOVE_T      3
#define MOVE_B      4
#define MOVE_LB      5
#define MOVE_RB      6
#define MOVE_LT      7
#define MOVE_RT      8

//Defining  Game states
#define GAME_START     	0 
#define GAME_WIN     		1
#define GAME_RUNNING 		2
#define TRY_AGAIN 			3
#define GAME_OVER     	-1
#define GAME_PAUSE			5

// Structure of objects

/* Structure for player bar*/
struct RECTA{ 
        float left,top,right,bottom; 
};

/* Structure for Bubbles*/
struct CIRCLE{
	float Cx, Cy, R, Xspeed, Yspeed, Color[3];
};

struct CIRCLE_ALT{  // Not Used
		float radii;
		int sides;
};

/* Structure for Easter egg*/
struct ESTER_EGG{
		CIRCLE Egg;//= {0 ,0 ,10, 0, 0, {0.0f, 0.0f, 0.0f}};
		int show;// = 0; 
};

//statice Fields
static int WINDOW_WIDTH ,WINDOW_HEIGHT, WINDOW_HEIGHTB;

/* Speed records for bubbles and bullets*/
static int playerResult=0;
static float Xspeed=1,Yspeed=1;
static float Xspeed1=-1,Yspeed1=1; 
static float Xspeed2=1,Yspeed2=1; 
static float Bulletspeed=4; 
static float delta=1; 
static int mouse_x=20;

/* Game States*/
static int GameState = GAME_START; 
static int GameLevel = LEVEL0;
static int LifeLine = 3;

/* Keeping player's score*/
static int preTotalScore =0;
static int CurrTotalScore =0;
static int BonusScore = 0;

/* Accounting times*/
static time_t startTime;
static time_t pauseTime;
static time_t resumeTime;

static char string1 [100];


static vector<RECTA> bullets;
static vector<CIRCLE> bubbles;
//static vector<ESTER_EGG> eEggs;


//static CIRCLE bub1, bub2;
static int splitFlag = 0;
//RECTA ball={100,100,120,120};
static RECTA wall ;
static RECTA player_1 ={0,490,40,500}; 

//Draw functions
/* Drawing all premitives*/
void DrawRectangle(RECTA  rect);
//void DrawCircle1(CIRCLE_ALT circle);
void drawCircle(CIRCLE circle);

/* Drawing text*/
void drawText(char*string1,int x,int y);
void drawEgg(CIRCLE c);

//Other functions
//void splitBubble(CIRCLE c0);
/* Functions for screen shot*/
bool save_screenshot(string filename, int w, int h);

#endif
