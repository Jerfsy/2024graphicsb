#include <GL/glut.h>
void display()
{

    glBegin(GL_POLYGON);
        glColor3f(1,1,1);
        glVertex2f((30-200)/200.0, -(45-200)/200.0);
        glVertex2f((46-200)/200.0, -(102-200)/200.0);
        glVertex2f((84-200)/200.0, -(23-200)/200.0);
        glEnd();
    glutSwapBuffers();
}

int main(int argc, char*argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("week02_glut_color_teapot");
    glutDisplayFunc(display);
    glutMainLoop();
}
