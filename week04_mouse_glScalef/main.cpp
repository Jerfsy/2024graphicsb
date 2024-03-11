#include <GL/glut.h>
float s = 1;
void display()
{

    glClearColor(1,1,0.9,1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glColor3f(0,1,0);
    glPushMatrix();
        glScalef(s,s,s);
        glutSolidTeapot( 0.3 );
    glPopMatrix();
    glutSwapBuffers();
}
void motion(int x, int y)
{
    s = 1 + (x-150)/150.0;
    display();
}
int main(int argc, char*argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("week04_mouse_glScalef");
    glutDisplayFunc(display);
    glutMotionFunc(motion);
    glutMainLoop();
}
