#include <glut.h>

float x = 0;
bool isAnimating = true;   

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
 // glPushMatrix();
 // glRotatef(angle, 0.0, 0.0, 1.0);
  glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(x - 0.5, -0.5);
    glVertex2f(x - 0.5, 0.5);
    glVertex2f(x + 0.5, 0.5);
    glVertex2f(x + 0.5, -0.5);
  glEnd();
  glutSwapBuffers();
}

void animate(int value) {
  x += 0.01;
  if (x > 1.5) x = -1.5;
  //angle += 2.0;
 // if (angle > 360) angle -= 360;
  glutPostRedisplay();
  glutTimerFunc(10, animate, value);
}
void keyboard(unsigned char key, int x, int y) {
	if (key == 's' || key == 'S') {
        isAnimating = !isAnimating;  // Toggle the animation state
    }  
    glutPostRedisplay(); // Request to redraw the window
}
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Translation Animation");
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutTimerFunc(25, animate, 0);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.5, 1.5, -1.0, 1.0, -1.0, 1.0);
  glutMainLoop();
  return 0;
}

