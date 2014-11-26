/***************** CS360 : Project *******************
 ******** Group 40 : Aniruddha Kumar Sahu (10092) ****
 *****************************************************/
#include "structure.h"
#include "collision.h"
#include <time.h>
#include "time.h"

#define GAME_WINDOW  100.0f
/********** Method Declaration ********/
void keyboard(unsigned char key, int x, int y);
void inputKey(int key, int x, int y);
void upkey(int key, int x, int y);
void mouseFunc(int button, int state, int x, int y);
void MouseMotion(int x,int y);
void Setting(void);
void reshape (int w, int h);
void Timer(int v);
void Render();
/* Function splits bubbles into two*/
void splitBubble(CIRCLE c0);

/* Random Bonus bubble generator*/
void eggGen(int N);


//Two Temp bubbles.
CIRCLE bub1, bub2;
GLfloat xT;
vector<ESTER_EGG> eEggs;
static GLuint _textureId;
const float WATER_TEXTURE_SIZE = 0.7f;
const float WATER_ALPHA = 0.8f;
double adjTime =50;


#define light_brown {1.0f, 0.7f, 0.4f}
#define dark_brown {1.0f, 0.8f, 0.6f}
#define red {0xff, 0x00, 0x00}
#define yellow {0xff, 0xff, 0x00}
#define magenta {0xff, 0, 0xff}
GLubyte texture[][3] = {
    light_brown, dark_brown
};

GLubyte texture1[][3] = {
    red, yellow,
    yellow, red,
};


float _angle = -60;
/******* Main method***************/
int main(int argc, char** argv)
{
	srand(time(NULL));
	//printf("%.1f\n", (float)sqrt(5));
   glutInit(&argc, argv);
   glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
   glutInitWindowSize (1000, 900); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Bubble Trouble");

		xT = 0.0f;
    Setting ();


	 CIRCLE bubble = {700, 110, 20.0f, -1 , 1, {0.0f, 1.0f, 0.0f}};
	 bubbles.push_back(bubble);
	 
	 //Bonus Points
	 eggGen(1);
	 
   glutDisplayFunc(Render); 
   glutIdleFunc(Render);

   glutTimerFunc(1,Timer,1);

   glutReshapeFunc(reshape);
   
   glutKeyboardFunc(keyboard);

   glutSpecialFunc(inputKey);
   //glutSpecialUpFunc(upkey);

   glutPassiveMotionFunc(MouseMotion);
   glutMouseFunc(mouseFunc);


   glutMainLoop();
   return 0;
}

