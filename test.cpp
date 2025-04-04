#include <windows.h>
#include <glut.h>

void init()
{
	glClearColor (1.0, 0.0, 0.0, 1.0);

	glColor3f(1.0, 1.0, 1.0); 

	glMatrixMode (GL_PROJECTION);    
	glLoadIdentity ();    
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);  
}


void mydisplay(){
    glClear(GL_COLOR_BUFFER_BIT); 
	glBegin(GL_POLYGON);              
		glVertex2f(-0.5, 0.0); 
		glVertex2f(-0.25, 0.5);  
		glVertex2f(0.25, 0.5);
		glVertex2f(0.5, 0.0);
		glVertex2f(0.25, -0.5);
		glVertex2f(-0.25, -0.5);
	glEnd();

	glBegin(GL_POLYGON);              
		glVertex2f(-0.8, 0.0); 
		glVertex2f(-0.7, 0.25);  
		glVertex2f(-0.6, 0.0);
	glEnd();

	glFlush(); 
}
void mydisplay2(){
    glClear(GL_COLOR_BUFFER_BIT); 
	glPointSize(10.0f);
	glBegin(GL_POINTS);               
		glVertex2f(-0.4, 0.5);        
		glVertex2f(-0.3, 0.5);        
		glVertex2f(-0.2, 0.5);
		glVertex2f(-0.1, 0.5);
		glVertex2f(0.0, 0.5);
		glVertex2f(0.1, 0.5);
		glVertex2f(0.2, 0.5);
		glVertex2f(0.3, 0.5);
		glVertex2f(0.4, 0.5);

		glVertex2f(0.0, 0.4);
		glVertex2f(0.0, 0.3);
		glVertex2f(0.0, 0.2);
		glVertex2f(0.0, 0.1);
		glVertex2f(0.0, 0.0);

	glEnd();
	glFlush(); 
}
void mydisplay3(){
    glClear(GL_COLOR_BUFFER_BIT); 
	glLineWidth(3.0f);
	glBegin(GL_LINES);        
		glVertex2f(-0.5, -0.5);        
		glVertex2f(-0.5, 0.5);        
		glVertex2f(0.5, 0.5);        
		glVertex2f(0.25, -0.75); 

		glVertex2f(-0.5, -0.5);        
		glVertex2f(0.25, -0.75); 

		glVertex2f(-0.5, 0.5);         
		glVertex2f(0.5, 0.5); 

	glEnd();
	glFlush(); 
}
void mydisplay4(){
    glClear(GL_COLOR_BUFFER_BIT); 
	glLineWidth(3.0f);
	glBegin(GL_LINE_LOOP);        
		glVertex2f(-0.5, -0.5);        
		glVertex2f(-0.5, 0.5);        
		glVertex2f(0.5, 0.5);        
		glVertex2f(0.25, -0.75);    
	glEnd();
	glFlush(); 
}

int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);  
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("simple");     
	glutDisplayFunc(mydisplay3);  
	init();  
	glutMainLoop();
}