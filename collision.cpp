/***************** CS360 : Project *******************
 ******** Group 40 : Aniruddha Kumar Sahu (10092) ****
 *****************************************************/

#include "collision.h"

int Test_Bullet_Bubble(RECTA bullet, CIRCLE bubble)
{
		int hit = 0;
		float bubble_right = bubble.Cx+bubble.R;
		float bubble_left = bubble.Cx-bubble.R;
		float bubble_bottom = bubble.Cy+bubble.R;
		float bubble_top = bubble.Cy-bubble.R;
		
		float bullet_right = bullet.right;
		float bullet_left = bullet.left;
		float bullet_top = bullet.top;
		float bullet_bottom = bullet.bottom;
		
		if(bubble_right <bullet_left)
			return hit;
		
		if(bubble_left >bullet_right)
			return hit;
		
		if(bubble_top >bullet_bottom)
			return hit;
		
		if(bubble_bottom <bullet_top)
			return hit;
		
		hit = 1;
		
		return hit;
}

int Test_Bubble_Bubble(CIRCLE  *bub , CIRCLE  *bub1) 
{ 
		CIRCLE bubble, bubble1;
		bubble = *bub;
		bubble1 = *bub1;
		
		if((bubble.Cx-bubble1.Cx)*(bubble.Cx-bubble1.Cx) + (bubble.Cy-bubble1.Cy)*(bubble.Cy-bubble1.Cy) <
				(bubble.R+bubble1.R)*(bubble.R+bubble1.R)){
					
						return 1;
				}
				
			return 0; 
}

int Test_Ball_Wall(RECTA  ball , RECTA wall) // Unused
{ 
        if(ball.right >=wall.right) 
        return FROM_RIGHT;  
        if(ball.left <=wall.left) 
        return FROM_LEFT;  
        if(ball.top <=wall.top) 
        return FROM_TOP;  
        if(ball.bottom >=wall.bottom) 
        return FROM_BOTTOM;  
 
        else return 0 ; 
}

int Test_Bubble_Wall(CIRCLE  bubble , RECTA wall) 
{ 
        if(bubble.Cx+bubble.R >=wall.right) 
        return FROM_RIGHT;  
        if(bubble.Cx-bubble.R <=wall.left) 
        return FROM_LEFT;  
        if(bubble.Cy-bubble.R <=wall.top) 
        return FROM_TOP;  
        if(bubble.Cy+bubble.R >=wall.bottom) 
        return FROM_BOTTOM;  
 
        else return 0 ; 
}

bool Test_Ball_Player(RECTA ball,RECTA player) // Unused
{ 
        /*if(ball.bottom>= player.top && ball.right<= player.right && ball.right>=player.left )
		{
			CurrTotalScore++;
			PlaySound("Data/Hourglass.wav", NULL, SND_ASYNC);
            return true;  
		}
        if(ball.bottom>= player.top && ball.left>= player.left && ball.left<=player.right ) 
        {
			CurrTotalScore++;
			PlaySound("Data/Hourglass.wav", NULL, SND_ASYNC);
            return true;  
		}*/
		if(ball.bottom >= player.top && ball.left>= player.left && ball.right <=player.right ) 
        {
			CurrTotalScore++;
			//you have to add lib in project-> settings
		//	PlaySound("Data/Hourglass.wav", NULL, SND_ASYNC);
            return true;  
		}
 
            return false;  
}

bool Test_Bubble_Player(CIRCLE bubble,RECTA player) 
{ 
		if(bubble.Cy+bubble.R  >= player.top && bubble.Cx >= player.left && bubble.Cx<=player.right ) 
        {
			      return true;  
		}
 
            return false;  
}

//Testing Eggs..
int Test_Bullet_Egg(RECTA bullet, ESTER_EGG egg)
{
		CIRCLE bubble = egg.Egg;
		int hit = 0;
		float bubble_right = bubble.Cx+bubble.R;
		float bubble_left = bubble.Cx-bubble.R;
		float bubble_bottom = bubble.Cy+bubble.R;
		float bubble_top = bubble.Cy-bubble.R;
		
		float bullet_right = bullet.right;
		float bullet_left = bullet.left;
		float bullet_top = bullet.top;
		float bullet_bottom = bullet.bottom;
		
		if(bubble_right <bullet_left)
			return hit;
		
		if(bubble_left >bullet_right)
			return hit;
		
		if(bubble_top >bullet_bottom)
			return hit;
		
		if(bubble_bottom <bullet_top)
			return hit;
		
		hit = 1;
		
		return hit;
}

int Test_Egg_Wall(ESTER_EGG egg , RECTA wall)
{ 
		CIRCLE bubble = egg.Egg;
        if(bubble.Cx+bubble.R >=wall.right) 
        return FROM_RIGHT;  
        if(bubble.Cx-bubble.R <=wall.left) 
        return FROM_LEFT;  
        if(bubble.Cy-bubble.R <=wall.top) 
        return FROM_TOP;  
        if(bubble.Cy+bubble.R >=wall.bottom) 
        return FROM_BOTTOM;  
 
        else return 0 ; 
}


bool Test_Egg_Player(ESTER_EGG egg,RECTA player)
{ 
		CIRCLE bubble = egg.Egg;
   
		if(bubble.Cy+bubble.R  >= player.top && bubble.Cx >= player.left && bubble.Cx <=player.right ) 
        {
            return true;  
		}
 
            return false;  
}

int Test_Egg_Bubble(ESTER_EGG egg , CIRCLE  *bub1)
{ 
		CIRCLE bubble , bubble1;
		bubble = egg.Egg;
		bubble1 = *bub1;
		
		if((bubble.Cx-bubble1.Cx)*(bubble.Cx-bubble1.Cx) + (bubble.Cy-bubble1.Cy)*(bubble.Cy-bubble1.Cy) <
				(bubble.R+bubble1.R)*(bubble.R+bubble1.R)){
					 /* bub->Xspeed = bubble1.Xspeed;
					 bub1->Xspeed = bubble.Xspeed;
					 
					 bub->Yspeed = bubble1.Yspeed;
					 	bub1->Yspeed = bubble.Yspeed;*/
						return 1;
				}
				
			return 0; 
}