/********** Methods*******************/
//Timer functions for animation
void Timer(int v) 
{ 
 		if(GameState == GAME_RUNNING){
       // ball.left+=Xspeed; 
       // ball.right+=Xspeed; 
       // ball.top+=Yspeed; 
       // ball.bottom+=Yspeed; 
       if(eEggs.size()>0){
       	//printf("In Timer0 %d\n", eEggs.size());
       	for(int i=0; i<eEggs.size(); i++){
       		if((eEggs.at(i)).show !=0){
       		//	printf("In Timer1 %d\n", eEggs.size());
       			if((eEggs.at(i)).show ==1){
       			
		     			if(Test_Egg_Wall(eEggs.at(i),wall)== FROM_BOTTOM){ 
									//(bubbles.at(i)).Yspeed=-(bubbles.at(i)).Yspeed; 
									eEggs.erase(eEggs.begin()+i);
									i--;
									continue;
									//((eEggs.at(i)).Egg).Yspeed = -(((eEggs.at(i)).Egg).Yspeed);
							}
						}else{
							/********************* Here **************/
						}
						
						/*if(Test_Egg_Wall(eEggs.at(i),wall)== FROM_TOP){ 
								//(bubbles.at(i)).Yspeed=-(bubbles.at(i)).Yspeed; 
								//eEggs.erase(eEggs.begin()+i);
								((eEggs.at(i)).Egg).Yspeed = -(((eEggs.at(i)).Egg).Yspeed);
						}*/
       			
       			((eEggs.at(i)).Egg).Cy += ((eEggs.at(i)).Egg).Yspeed;
       			
       				float v_sqr;
				   		float v;
							if(((eEggs.at(i)).Egg).Yspeed >=0){
								v_sqr = (((eEggs.at(i)).Egg).Yspeed)*(((eEggs.at(i)).Egg).Yspeed) + 0.001*(WINDOW_HEIGHTB-((eEggs.at(i)).Egg).Cy);
								v= sqrt(v_sqr);
							}else{
								v_sqr = (((eEggs.at(i)).Egg).Yspeed)*(((eEggs.at(i)).Egg).Yspeed) - 0.001*(WINDOW_HEIGHTB-((eEggs.at(i)).Egg).Cy);
								if(v_sqr<0){
									v_sqr = 0;
								}
								v= -sqrt(v_sqr);
							}
							 
				   		((eEggs.at(i)).Egg).Yspeed = v;       				
       				
       		}
       	}
       }
       
       if(bubbles.size()>0){
       	for(int i=0; i<bubbles.size(); i++){
       		(bubbles.at(i)).Cx += (bubbles.at(i)).Xspeed;
       		(bubbles.at(i)).Cy += (bubbles.at(i)).Yspeed;
       		
       		float v_sqr;
       		float v;
					if((bubbles.at(i)).Yspeed >=0){
						v_sqr = ((bubbles.at(i)).Yspeed)*((bubbles.at(i)).Yspeed) + 0.001*(WINDOW_HEIGHTB-(bubbles.at(i)).Cy);
						v= sqrt(v_sqr);
					}else{
						v_sqr = ((bubbles.at(i)).Yspeed)*((bubbles.at(i)).Yspeed) - 0.001*(WINDOW_HEIGHTB-(bubbles.at(i)).Cy);
						if(v_sqr<0){
							v_sqr = 0;
						}
						v= -sqrt(v_sqr);
					}
					 
       		(bubbles.at(i)).Yspeed = v;
       	}
       }
        
       /* bubble.Cx +=Xspeed;
        bubble.Cy +=Yspeed;
        if(splitFlag != 0){
        	bub1.Cx +=Xspeed1;
        	bub1.Cy +=Yspeed1;
        
        	bub2.Cx +=Xspeed2;
        	bub2.Cy +=Yspeed2;
        }*/
        
        if(bullets.size()!=0){
        	for(int l=0; l<bullets.size(); l++){
						 (bullets.at(l)).top -= Bulletspeed;
						 if((bullets.at(l)).top <= wall.top){
						 		bullets.erase(bullets.begin()+l);
						 		l--;
						 		continue;
						 }
						 (bullets.at(l)).bottom -= Bulletspeed;
						 int hit=0;
						 
						 if(eEggs.size()>0){
						 		for(int i=0; i<eEggs.size() ; i++){
						 			hit = Test_Bullet_Egg(bullets.at(l), eEggs.at(i));
						 			if(hit==1){
							 			if((eEggs.at(i)).show ==0){
							 			//printf("In Timer2 %d\n", eEggs.size());
							 				int rand_show = rand()%2 +1;
							 				if(((eEggs.at(i)).Egg).Cy == 400){
							 					rand_show = 3;
							 				}
							 				(eEggs.at(i)).show =rand_show;
							 				
							 				if(rand_show >=2){
							 					((eEggs.at(i)).Egg).Color[0] = 1.0f;
							 					((eEggs.at(i)).Egg).Color[1] = 0.0f;
							 					((eEggs.at(i)).Egg).Color[2] = 0.0f;
							 				}
							 			}else{//if (eEggs.at(i)).show ==1
							 			//printf("In Timer3 %d\n", eEggs.size());
							 				if((eEggs.at(i)).show ==1){
								 				//CurrTotalScore += 25;
								 				BonusScore += 25;
								 				eEggs.erase(eEggs.begin()+i);
								 			}
							 			}
							 			break;
						 			}
						 			
						 		}
						 }
						 
						 if(hit==1){
							 		bullets.erase(bullets.begin()+l);
							 		l--;
							 		continue;
						 }
						 
						 hit = 0;
						 if(bubbles.size()>0){
							 	for(int i=0; i<bubbles.size(); i++){
							 		hit = Test_Bullet_Bubble(bullets.at(l), bubbles.at(i));
							 		
							 		if(hit==1){
							 			CurrTotalScore += 50;
							 			if((bubbles.at(i)).R <= 15.0f){
							 					bubbles.erase(bubbles.begin()+i);
							 			}else{
							 					
							 					splitBubble(bubbles.at(i));
							 					bubbles.erase(bubbles.begin()+i);
							 					
							 					bubbles.push_back(bub1);
							 					bubbles.push_back(bub2);
							 					//printf("Size of bub %f\n",(bubbles.at(1)).Cx);
							 			}
							 			break;
							 		}
							 		
							 		
							 	}
						 }
						 
						 if(hit==1){
							 		bullets.erase(bullets.begin()+l);
							 		l--;
							 		continue;
						 }
						 
					}
        }
   }		
   			//glutPostRedisplay();
        glutTimerFunc(1,Timer,1); // ??? ????? ???? ??? ?? ??? ?????? ?????? ?????? 
}

