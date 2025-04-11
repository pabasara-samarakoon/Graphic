#include <glut.h>
#include <math.h>

float angle = 0;

void display() {
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  glRotatef(angle, 0.0, 0.0, 1.0);
  glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
  glEnd();
  glPopMatrix();
  glutSwapBuffers();
}

void animate(int value) {
  angle += 2.0;
  if (angle > 360) angle -= 360;
  glutPostRedisplay();
  glutTimerFunc(25, animate, value);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(500, 500);
  glutCreateWindow("Rotation Animation");
  glutDisplayFunc(display);
  glutTimerFunc(25, animate, 0);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
  glutMainLoop();
  return 0;
}