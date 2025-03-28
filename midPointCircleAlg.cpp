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
	putPixel((x+h), (y+k)); //x,y
	putPixel((y+h), (x+k));//y, x
	putPixel((-y+h), (x+k));//-y, x
	putPixel((-x+h), (y+k));//-x, y
	putPixel((-x+h), (-y+k));//-x,-y
	putPixel((-y+h), (-x+k));//-y,-x
	putPixel((y+h), (-x+k));//y,-x
	putPixel((x+h), (-y+k));//x,-y

}


void display()  
{  
   glClearColor(0.4, 0.7, 0.5, 1.0);  
   glColor3f(0.2, 0.3, 0.3);  
   glClear(GL_COLOR_BUFFER_BIT);  
   glFlush();  
} 

void midPointCircleAlg(int h, int k, int r)
{
	int x=0, y=r, p= 1-r;
	while(x <= y)
	{
		plotCircle(h, k, x, y);
		if(p<0)
		{
			p = p + 2*x +3;
		}
		else
		{
			p = p + 2*(x-y) +5;
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
			glutPostRedisplay();//if this removed we can display all outputs
			int r = (int) sqrt((double)(xi-xf)*(xi-xf)+(yi-yf)*(yi-yf));
			 midPointCircleAlg (xi, yi, r);
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
     glutCreateWindow("MidPoint Circle Algorithm");  
     glutDisplayFunc(display);  
     myinit();  
     glutMouseFunc(mouse);  
     glutMainLoop();  
     return 0;  
}