//Redering function..
void Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor3f( 1.0f, 1.0f, 1.0f );
	//glTranslatef(xT,0.0f,0.0f);
	wall.left=-GAME_WINDOW;
	wall.top=0;
	wall.right=WINDOW_WIDTH+GAME_WINDOW;
	wall.bottom=WINDOW_HEIGHTB;
	//generateTexture();
	/***************Textutre **************/
		glColor3f( 1.0f,0.8f, 0.6f );
		glBegin(GL_TRIANGLES);
		  glTexCoord2f(0.5, 1.0);    glVertex2f(-100, wall.bottom);
		  glTexCoord2f(0.0, 0.0);    glVertex2f(-100, 000);
		  glTexCoord2f(1.0, 0.0);    glVertex2f(wall.right, 00);

		  glTexCoord2f(4, 8);        glVertex2f(-100, wall.bottom);
		  glTexCoord2f(0.0, 0.0);    glVertex2f(wall.right, wall.bottom);
		  glTexCoord2f(8, 0.0);      glVertex2f(wall.right, 0);

		  glTexCoord2f(5, 5);        glVertex2f(0, 0);
		  glTexCoord2f(0.0, 0.0);    glVertex2f(-1.5, -3);
		  glTexCoord2f(4, 0.0);      glVertex2f(1.5, -3);
  	glEnd();
		glColor3f( 1.0f, 1.0f, 1.0f );
		
		glEnable(GL_TEXTURE_2D);
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glTexImage2D(GL_TEXTURE_2D,
				           0,                    // level 0
				           3,                    // use only R, G, and B components
				           2, 2,                 // texture has 2x2 texels
				           0,                    // no border
				           GL_RGB,               // texels are in RGB format
				           GL_UNSIGNED_BYTE,     // color components are unsigned bytes
				           texture);
					//glBindTexture(GL_TEXTURE_2D, _textureId);       
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glFlush();
		glDisable(GL_TEXTURE_2D);
		
		//glColor3f( 1.0f,1.0f, 0.7f );
		glColor3f( 1.0f,0.7f, 0.4f );
		int tex_count =0;
			for(int fh=0; fh<=wall.right ; fh=fh+100){
				if(tex_count%2==0){
						for(int fv=wall.bottom; fv>=0 ; fv=fv-100){
								glBegin(GL_QUADS); 
								glVertex2f(wall.left+fh+100,fv);      //Left - Bottom 
								glVertex2f(wall.left+fh+200,fv); 
								glVertex2f(wall.left+fh+200,fv-50); 
								glVertex2f(wall.left+fh+100,fv-50); 
								glEnd();
						 }
						 tex_count =1;
					}else{
						for(int fv=wall.bottom-50; fv>=0 ; fv=fv-100){
								glBegin(GL_QUADS); 
								glVertex2f(wall.left+fh+100,fv);      //Left - Bottom 
								glVertex2f(wall.left+fh+200,fv); 
								glVertex2f(wall.left+fh+200,fv-50); 
								glVertex2f(wall.left+fh+100,fv-50); 
								glEnd();
						 }
					
						tex_count =0;
					}
				
			} 
		glColor3f( 1.0f, 1.0f, 1.0f );
		
		
	/********** ends *************/
			
	//glClear(GL_COLOR_BUFFER_BIT );
	
 
	glTranslatef(xT,0.0f,0.0f);
	
	RECTA BorderL = {-GAME_WINDOW-10, 0, -GAME_WINDOW, WINDOW_HEIGHTB};
		glColor3f( 1.0f,0.0f, 0.0f );
				    glBegin(GL_QUADS); 
				    glVertex2f(BorderL.left,BorderL.bottom);      //Left - Bottom 
				    glVertex2f(BorderL.right,BorderL.bottom); 
				    glVertex2f(BorderL.right,BorderL.top); 
				    glVertex2f(BorderL.left,BorderL.top); 
				    glEnd(); 
		glColor3f( 1.0f, 1.0f, 1.0f );
	RECTA BorderR = {WINDOW_WIDTH+GAME_WINDOW, 0, WINDOW_WIDTH+GAME_WINDOW+10, WINDOW_HEIGHTB};
		glColor3f( 1.0f,0.0f, 0.0f );
				    glBegin(GL_QUADS); 
				    glVertex2f(BorderR.left,BorderR.bottom);      //Left - Bottom 
				    glVertex2f(BorderR.right,BorderR.bottom); 
				    glVertex2f(BorderR.right,BorderR.top); 
				    glVertex2f(BorderR.left,BorderR.top); 
				    glEnd(); 
		glColor3f( 1.0f, 1.0f, 1.0f );
	
	RECTA Srect = {0, WINDOW_HEIGHTB, WINDOW_WIDTH, WINDOW_HEIGHT}; //left,top,right,bottom;
		glColor3f( 0.2f,1.0f, 1.0f );
				    glBegin(GL_QUADS); 
				    glVertex2f(Srect.left-xT,Srect.bottom);      //Left - Bottom 
				    glVertex2f(Srect.right-xT,Srect.bottom); 
				    glVertex2f(Srect.right-xT,Srect.top); 
				    glVertex2f(Srect.left-xT,Srect.top); 
				    glEnd(); 
		glColor3f( 1.0f, 1.0f, 1.0f );
	
		if(GameState == GAME_START || GameState == GAME_RUNNING || GameState == GAME_PAUSE){
			if(GameState == GAME_START){
				CurrTotalScore = preTotalScore;
				time(&startTime);
				//resumetime = startTime;
				if(GameLevel == LEVEL0){
					glEnable (GL_BLEND);
					glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
					for(int c = 0; c<=10; c++){
						glColor4f( 1.0f-((float)c)/10, 0.0f+((float)c)/10, 0.0f+((float)c)/20, 0.5f -((float)c)/40 );
							glBegin(GL_QUADS); 
								glVertex2f(WINDOW_WIDTH/2 - 40 +2*c,WINDOW_HEIGHTB/2 - 10 +2*c);      
								glVertex2f(WINDOW_WIDTH/2 +30 -2*c,WINDOW_HEIGHTB/2 - 10 +2*c); 
								glVertex2f(WINDOW_WIDTH/2 +30 -2*c,WINDOW_HEIGHTB/2 + 35 -2*c); 
								glVertex2f(WINDOW_WIDTH/2 -40 +2*c,WINDOW_HEIGHTB/2 +35 -2*c); 
							glEnd(); 
						glColor3f( 1.0f, 1.0f, 1.0f );
					}
				
					glColor3f( 0.0f, 0.0f, 0.0f );
					sprintf(string1," PLAY ");
					drawText(string1,WINDOW_WIDTH/2 - 30,WINDOW_HEIGHTB/2 + 20 );
					glColor3f( 1.0f, 1.0f, 1.0f );
					
					glColor3f( 0.2f,1.0f, 1.0f );
					glBegin(GL_QUADS); 
				    glVertex2f(Srect.left-xT,Srect.bottom);      //Left - Bottom 
				    glVertex2f(Srect.right-xT,Srect.bottom); 
				    glVertex2f(Srect.right-xT,Srect.top); 
				    glVertex2f(Srect.left-xT,Srect.top); 
				  glEnd();
				  
				  //Instructions
					sprintf(string1,"CONTROLS");
					glColor3f( 0.0f, 0.0f, 0.0f );
					drawText(string1,(WINDOW_WIDTH/2-80)-xT,WINDOW_HEIGHTB+50);
					glColor3f( 1.0f, 1.0f, 1.0f );
					sprintf(string1,"_________");
					glColor3f( 0.0f, 0.0f, 0.0f );
					drawText(string1,(WINDOW_WIDTH/2-85)-xT,WINDOW_HEIGHTB+50);
					glColor3f( 1.0f, 1.0f, 1.0f );
					sprintf(string1,"Move Left  : <-");
					glColor3f( 0.0f, 0.0f, 0.0f );
					drawText(string1,(WINDOW_WIDTH/2-90)-xT,WINDOW_HEIGHTB+75);
					glColor3f( 1.0f, 1.0f, 1.0f );
					sprintf(string1,"Move Right : ->");
					glColor3f( 0.0f, 0.0f, 0.0f );
					drawText(string1,(WINDOW_WIDTH/2-90)-xT,WINDOW_HEIGHTB+95);
					glColor3f( 1.0f, 1.0f, 1.0f );
					sprintf(string1,"Shoot    : SPACE");
					glColor3f( 0.0f, 0.0f, 0.0f );
					drawText(string1,(WINDOW_WIDTH/2-90)-xT,WINDOW_HEIGHTB+115);
					glColor3f( 1.0f, 1.0f, 1.0f );
					sprintf(string1,"ScreenShot : S");
					glColor3f( 0.0f, 0.0f, 0.0f );
					drawText(string1,(WINDOW_WIDTH/2-90)-xT,WINDOW_HEIGHTB+135);
					glColor3f( 1.0f, 1.0f, 1.0f );
				   
				}else{
					GameState= GAME_RUNNING;
				}
			}else{
			
				//Displaying Ester eggs
				if(eEggs.size()>0){
					for(int i=0; i<eEggs.size() ; i++){
						if((eEggs.at(i)).show !=0){
							//printf("In Timer4 %d\n", eEggs.size());
							CIRCLE eg = (eEggs.at(i)).Egg;
							drawCircle(eg);
							if(GameState==GAME_RUNNING){
								if(Test_Egg_Player(eEggs.at(i),player_1)==true){
									if((eEggs.at(i)).show==3){
										time_t now;
										time(&now);
										double seconds = difftime(now, startTime);
										double timeLeft = adjTime-seconds;
					
										BonusScore += eEggs.size()*25;
										CurrTotalScore +=bubbles.size()*50; 
														
										 BonusScore += timeLeft*20; // Bonus
										 CurrTotalScore += BonusScore;
										 GameState = GAME_WIN;
										 break;
									}else{
										xT=0;
										GameState = GAME_OVER;
										CurrTotalScore += BonusScore;
										LifeLine--;
										break;
									}
									
								}
							
								for(int j=0; j<bubbles.size(); j++){
										if(Test_Egg_Bubble(eEggs.at(i), &(bubbles.at(j)))==1){
								 				//float tmpx = (bubbles.at(i)).Xspeed;
								 				//float tmpy = (bubbles.at(i)).Yspeed;
								 				//(bubbles.at(i)).Xspeed = (bubbles.at(j)).Xspeed;
								 				//(bubbles.at(i)).Yspeed = (bubbles.at(j)).Yspeed;
								 				
								 				(bubbles.at(j)).Xspeed = (-1)*((bubbles.at(j)).Xspeed);
								 				(bubbles.at(j)).Yspeed = (-1)*((bubbles.at(j)).Yspeed);
								 		}
								}
							
							
								//Test_Egg_Wall
								if((eEggs.at(i)).show >= 2){
									int t_e_b = Test_Egg_Wall(eEggs.at(i),wall);
									if(t_e_b== FROM_BOTTOM){ 
											//(bubbles.at(i)).Yspeed=-(bubbles.at(i)).Yspeed; 
											//eEggs.erase(eEggs.begin()+i);
											//i--;
										//	continue;
											((eEggs.at(i)).Egg).Yspeed = -(((eEggs.at(i)).Egg).Yspeed);
									}
							
									if(t_e_b== FROM_TOP){ 
											//(bubbles.at(i)).Yspeed=-(bubbles.at(i)).Yspeed; 
											//eEggs.erase(eEggs.begin()+i);
											//i--;
											//continue;
											((eEggs.at(i)).Egg).Yspeed = -(((eEggs.at(i)).Egg).Yspeed);
									}
								}
							}
							
						}else{
									CIRCLE eg = (eEggs.at(i)).Egg;
									drawEgg(eg);
									
						}
					}
				}
				
				if(bubbles.size() >0){
					for(int i=0; i<bubbles.size(); i++){
						CIRCLE bubble = bubbles.at(i);
			
						drawCircle(bubble);
						if(GameState == GAME_RUNNING){
					
								if(Test_Bubble_Player(bubble,player_1)==true){
									xT=0;
									GameState = GAME_OVER;
									LifeLine--;
									break;
								}
										for(int j=i+1; j<bubbles.size(); j++){
									 			if(Test_Bubble_Bubble(&(bubbles.at(i)), &(bubbles.at(j)))==1){
									 				float tmpx = (bubbles.at(i)).Xspeed;
									 				float tmpy = (bubbles.at(i)).Yspeed;
									 				(bubbles.at(i)).Xspeed = (bubbles.at(j)).Xspeed;
									 				(bubbles.at(i)).Yspeed = (bubbles.at(j)).Yspeed;
									 				
									 				(bubbles.at(j)).Xspeed = tmpx;
									 				(bubbles.at(j)).Yspeed = tmpy;
									 			}
									 	}
						
								if(Test_Bubble_Wall(bubbles.at(i),wall)== FROM_RIGHT) 
									(bubbles.at(i)).Xspeed=-delta; 

								if(Test_Bubble_Wall(bubbles.at(i),wall)== FROM_LEFT) 
									(bubbles.at(i)).Xspeed=delta; 

								if(Test_Bubble_Wall(bubbles.at(i),wall)== FROM_TOP) 
									(bubbles.at(i)).Yspeed=-(bubbles.at(i)).Yspeed; 

								if(Test_Bubble_Wall(bubbles.at(i),wall)== FROM_BOTTOM) 
									(bubbles.at(i)).Yspeed=-(bubbles.at(i)).Yspeed; 
									
						}
					}
		
				}else{
					xT=0;
					time_t now;
					time(&now);
					double seconds = difftime(now, startTime);
					double timeLeft = adjTime-seconds;
					
					
					 BonusScore += timeLeft*20; // Bonus
					 CurrTotalScore += BonusScore;
					GameState = GAME_WIN;
				}
	
				//DrawRectangle(ball);
			 
				 DrawRectangle(player_1); 
					player_1.left=mouse_x-30; 
					player_1.right=mouse_x+30; 


				 /* if(Test_Bubble_Player(bubble,player_1)==true){ 
							     Yspeed=-delta; 
						      splitBubble(bubble);
					}*/
		
					if(bullets.size()!=0){
						for(int l=0; l<bullets.size(); l++){
							DrawRectangle(bullets.at(l));
						}
					}
				
					//Score Board
				
					time_t now;
					time(&now);
				
					double seconds = difftime(now, startTime);
					double timeLeft;
					if(GameState==GAME_PAUSE){
						timeLeft = adjTime;
					}else{
					 timeLeft= adjTime-seconds;
					}
					//Time Bar
						RECTA Trect = {-xT,WINDOW_HEIGHTB, (WINDOW_WIDTH*timeLeft)/50-xT, WINDOW_HEIGHTB+30 }; //left,top,right,bottom;
						glColor3f( 0.0f, 1.0f, 0.0f );
						glBegin(GL_LINES);
   					 glVertex2f(-xT, WINDOW_HEIGHTB);
   					 glVertex2f(WINDOW_WIDTH-xT, WINDOW_HEIGHTB);
						glEnd(); 
						
						glColor3f( 1.0f-((float)timeLeft)/50, ((float)timeLeft)/50, 0.0f );
				    glBegin(GL_QUADS); 
				    glVertex2f(Trect.left,Trect.bottom);      //Left - Bottom 
				    glVertex2f(Trect.right,Trect.bottom); 
				    glVertex2f(Trect.right,Trect.top); 
				    glVertex2f(Trect.left,Trect.top); 
				    glEnd(); 
				    
				    glColor3f( 0.0f, 0.0f, 0.0f );
						glBegin(GL_LINES);
   					 glVertex2f(-xT, WINDOW_HEIGHTB);
   					 glVertex2f(WINDOW_WIDTH-xT, WINDOW_HEIGHTB);
						glEnd();
						
						glColor3f( 0.0f, 0.0f, 0.0f );
						glBegin(GL_LINES);
   					 glVertex2f(-xT, WINDOW_HEIGHTB+30);
   					 glVertex2f(WINDOW_WIDTH-xT, WINDOW_HEIGHTB+30);
						glEnd();
				    
				   	glColor3f( 1.0f, 1.0f, 1.0f );
					//End
					sprintf(string1,"Time Left : %d ",(int)timeLeft);
					glColor3f( 0.0f, 0.0f, 0.0f );
					drawText(string1,10-xT,WINDOW_HEIGHTB+80);
					glColor3f( 0.0f, 0.0f, 0.0f );
					sprintf(string1,"Player's Score : %d ",CurrTotalScore);
					drawText(string1,10-xT,WINDOW_HEIGHTB+120);
					glColor3f( 1.0f, 1.0f, 1.0f );
					glColor3f( 0.0f, 0.0f, 0.0f );
					sprintf(string1,"Level : %d ",GameLevel);
					drawText(string1,10-xT,WINDOW_HEIGHTB+160);
					glColor3f( 1.0f, 1.0f, 1.0f );
					
					//Instructions
					sprintf(string1,"Controls");
					glColor3f( 0.0f, 0.0f, 0.0f );
					drawText(string1,(WINDOW_WIDTH-280)-xT,WINDOW_HEIGHTB+50);
					glColor3f( 1.0f, 1.0f, 1.0f );
					sprintf(string1,"_______");
					glColor3f( 0.0f, 0.0f, 0.0f );
					drawText(string1,(WINDOW_WIDTH-290)-xT,WINDOW_HEIGHTB+50);
					glColor3f( 1.0f, 1.0f, 1.0f );
					sprintf(string1,"Move Left  : <-");
					glColor3f( 0.0f, 0.0f, 0.0f );
					drawText(string1,(WINDOW_WIDTH-300)-xT,WINDOW_HEIGHTB+75);
					glColor3f( 1.0f, 1.0f, 1.0f );
					sprintf(string1,"Move Right : ->");
					glColor3f( 0.0f, 0.0f, 0.0f );
					drawText(string1,(WINDOW_WIDTH-300)-xT,WINDOW_HEIGHTB+95);
					glColor3f( 1.0f, 1.0f, 1.0f );
					sprintf(string1,"Shoot    : SPACE");
					glColor3f( 0.0f, 0.0f, 0.0f );
					drawText(string1,(WINDOW_WIDTH-300)-xT,WINDOW_HEIGHTB+115);
					glColor3f( 1.0f, 1.0f, 1.0f );
					sprintf(string1,"CAM Left  : D");
					glColor3f( 0.0f, 0.0f, 0.0f );
					drawText(string1,(WINDOW_WIDTH-300)-xT,WINDOW_HEIGHTB+135);
					glColor3f( 1.0f, 1.0f, 1.0f );
					sprintf(string1,"CAM Right : G");
					glColor3f( 0.0f, 0.0f, 0.0f );
					drawText(string1,(WINDOW_WIDTH-300)-xT,WINDOW_HEIGHTB+155);
					glColor3f( 1.0f, 1.0f, 1.0f );
					
					
				
					
					if(timeLeft<0){
						xT=0;
						CurrTotalScore += BonusScore;
						GameState = GAME_OVER;
						LifeLine--;
					}
				}
			}else{
				if(GameState == GAME_WIN){
					xT=0;
						if(GameLevel == LEVEL4){
							sprintf(string1," YOU WON");
							glColor3f( 0.0f, 0.0f, 0.0f );
							drawText(string1, WINDOW_WIDTH/2 - 30,WINDOW_HEIGHTB/2 -60);
							glColor3f( 1.0f, 1.0f, 1.0f );
						}
						
						sprintf(string1," SCORE : %d", CurrTotalScore);
						glColor3f( 0.0f, 0.0f, 0.0f );
						drawText(string1,WINDOW_WIDTH/2 - 50,WINDOW_HEIGHTB+ 80 );
						glColor3f( 1.0f, 1.0f, 1.0f );
						
						sprintf(string1," BONUS : %d", BonusScore);
						glColor3f( 0.0f, 0.0f, 0.0f );
						drawText(string1,WINDOW_WIDTH/2 - 50,WINDOW_HEIGHTB+ 100  );
						glColor3f( 1.0f, 1.0f, 1.0f );
						
						for(int c = 0; c<=10; c++){
						glColor4f( 1.0f-((float)c)/10, 0.0f+((float)c)/10, 0.0f+((float)c)/20, 0.5f -((float)c)/40 );
							glBegin(GL_QUADS); 
								glVertex2f(WINDOW_WIDTH/2 - 40 +2*c,WINDOW_HEIGHTB/2 - 10 +2*c);      
								glVertex2f(WINDOW_WIDTH/2 +75 -2*c,WINDOW_HEIGHTB/2 - 10 +2*c); 
								glVertex2f(WINDOW_WIDTH/2 +75 -2*c,WINDOW_HEIGHTB/2 + 35 -2*c); 
								glVertex2f(WINDOW_WIDTH/2 -40 +2*c,WINDOW_HEIGHTB/2 +35 -2*c); 
							glEnd(); 
						glColor3f( 1.0f, 1.0f, 1.0f );
					}
						if(GameLevel == LEVEL4){
							sprintf(string1," REPLAY ");
							glColor3f( 0.0f, 0.0f, 0.0f );
							drawText(string1,WINDOW_WIDTH/2 - 10,WINDOW_HEIGHTB/2 + 20 );
						}else{
							sprintf(string1," NEXT LEVEL ");
							glColor3f( 0.0f, 0.0f, 0.0f );
							drawText(string1,WINDOW_WIDTH/2 - 30,WINDOW_HEIGHTB/2 + 20 );
						}
						glColor3f( 1.0f, 1.0f, 1.0f );
						
				}else{ // Game Over State
						glColor3f( 0.0f, 0.0f, 0.0f );
						sprintf(string1," GAME OVER !!!!");
						drawText(string1,WINDOW_WIDTH/2 -40,WINDOW_HEIGHTB +60);
						glColor3f( 1.0f, 1.0f, 1.0f );
						
						sprintf(string1," SCORE : %d", CurrTotalScore);
						glColor3f( 0.0f, 0.0f, 0.0f );
						drawText(string1,WINDOW_WIDTH/2 - 50,WINDOW_HEIGHTB+ 80 );
						glColor3f( 1.0f, 1.0f, 1.0f );
						
						sprintf(string1," BONUS : %d", BonusScore);
						glColor3f( 0.0f, 0.0f, 0.0f );
						drawText(string1,WINDOW_WIDTH/2 - 50,WINDOW_HEIGHTB+ 100  );
						glColor3f( 1.0f, 1.0f, 1.0f );
						
						
						for(int c = 0; c<=10; c++){
						glColor4f( 1.0f-((float)c)/10, 0.0f+((float)c)/10, 0.0f+((float)c)/20, 0.5f -((float)c)/40 );
							glBegin(GL_QUADS); 
								glVertex2f(WINDOW_WIDTH/2 - 40 +2*c,WINDOW_HEIGHTB/2 - 10 +2*c);      
								glVertex2f(WINDOW_WIDTH/2 +75 -2*c,WINDOW_HEIGHTB/2 - 10 +2*c); 
								glVertex2f(WINDOW_WIDTH/2 +75 -2*c,WINDOW_HEIGHTB/2 + 35 -2*c); 
								glVertex2f(WINDOW_WIDTH/2 -40 +2*c,WINDOW_HEIGHTB/2 +35 -2*c); 
							glEnd(); 
						glColor3f( 1.0f, 1.0f, 1.0f );
					}
						
						sprintf(string1," TRY AGAIN ");
						glColor3f( 0.0f, 0.0f, 0.0f );
						drawText(string1,WINDOW_WIDTH/2 - 30,WINDOW_HEIGHTB/2 + 20 );
						glColor3f( 1.0f, 1.0f, 1.0f );
						
						
				}
			}
			
		//glTranslatef(xT,0.0f,0.0f);
	glutSwapBuffers();
}


