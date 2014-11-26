/***************** CS360 : Project *******************
 ******** Group 40 : Aniruddha Kumar Sahu (10092) ****
 *****************************************************/
#include "structure.h"

void DrawRectangle(RECTA  rect) 
{ 
			glColor3f( 0.0f, 0.0f, 1.0f );
        glBegin(GL_QUADS); 
        glVertex2f(rect.left,rect.bottom);      //Left - Bottom 
        glVertex2f(rect.right,rect.bottom); 
        glVertex2f(rect.right,rect.top); 
        glVertex2f(rect.left,rect.top); 
        glEnd(); 
       glColor3f( 1.0f, 1.0f, 1.0f );
}

/*void DrawCircle1(CIRCLE1 circle)//(  float radius, int numSides /* = 8 */ //)
/*{
		float radius = circle.radii;
		int numSides = circle.sides;
    const float step = M_PI / numSides;
    glBegin( GL_TRIANGLE_FAN );
        glVertex2f(0.0f, 0.0f);
        for ( float angle = 0.0f; angle < ( 2.0f * M_PI ); angle += step )
        {
            glVertex2f( radius * sinf(angle), radius * cosf(angle) );
        }
        glVertex2f( 0.0f, radius ); // One more vertex to close the circle
    glEnd();
}*/

void drawCircle(CIRCLE circle) //(double x0,double y0,double r){
{
	float x0 = circle.Cx;
	float y0 = circle.Cy;
	float r = circle.R;	
	
	const float PI = 3.1515f;
	const float DEGTORAD = PI/180.0f;
	glColor3f( circle.Color[0], circle.Color[1], circle.Color[2] );
	//glBegin(GL_LINE_LOOP); // Non Solid
	glBegin( GL_TRIANGLE_FAN ); // Solid Circle
	for(int i = 0; i < 360; ++i){
		
			float fSin = std::cos(i*DEGTORAD);//sinf(angle);
      float fCos = std::cos(i*DEGTORAD);//cosf(angle);
		
		float posX = std::cos(i*DEGTORAD) * r + x0;
		float posY = std::sin(i*DEGTORAD) * r + y0;
		
		/*//Add ambient light
		GLfloat ambientColor[] = {0.2f, 0.2f, 0.2f, 1.0f}; //Color (0.2, 0.2, 0.2)
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
	
		//Add positioned light
		GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f}; //Color (0.5, 0.5, 0.5)
		GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f}; //Positioned at (4, 0, 8)
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
	
		//Add directed light
		GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f}; //Color (0.5, 0.2, 0.2)
		//Coming from the direction (-1, 0.5, 0.5)
		GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
		glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
		glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
			float _angle = -70.0f;
		glRotatef(_angle, 0.0f, 1.0f, 0.0f);
		*/
		
		//glColor3f( ( fCos + 1.0f ) * 0.5f, ( fSin + 1.0f ) * 0.5f , 0.0f);
		glColor3f( ( fCos + circle.Color[0] ) , ( fSin + circle.Color[1] ) * 0.5f, circle.Color[2]* 0.5f );
		glVertex3f( posX, posY , 0.0f );
	}
	glEnd();
	glColor3f( 0.0f, 0.0f, 0.0f );
}

void drawEgg(CIRCLE circle){	
	float x0 = circle.Cx;
	float y0 = circle.Cy;
	float r = circle.R;	
	
	const float PI = 3.1515f;
	const float DEGTORAD = PI/180.0f;
	glColor3f( 0.0f, 0.0f, 0.0f );
	//glBegin(GL_LINE_LOOP); // Non Solid
	glEnable (GL_BLEND);

	glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	glBegin( GL_TRIANGLE_FAN ); // Solid Circle
	for(int i = 0; i < 360; ++i){
		
			float fSin = std::cos(i*DEGTORAD);//sinf(angle);
      float fCos = std::cos(i*DEGTORAD);//cosf(angle);
		
		float posX = std::cos(i*DEGTORAD) * r + x0;
		float posY = std::sin(i*DEGTORAD) * r + y0;		
		
		//glColor4f( ( fCos + 0.4f ), ( fSin + 0.2f )  , 0.0f, 0.2);
		glColor4f( ( fCos + 1.0f ), ( fSin + 0.8f )  , 0.4f, 0.2);
		//glColor4f( 0.4f,0.2f, 0.0f, 0.4  );
		//glColor4f( 1.0f,0.8f, 0.6f, 0.4  );
		//glColor3f( ( fCos + circle.Color[0] ) , ( fSin + circle.Color[1] ) * 0.5f, circle.Color[2]* 0.5f );
		glVertex3f( posX, posY , 0.0f );
	}
	glEnd();
	
	//glDisable (GL_BLEND);
	glColor3f( 0.0f, 0.0f, 0.0f );
}

void drawText(char*string1,int x,int y)
{
	  char *c;
	  //glColor3f( 0.0f, 0.0f, 0.0f );
	  glPushMatrix();
	  glTranslatef(x, y,0);
	  glScalef(0.1,-0.1,1);
  
	  for (c=string1; *c != '\0'; c++)
	  {
    		glutStrokeCharacter(GLUT_STROKE_ROMAN , *c); //GLUT_STROKE_ROMAN
    		//glutBitmapCharacter(GLUT_BITMAP_9_BY_15,*c);
	  }
	  glPopMatrix();
		glColor3f( 1.0f, 1.0f, 1.0f );
}



 // Taking ScreenShot
 bool save_screenshot(string filename, int w, int h)
{	
  //This prevents the images getting padded 
 // when the width multiplied by 3 is not a multiple of 4
  glPixelStorei(GL_PACK_ALIGNMENT, 1);
 
  int nSize = w*h*3;
  // First let's create our buffer, 3 channels per Pixel
  char* dataBuffer = (char*)malloc(nSize*sizeof(char));
 
  if (!dataBuffer) return false;
 
   // Let's fetch them from the backbuffer	
   // We request the pixels in GL_BGR format,
   glReadPixels((GLint)0, (GLint)0,
		(GLint)w, (GLint)h,
		 GL_BGR, GL_UNSIGNED_BYTE, dataBuffer);
 
   //Now the file creation
   FILE *filePtr = fopen(filename.c_str(), "wb");
   if (!filePtr) return false;
 
 
   unsigned char TGAheader[12]={0,0,2,0,0,0,0,0,0,0,0,0};
   unsigned char header[6] = { w%256,w/256,
			       h%256,h/256,
			       24,0};
   
   fwrite(TGAheader,	sizeof(unsigned char),	12,	filePtr);
   fwrite(header,	sizeof(unsigned char),	6,	filePtr);
   // And finally our image data
   fwrite(dataBuffer,	sizeof(GLubyte),	nSize,	filePtr);
   fclose(filePtr);
 
  return true;
}
 
