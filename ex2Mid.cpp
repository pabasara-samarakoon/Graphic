#include <glut.h>
#include <math.h> 

int ww = 800, wh = 600;
int xi, yi, xf, yf; 

void putPixel (int x, int y)  
{  
   glColor3f (0.3, 0.2, 0.0); // activate the pixel by setting the point color to white  
   glBegin (GL_POINTS);  
	glVertex2i (x, y); // set the point  
   glEnd ();  
   glFlush (); // process all openGL routines as quickly as possible  
} 

void plotCircle(int h, int k, int x, int y)
{
	putPixel((x+h), (y+k));
	putPixel((y+h), (x+k));
	putPixel((-y+h), (x+k));
	putPixel((-x+h), (y+k));
	putPixel((-x+h), (-y+k));
	putPixel((-y+h), (-x+k));
	putPixel((y+h), (-x+k));
	putPixel((x+h), (-y+k));

}




void display()  
{  
   glClearColor(0.4, 0.7, 0.5, 1.0);  
   glColor3f(0.2, 0.3, 0.3);  
   glClear(GL_COLOR_BUFFER_BIT);  
   glFlush();  
} 

//bresenhamsLine
void bresenhamLine (int h, int k, int x, int y)  
{  
  int dx = abs (x - h);  
  int dy = abs (y - k);  
  int x1, y1;  
  if (dx >= dy)  
  {  
   int d = 2*dy-dx;  
   int ds = 2*dy;  
   int dt = 2*(dy-dx);  
       if (h < x)   
       {  
            x1 = h;  
            y1 = k;  
        }  
        else  
        {   
            x1 = x;  
            y1 = y;  
            x = h;  
            y = k;  
        }  
  putPixel (x1, y1);  
  while (x1 < x)  
  {  
    if (d < 0)  
        d += ds;  
        else {  
             if (y1 < y) {  
               y1++;  
               d += dt;  
				}   
             else {  
				y1--;  
				d += dt;             
			 }  
		}  
        x1++;  
		putPixel (x1, y1);  
    }  
}  
       else {   
           int d = 2*dx-dy;  
             int ds = 2*dx;  
             int dt = 2*(dx-dy);  
             if (k < y) 
			 {  
				 x1 = h;  
				 y1 = k;  
             }  
             else 
			 {   
				 x1 = x;  
				 y1 = y;  
				 y = k;  
			     x = h;  
             }  
            putPixel (x1, y1);   
        while (y1 < y)  
        {  
              if (d < 0)  
                 d += ds;  
             else {  
                   if (x1 < x)
				   {  
						x1++;  
						d += dt;  
					} else 
					{  
						x1--;  
						d += dt;  
					}                
				}  
			y1++;  
             putPixel (x1, y1);
			 
       }        
	}  
}  
 
void drawBresenhamsLine(int h, int k, int x, int y)
{
	bresenhamLine(-x+h,y+k,x+h,y+k);
	bresenhamLine(-y+h,x+k,y+h,x+k);
	bresenhamLine(-y+h,-x+k,y+h,-x+k);
	bresenhamLine(-x+h,-y+k,x+h,-y+k);
}
//midpoint Circle
void midCircle(int h, int k, int r)
{
	int x=0, y=r, p=1-r;
	while(x <= y)
	{
		plotCircle(h, k, x, y);
		drawBresenhamsLine(h, k, x, y);
		if(p<0)
		{
			p=p+2*x+3; 
		}
		else
		{
			p = p+2*(x-y)+5;
			y--;
		}
		x++;
	}
}

void mouse(int btn, int state, int x, int y)
{
	
	if (btn == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN)
		{
			xi = x;
			yi = (wh - y);
		}
		else if (state == GLUT_UP) {
			xf = x;
			yf = (wh - y);
			glutPostRedisplay();
			int r = (int) sqrt((double)(xi-xf)*(xi-xf)+(yi-yf)*(yi-yf));
			midCircle (xi, yi, r);
		}
	if (btn == GLUT_RIGHT_BUTTON) {
		glClear(GL_COLOR_BUFFER_BIT);
		glFlush();
	}
}




void myinit()  
{        
     glViewport(0,0,ww,wh);  
     glMatrixMode(GL_PROJECTION);  
     glLoadIdentity();  
     gluOrtho2D(0.0,(GLdouble)ww,0.0,(GLdouble)wh);  
     glMatrixMode(GL_MODELVIEW);  
}  
int main(int argc, char** argv)  
{  
     glutInit(&argc,argv);  
     glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);  
     glutInitWindowSize(ww,wh);  
     glutCreateWindow("Bresenham line Algorithm midpoint");  
     glutDisplayFunc(display);  
     myinit();  
     glutMouseFunc(mouse);  
     glutMainLoop();  
     return 0;  
}