// Key Board Messages 
void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
   		case ' ' :
				if(GameState == GAME_RUNNING){
					RECTA bul = {mouse_x-5, WINDOW_HEIGHTB-7, mouse_x+5, WINDOW_HEIGHTB};
					bullets.push_back(bul);
				}
			break;
			
			case 's' :
					save_screenshot("screen.tga" , WINDOW_WIDTH, WINDOW_HEIGHT);
				break;
			
			case 'g' :
				if(GameState== GAME_RUNNING){
					if(xT>= -GAME_WINDOW)
						xT -= 5.0f;
				}
				break;
			
			case 'd' :
				if(GameState== GAME_RUNNING){
					if(xT<=GAME_WINDOW)
						xT += 5.0f;
				}
				break;
				
      case 27:
      	/*if(GameState==GAME_RUNNING){
      		time_t now;
					time(&now);
				
					double seconds = difftime(now, startTime);
					adjTime = adjTime-seconds;
					GameState == GAME_PAUSE;
      	}*/
         exit(0);
         break;
   }
}


//Key Board Message 
void inputKey(int key, int x, int y) {

	switch (key) {
		case GLUT_KEY_LEFT : 
					mouse_x= mouse_x - 10;
					if(mouse_x -30 < -GAME_WINDOW) mouse_x = 30 - GAME_WINDOW;
			break;

		case GLUT_KEY_RIGHT : 
					mouse_x= mouse_x + 10;
					if(mouse_x +30 > WINDOW_WIDTH+GAME_WINDOW) mouse_x = WINDOW_WIDTH-30+GAME_WINDOW;
			break;


		case GLUT_KEY_UP : 

			break ;


		case GLUT_KEY_DOWN : 

			break;
		
		


	}
}

