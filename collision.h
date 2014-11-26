/***************** CS360 : Project *******************
 ******** Group 40 : Aniruddha Kumar Sahu (10092) ****
 *****************************************************/
 
#ifndef COLLISION_H
#define COLLISION_H
#include "structure.h"

/* Testing collision between Bullet and Bubble*/
int Test_Bullet_Bubble(RECTA bullet, CIRCLE bubble);

/* Testing collision between Bullet and Bubbles*/
int Test_Bubble_Bubble(CIRCLE  *bub , CIRCLE  *bub1);

/* Testing collision between Ball and Bubble*/
int Test_Ball_Wall(RECTA  ball , RECTA wall);//unused

/* Testing collision between Wall(Game boundary) and Bubble*/
int Test_Bubble_Wall(CIRCLE  bubble , RECTA wall);


bool Test_Ball_Player(RECTA ball,RECTA player);//Unused

/* Testing hit of Bubble and the player bar*/
bool Test_Bubble_Player(CIRCLE bubble,RECTA player);

int Test_Bullet_Egg(RECTA bullet, ESTER_EGG egg);

/* Testing Collision of wall and easter egg*/
int Test_Egg_Wall(ESTER_EGG egg , RECTA wall);

/* Testing hit of Bonus bubbles and the player bar*/
bool Test_Egg_Player(ESTER_EGG egg, RECTA player);


/* Testing collision of Easter eggs and */
int Test_Egg_Bubble(ESTER_EGG egg , CIRCLE  *bub1);

#endif
