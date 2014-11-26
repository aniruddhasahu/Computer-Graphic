
				CS360 - Bubble Trouble
	Group 40 : Aniruddha Sahu
	--------------------------------------
	
	->This folder contains following files: 
		0) README.txt
		1) main.cpp
		2) structure.h
		3) structure.cpp
		4) collision.h
		5) collision.cpp
		6) Makefile
		7) group_40.pdf (Presentation)
		
		 and some screen shots of the game.
----	
	 
	-> How to use these (On Linux): run following command in the terminal -
	
					$ make
		
		and to run the game:
		
					$ ./bubbleTrouble
----	
		
	 -> How to play the game : 
			1) Click on the play button.
			2) The player bar can be controlled by mouse or Left and Right arrow key 
			   and used to move it horizontally.	
			3) To shoot the ball click 'Left' mouse button or SPACE key.
			4) Only after all the balls on the screen disaapear (been shot),
			   then you can clear the level.
			5) There is time limit, which is indicated by 'Time Bar' below.
			6) If any bubble touches the player bar, the game will be over for the level.
			7) And there are 4 levels in the game.
			8) To exit from the game press 'Esc' button.
			
-----
Documentation
------
		All functions have been explained in files itself.
		-> main functions used :
			1) Render() : For redering the game. It triggers the game in different stages
			  (GameStage : GAME_START, GAME_RUNNING, GAME_WIN and GAME_OVER) and Game Levels.
				It checks the conditions, when 'Bubble' hits the 'wall' (Window boundary), the 'floor'
				and 'Bullets'.
				
			2) Timer(int) : time Callback function, which triggered every 2 millisecond.
				 It manages the vectors for 'Bullets' and 'Bubbles', which are needed to be rendered 
				 and popped out of the screen.
			
			3) muouseFunc(int,int,int,int) : For controlling mouse motions.
			
			4) Drawing objects:
					DrawRectangle(RECTA  rect) 
					drawCircle(CIRCLE circle)
					drawText(char*string,int x,int y)
					
			5) splitBubble(CIRCLE c0) : Splits the bubble into two on hitting bubble from bullet.
				 It pops out original bubble from the vector and pushes new bubbles into it.
				 
			6) Checking hitting conditions:
					int Test_Bullet_Bubble(RECTA bullet, CIRCLE bubble) : for Bullet and bubble
					int Test_Bubble_Wall (CIRCLE  bubble , RECTA wall) : for bubble and game boundary
					bool Test_Bubble_Player(CIRCLE bubble,RECTA player) : for Bubble and player bar.
				 
				 
				 