//Key Board Message 
void upkey(int key, int x, int y) {

	switch (key)
	{
 

	}
}

void mouseFunc(int button, int state, int x, int y) {
    
 /* if (button == GLUT_RIGHT_BUTTON) {
    if (state == GLUT_DOWN) {
      beginY = y; beginX = x;
    }
    else if (state == GLUT_UP) {
      xRot += (float)(y-beginY) / 10.0;
      yRot += (float)(x-beginX) / 10.0;
      glutPostRedisplay();
    }
  }*/

  // when the left click, fire an arrow.
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
	/*GLfloat xx = (float)(x) / (float) windowWidth * (maxX-minX) + minX;
	GLfloat yy = (float)(windowHeight-y) / (float) windowHeight * (maxY-minY) + minY;
    arrow a(xx,yy);
    arrows.push_back(a);*/
    // Draw Bullet..
    
//    if(GameState== GAME_START || GameState == GAME_RUNNING){
		if(GameState == GAME_START && GameLevel == LEVEL0){
			if((x >= (WINDOW_WIDTH/2 - 40)) && (x <= (WINDOW_WIDTH/2 + 30)) 
						&& (y >= (WINDOW_HEIGHTB/2 -10)) && (y <= (WINDOW_HEIGHTB/2 + 35))){
							//bubbles.clear();
							//bullets.clear();s
							
							GameState = GAME_RUNNING;
							GameLevel = LEVEL1;
			}
		}	
		
    if(GameState == GAME_RUNNING){
		  RECTA bul = {x-5, WINDOW_HEIGHTB-7, x+5, WINDOW_HEIGHTB};
		  bullets.push_back(bul);
		}
		if(GameState == GAME_PAUSE){
			if((x >= (WINDOW_WIDTH/2 - 40)) && (x <= (WINDOW_WIDTH/2 + 75)) 
						&& (y >= (WINDOW_HEIGHTB/2 -10)) && (y <= (WINDOW_HEIGHTB/2 + 35))){
							time(&startTime);
							GameState = GAME_RUNNING;
			}
		}
		if(GameState == GAME_OVER || GameState == GAME_WIN){
			// Try again
			xT=0;
			if((x >= (WINDOW_WIDTH/2 - 40)) && (x <= (WINDOW_WIDTH/2 + 75)) 
						&& (y >= (WINDOW_HEIGHTB/2 -10)) && (y <= (WINDOW_HEIGHTB/2 + 35))){
							bubbles.clear();
							bullets.clear();
							eEggs.clear();
							
							eggGen(2+GameLevel);
							
							if(GameState == GAME_WIN){
								if(GameLevel==LEVEL4){
									GameLevel = LEVEL1;
									preTotalScore = 0;
									CurrTotalScore = 0;
									BonusScore =0;
								}else{
									GameLevel++;
								}
								BonusScore =0;
								preTotalScore = CurrTotalScore;		
							}
							if(GameLevel == LEVEL3){
								int rand_posX = rand()%1200;
								if(rand_posX >1170 ){
									rand_posX = 1170;
								}
		
								if( rand_posX < 30){
									rand_posX = 30;
								}
								ESTER_EGG eg = { {rand_posX ,400 ,20.0f, 0, 0, {0.0f, 0.0f, 0.0f}}, 0};
								eEggs.push_back(eg);
							}
												
							//CIRCLE bubble = {110, 110, (GameLevel)*20.0f, 1 , 1, {0.0f,1.0f, 0.0f}};
							CIRCLE bubble;// = {110, 110, (GameLevel)*20.0f, 1 , 1, {0.0f,1.0f, 0.0f}};
							bubble.Cx = 700;
							bubble.Cy = 110;
							bubble.R = GameLevel *20.0f;// (pow(2, GameLevel-1))*20.0f;
							bubble.Xspeed = -1;
							bubble.Yspeed = 1;
							
							if(bubble.R == 10.0f || bubble.R == 15.0f){
								bubble.Color[0] = 1.0f;
								bubble.Color[1] = 0.5f;
								bubble.Color[2] = 0.0f;
		
							}else if(bubble.R == 20.0f || bubble.R == 30.0f){
								bubble.Color[0] = 0.0f;
								bubble.Color[1] = 1.0f;
								bubble.Color[2] = 0.0f;
		
							}else if(bubble.R == 40.0f || bubble.R == 60.0f){
								bubble.Color[0] = 0.5f;
								bubble.Color[1] = 0.0f;
								bubble.Color[2] = 0.5f;
		
							}else if (bubble.R == 80.0f){
								bubble.Color[0] = 1.0f;
								bubble.Color[1] = 0.3f;
								bubble.Color[2] = 0.6f;
							}else {
								bubble.Color[0] = 1.0f;
								bubble.Color[1] = 0.0f;
								bubble.Color[2] = 0.0f;
							}
							
	 						bubbles.push_back(bubble);
	 						adjTime = 50;
							GameState = GAME_START;
							
			}
		}
  }
}
 
