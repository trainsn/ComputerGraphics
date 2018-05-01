#define FREEGLUT_STATIC
#pragma comment(lib,"freeglut_staticd.lib")

#include <GL/freeglut.h>  
#include <math.h>  

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);  //���ڱ�������Ϊ��ɫ
    glMatrixMode(GL_PROJECTION);    //����ͶӰ����
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void TRIANGLE(float i, float j, int r)
{
    float PI = 3.14;
    float ax, ay, bx, by, cx, cy, dx, dy, ex, ey;
    ax = 0;
    ay = r;
    bx = r*cos(18 * PI / 180);
    by = r*sin(18 * PI / 180);
    ex = -bx;
    ey = by;
    cx = r*sin(36 * PI / 180);
    cy = -r*cos(36 * PI / 180);
    dx = -cx;
    dy = cy;

    glColor3f(1.0, 1.0, 0.0);
    glBegin(GL_TRIANGLES);
    glVertex2i(i, j);
    glVertex2i(i + ax, j + ay);
    glVertex2i(i + dx, j + dy);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2i(i, j);
    glVertex2i(i + ax, j + ay);
    glVertex2i(i + cx, j + cy);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2i(i, j);
    glVertex2i(i + bx, j + by);
    glVertex2i(i + ex, j + ey);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2i(i, j);
    glVertex2i(i + bx, j + by);
    glVertex2i(i + dx, j + dy);
    glEnd();

    glBegin(GL_TRIANGLES);
    glVertex2i(i, j);
    glVertex2i(i + cx, j + cy);
    glVertex2i(i + ex, j + ey);
    glEnd();


}

void flagSegment(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glColor3f(1.0, 0.0, 0.0);        //��ɫΪ��ɫ
    glBegin(GL_QUADS);
    glVertex2i(13, 140);
    glVertex2i(100, 140);
    glVertex2i(100, 80);
    glVertex2i(13, 80);
    glEnd();

    TRIANGLE(28, 123, 9);

    glTranslatef(40.0f, 135.0f, 0.0f);
    glPushMatrix();
    glRotatef(-30.0f, 0.0f, 0.0f, 1.0f);
    TRIANGLE(0, 0, 4);
    glPopMatrix();

    glTranslatef(7.0f, -7.0f, 0.0f);
    glPushMatrix();
    glRotatef(30.0f, 0.0f, 0.0f, 1.0f);
    TRIANGLE(0, 0, 4);
    glPopMatrix();

    glTranslatef(0.0f, -10.0f, 0.0f);
    TRIANGLE(0, 0, 4);
    glTranslatef(-7.0f, -6.0f, 0.0f);
    glPushMatrix();
    glRotatef(-30.0f, 0.0f, 0.0f, 1.0f);
    TRIANGLE(0, 0, 4);
    glPopMatrix();
    glFlush();                     //��Ⱦ
}

void main(int argc, char** argv)
{
    glutInit(&argc, argv);                         //��ʼ��GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  //������ʾģʽ
    glutInitWindowPosition(100, 100);               //������ʾ���ڵ����Ͻ�λ��
    glutInitWindowSize(800, 600);                  //���ô��ڵĳ��͸�
    glutCreateWindow("An Example OpenGL Program");     //������ʾ����
    init();                                       //��ʼ��ʼ������
    glutDisplayFunc(flagSegment); //����ͼ�ε���ʾ����
    //glutReshapeFunc(reshape);
    glutMainLoop();              //��ʾ���в��Ⱥ�
}
