#include <opencv/highgui.h> ///使用 OpenCV 2.1 比較簡單, 只要用 High GUI 即可
#include <opencv/cv.h>
#include <GL/glut.h>
int myTexture(char * filename)
{
    IplImage * img = cvLoadImage(filename); ///OpenCV讀圖
    cvCvtColor(img,img, CV_BGR2RGB); ///OpenCV轉色彩 (需要cv.h)
    glEnable(GL_TEXTURE_2D); ///1. 開啟貼圖功能
    GLuint id; ///準備一個 unsigned int 整數, 叫 貼圖ID
    glGenTextures(1, &id); /// 產生Generate 貼圖ID
    glBindTexture(GL_TEXTURE_2D, id); ///綁定bind 貼圖ID
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖T, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); /// 貼圖參數, 超過包裝的範圖S, 就重覆貼圖
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); /// 貼圖參數, 放大時的內插, 用最近點
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); /// 貼圖參數, 縮小時的內插, 用最近點
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->width, img->height, 0, GL_RGB, GL_UNSIGNED_BYTE, img->imageData);
    return id;
}

///上週有做過, 請用剪貼的
#include <GL/glut.h>
#include "glm.h"
GLMmodel * pmodel = NULL;
GLMmodel * hand1 = NULL;
GLMmodel * hand2 = NULL;
void drawmodel(void)
{
    if (!pmodel) {
        pmodel = glmReadOBJ("Gundam.obj");
        if (!pmodel) exit(0);
        glmUnitize(pmodel);
        glmFacetNormals(pmodel);
        glmVertexNormals(pmodel, 90.0);
    }
    glmDraw(pmodel, GLM_SMOOTH | GLM_TEXTURE);
}
void drawhand1(void)
{
    if (!hand1) {
        hand1 = glmReadOBJ("hand1.obj");
        if (!hand1) exit(0);
        glmUnitize(hand1);
        glmFacetNormals(hand1);
        glmVertexNormals(hand1, 90.0);
    }
    glmDraw(hand1, GLM_SMOOTH | GLM_TEXTURE);
}
void drawhand2(void)
{
    if (!hand2) {
        hand2 = glmReadOBJ("hand2.obj");
        if (!hand2) exit(0);
        glmUnitize(hand2);
        glmFacetNormals(hand2);
        glmVertexNormals(hand2, 90.0);
    }
    glmDraw(hand2, GLM_SMOOTH | GLM_TEXTURE);
}
float angle=0; ///加入旋轉
void display()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glutWireCube(0.6);
    glutSolidSphere( 0.1, 30, 30 ); ///week11-3
    glPushMatrix(); ///加入旋轉
        ///glRotatef(angle++, 0, 1, 0); ///加旋轉
        glTranslatef(-0.3,0.3,0);///(3) 把旋轉中的手,掛到肩上
        glRotatef(angle++,0,0,1);///(2) 旋轉
        glTranslatef(0,-0.3,0);///(1) 把旋轉中心,放到正中心 (有個球在正中心)
        drawhand1(); ///week11-3
    glPopMatrix(); ///加入旋轉
    glutSwapBuffers();
}
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, -5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
    glutCreateWindow("week11-2 obj gundam opencv texture");
    glutDisplayFunc(display);
    glutIdleFunc(display); ///加入旋轉
    myTexture("Diffuse.jpg");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
    glutMainLoop();
}