void MouseMotion(int x,int y)
{
	mouse_x=x;
	if(mouse_x-20<0) mouse_x = 20;
}


// OpenGL Setting
void Setting(void) 
{
   glClearColor (1.0, 1.0, 1.0, 1.0);
   glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
   glTranslatef(xT,0.0f,0.0f);

}

 
// OnWindowResize 
void reshape (int w, int h)
{
	WINDOW_WIDTH =w ;
	WINDOW_HEIGHT =h ;
	WINDOW_HEIGHTB = (int)((float)h-((200.0f)*(float)h)/900);
	
	if(GameState == GAME_RUNNING){       
      if(bubbles.size()>0){
       	for(int i=0; i<bubbles.size(); i++){
       		if(((bubbles.at(i)).Cx+(bubbles.at(i)).R)>WINDOW_WIDTH)
       			(bubbles.at(i)).Cx = WINDOW_WIDTH - (bubbles.at(i)).R;
       			
       		if(((bubbles.at(i)).Cy+(bubbles.at(i)).R)>WINDOW_HEIGHTB)
       			(bubbles.at(i)).Cy = WINDOW_HEIGHTB - (bubbles.at(i)).R;
       	}
       	
   		}
   }
	
	player_1.top=WINDOW_HEIGHTB-10; 
	player_1.bottom=WINDOW_HEIGHTB;
	
	

   glViewport (0, 0, (GLsizei) w, (GLsizei) h);

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluOrtho2D (0, w, h, 0);


   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();

}

