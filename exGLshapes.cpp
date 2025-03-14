#include <Windows.h>
#include <GL/glut.h>

float red = 1.0, green = 0.0, blue = 0.0; // Initial color

void display1() {
    glClear(GL_COLOR_BUFFER_BIT); 

    glColor3f(red, green, blue); 
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.5, -0.5);
        glVertex2f( 0.5, -0.5);
        glVertex2f( 0.5,  0.5);      
    glEnd();

    glFlush();
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT); 

    glBegin(GL_POLYGON);
		glColor3f(1.0f,1.0f,1.0f); 
        glVertex2f(-0.1, 0.1);
		glColor3f(1.0f,0.0f,0.0f); 
		glVertex2f(0.1, 0.1);
		glColor3f(1.0f,1.0f,0.0f); 
		glVertex2f(0.2, 0.2);
		glColor3f(0.0f,1.0f,0.0f); 
		glVertex2f(0.2, 0.3);
		glColor3f(0.0f,1.0f,1.0f);
		glVertex2f(0.1, 0.4);
		glColor3f(0.0f,0.0f,1.0f); 
		glVertex2f(-0.1, 0.4);
		glColor3f(1.0f,0.0f,1.0f); 
		glVertex2f(-0.2, 0.3);
		glColor3f(0.0f,0.0f,0.0f); 
		glVertex2f(-0.2, 0.2);
    glEnd();
    glFlush();
}

void display2() {
    glClear(GL_COLOR_BUFFER_BIT);  
    glBegin(GL_TRIANGLES);//each set of 3 verticles from traingle
		glColor3f(1.0f,1.0f,0.0f);
        glVertex2f(0.1f, -0.6f);  
		glVertex2f(0.7f, -0.6f);  
		glVertex2f(0.4f, -0.1f);  

		glColor3f(1.0f,0.0f,0.0f);//red
        glVertex2f(0.3f, -0.4f);
		glColor3f(0.0f,1.0f,0.0f);//green
        glVertex2f(0.9f, -0.4f);
		glColor3f(0.0f,0.0f,1.0f);//blue
        glVertex2f(0.6f, -0.9f);
    glEnd();

    glFlush();
}

void display3() {
    glClear(GL_COLOR_BUFFER_BIT);  
    glBegin(GL_QUAD_STRIP);//each set of 3 verticles from traingle 
		glColor3f(1.0f,0.0f,0.0f);//red
        glVertex2f(0.0f, 0.0f);
		glColor3f(1.0f,1.0f,0.0f);//green
        glVertex2f(-0.2f, -0.4f);
		glColor3f(1.0f,1.0f,1.0f);//blue
        glVertex2f(0.2f, -0.4f);
		
		glColor3f(0.0f,0.0f,1.0f);
        glVertex2f(0.0f, 0.0f);
		glColor3f(1.0f,0.0f,1.0f);
        glVertex2f(0.4f, 0.2f);
		glColor3f(1.0f,1.0f,1.0f);
        glVertex2f(0.4f, -0.2f);

		glColor3f(0.0f,1.0f,0.0f);//red
        glVertex2f(0.0f, 0.0f);
		glColor3f(0.0f,1.0f,1.0f);//green
        glVertex2f(0.2f, 0.4f);
		glColor3f(1.0f,1.0f,1.0f);//blue
        glVertex2f(-0.2f, 0.4f);

		glColor3f(0.0f,0.0f,1.0f);//red
        glVertex2f(0.0f, 0.0f);
		glColor3f(0.0f,1.0f,1.0f);//green
        glVertex2f(-0.4f, 0.2f);
		glColor3f(1.0f,1.0f,1.0f);//blue
        glVertex2f(-0.4f, -0.2f);

    glEnd();

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'r') { red = 1.0; green = 0.0; blue = 0.0; }  // Red
    if (key == 'g') { red = 0.0; green = 1.0; blue = 0.0; }  // Green
    if (key == 'b') { red = 0.0; green = 0.0; blue = 1.0; }  // Blue

    glutPostRedisplay(); // Request to redraw the window
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("GLUT PostRedisplay Example");

    glutDisplayFunc(display3);

    glutKeyboardFunc(keyboard); // Register keyboard callback

    glutMainLoop();
    return 0;
}