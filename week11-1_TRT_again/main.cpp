#include <GL/glut.h>
void myBody()
{
    glColor3f(1,0,0);
    glutSolidCube(0.6);
}

void myArm()
{
    glPushMatrix();
    glColor3f(0,1,0);
    glScalef(1.5,0.5,0.5);
    glutSolidCube(0.3);
    glPopMatrix();
}
float angle=0;
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        myBody();
    glPopMatrix();
    glPushMatrix();
        //glTranslatef(0.3,0.3,0);
        glRotatef(angle++,0,0,1);
        glTranslatef(0.45/2,0,0);
        myArm();
    glPopMatrix();
    glutSwapBuffers();

}
int main(int argc, char * argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");
    glutIdleFunc(display);
    glutDisplayFunc(display);

    glutMainLoop();
}