//Splitting a Bubble
void splitBubble(CIRCLE c0)
{
	//TwoCIRCLE c;
	//PlaySound("starwars.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
	//system("canberra-gtk-play -f /home/aniruddha/Documents/CS360/Project/level_animation/GUN2.wav");
	float newR = (c0.R)/2;
	bub1.Cx = c0.Cx-((c0.R)/2);
	bub1.Cy = c0.Cy;
	bub1.R = newR;
	bub1.Xspeed = Xspeed1;
	//bub1.Yspeed = Yspeed1;
	float v_sqr;
	float v;
	if(c0.Yspeed >=0){
		v_sqr = (c0.Yspeed)*(c0.Yspeed) + 0.0005*(WINDOW_HEIGHTB-c0.Cy);
		v= sqrt(v_sqr);
	}else{
		v_sqr = (c0.Yspeed)*(c0.Yspeed) - 0.0005*(WINDOW_HEIGHTB-c0.Cy);
		if(v_sqr<0){
			v_sqr = 0;
		}
		v= -sqrt(v_sqr);
	}
	
	bub1.Yspeed = v;
	
	
	bub2.Cx = c0.Cx+((c0.R)/2);
	bub2.Cy = c0.Cy;
	bub2.R = newR;
	bub2.Xspeed = Xspeed2;
	//bub2.Yspeed = Yspeed2;
	bub2.Yspeed = v;
	
	if((c0.R)/2 == 10.0f || (c0.R)/2 == 15.0f){
		bub1.Color[0] = 1.0f;
		bub1.Color[1] = 0.5f;
		bub1.Color[2] = 0.0f;
		
		bub2.Color[0] = 1.0f;
		bub2.Color[1] = 0.5f;
		bub2.Color[2] = 1.0f;
	}else if((c0.R)/2 == 20.0f || (c0.R)/2 == 30.0f){
		bub1.Color[0] = 0.0f;
		bub1.Color[1] = 1.0f;
		bub1.Color[2] = 0.0f;
		
		bub2.Color[0] = 0.0f;
		bub2.Color[1] = 1.0f;
		bub2.Color[2] = 0.0f;
	}else if((c0.R)/2 == 40.0f || (c0.R)/2 == 60.0f){
		bub1.Color[0] = 0.5f;
		bub1.Color[1] = 0.0f;
		bub1.Color[2] = 0.5f;
		
		bub2.Color[0] = 0.5f;
		bub2.Color[1] = 0.0f;
		bub2.Color[2] = 0.5f;
	}else{
		bub1.Color[0] = 1.0f;
		bub1.Color[1] = 0.0f;
		bub1.Color[2] = 0.0f;
		
		bub2.Color[0] = 1.0f;
		bub2.Color[1] = 0.0f;
		bub2.Color[2] = 0.0f;
	}
	splitFlag = 1;
	
		//return c;
}


void eggGen(int N){
	int prev_pos =0;
	for(int i=0; i<N; i++){ 
		//srand(time(NULL));
		int rand_posX = rand()%1200;
		if(rand_posX >1170 ){
			rand_posX = 1170;
		}
		
		if( rand_posX < 30){
			rand_posX = 30;
		}
		//srand(time(NULL));
		int rand_posY = rand()%250;
		if(rand_posY < 30){
			rand_posY=30;
		}
		 ESTER_EGG eg = { {rand_posX-100 ,rand_posY ,25.0f, 0, 0, {0.7f, 0.0f, 0.9f}}, 0};
		 eEggs.push_back(eg);
		 //free(eg);
	}
}


