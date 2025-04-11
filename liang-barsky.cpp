#include <glut.h>  
#include <math.h>  
int ww = 600, wh = 400;    
int xi, yi, xf, yf;  
// Define the region codes
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000

// Define the clipping window
const float xmin = 50, xmax = 250, ymin = 50, ymax = 250;

void putPixel (int x, int y)  
{  
   glColor3f (0.3, 0.2, 0.0); // activate the pixel by setting the point color to white  
   glBegin (GL_POINTS);  
   glVertex2i (x, y); // set the point  
   glEnd ();  
   glFlush (); // process all openGL routines as quickly as possible  
} 

void bresenhamAlg (int x0, int y0, int x1, int y1)  
{  
  int dx = abs (x1 - x0);  
  int dy = abs (y1 - y0);  
  int x, y;  
  if (dx >= dy)  
  {  
   int d = 2*dy-dx;  
   int ds = 2*dy;  
   int dt = 2*(dy-dx);  
       if (x0 < x1)   
       {  
            x = x0;  
            y = y0;  
        }  
        else  
        {   
            x = x1;  
            y = y1;  
            x1 = x0;  
            y1 = y0;  
        }  
  putPixel (x, y);  
  while (x < x1)  
  {  
    if (d < 0)  
        d += ds;  
        else {  
             if (y < y1) {  
               y++;  
               d += dt;  
				}   
             else {  
				y--;  
				d += dt;             
			 }  
		}  
        x++;  
		putPixel (x, y);  
    }  
}  
       else {   
           int d = 2*dx-dy;  
             int ds = 2*dx;  
             int dt = 2*(dx-dy);  
             if (y0 < y1) 
			 {  
				 x = x0;  
				 y = y0;  
             }  
             else 
			 {   
				 x = x1;  
				 y = y1;  
				 y1 = y0;  
				x1 = x0;  
             }  
            putPixel (x, y);   
        while (y < y1)  
        {  
              if (d < 0)  
                 d += ds;  
             else {  
                   if (x < x1)
				   {  
						x++;  
						d += dt;  
					} else 
					{  
						x--;  
						d += dt;  
					}                
				}  
			y++;  
             putPixel (x, y);
			 
       }        
	}  
}  
// Function to compute the region code of a point
int computeOutCode(int x, int y) {
    int code = INSIDE;

    if (x < xmin)
        code |= LEFT;
    else if (x > xmax)
        code |= RIGHT;
    if (y < ymin)
        code |= BOTTOM;
    else if (y > ymax)
        code |= TOP;

    return code;
}
// Function to clip a line using Liang Barsky algorithm
void liangBarsky(int x0, int y0, int x1, int y1) {

	//int outcode0, outcode1, outcode;
   // bool accept = false, done = false;

    //outcode0 = computeOutCode(x0, y0);
    //outcode1 = computeOutCode(x1, y1);

    float t0 = 0.0 , t1 = 1.0;
    float dx=x1-x0 , dy=y1-y0;
	float p,q,r;

	for(int edge = 0 ; edge < 4 ; edge ++){
		if(edge==0){
			p = -dx;
			q = x0-LEFT;
		}else if(edge==1){
			p = dx;
			q = RIGHT - x0;
		}else if(edge==2){
			p = -dy;
			q = y0 - BOTTOM;
		}else{
			p = dy;
			q = TOP - y0;
		}
		r = q/p ;
		if (p==0 && q < 0)
			return;
		if (p<0){
			if(r>t1)
				return;
			else if(r>t0)
				t0 = r;
		}
		else if(p>0){
			if(r<t0)
				return;
			else if(r<t1)
				t1 = r;
		}
	}

	float x_clipped = x0 + t0*dx;
	float y_clipped = y0 + t0*dy;
	float x_clipped_end = x0 + t1*dx;
	float y_clipped_end = y0 + t1*dy;

   // if (accept) {
        glColor3f(1.0, 0.0, 0.0);
		bresenhamAlg ( x0,  y0,  x1,  y1);
   // }
}

 
void display()  
{  

   glClearColor(0.4, 0.7, 0.5, 1.0);  
   glColor3f(0.2, 0.3, 0.3);  
   glClear(GL_COLOR_BUFFER_BIT);  
   glFlush();  
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
			glBegin(GL_LINE_LOOP);
			glVertex2f(xmin, ymin);
			glVertex2f(xmax, ymin);
			glVertex2f(xmax, ymax);
			glVertex2f(xmin, ymax);
			glEnd();
			glutPostRedisplay();
			liangBarsky( xi, yi, xf, yf);
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
     glutCreateWindow("liang barsky Algorithm");  
     glutDisplayFunc(display);  
     myinit();  
     glutMouseFunc(mouse);  
     glutMainLoop();  
     return 0;  
}  