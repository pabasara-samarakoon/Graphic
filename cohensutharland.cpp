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
// Function to clip a line using Cohen-Sutherland algorithm
void cohenSutherland(int x0, int y0, int x1, int y1) {
    int outcode0, outcode1, outcode;
    bool accept = false, done = false;

    outcode0 = computeOutCode(x0, y0);
    outcode1 = computeOutCode(x1, y1);

    do {
        if (!(outcode0 | outcode1)) { // Trivially accepted
            accept = true;
            done = true;
        } else if (outcode0 & outcode1) { // Trivially rejected
            done = true;
        } else {
            float x, y;
            outcode = outcode0 ? outcode0 : outcode1;

            if (outcode & TOP) {
                x = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
                y = ymax;
            } else if (outcode & BOTTOM) {
                x = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
                y = ymin;
            } else if (outcode & RIGHT) {
                y = y0 + (y1 - y0) * (xmax - x0) / (x1 - x0);
                x = xmax;
            } else if (outcode & LEFT) {
                y = y0 + (y1 - y0) * (xmin - x0) / (x1 - x0);
                x = xmin;
            }

            if (outcode == outcode0) {
                x0 = x;
                y0 = y;
                outcode0 = computeOutCode(x0, y0);
            } else {
                x1 = x;
                y1 = y;
                outcode1 = computeOutCode(x1, y1);
            }
        }
    } while (!done);

    if (accept) {
        glColor3f(1.0, 0.0, 0.0);
		bresenhamAlg ( x0,  y0,  x1,  y1);
    }
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
			cohenSutherland( xi, yi, xf, yf);
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
     glutCreateWindow("Bresenham Line Algorithm");  
     glutDisplayFunc(display);  
     myinit();  
     glutMouseFunc(mouse);  
     glutMainLoop();  
     return 0;  
}  