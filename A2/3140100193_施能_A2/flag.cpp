#define FREEGLUT_STATIC
#pragma comment(lib,"freeglut_staticd.lib")

#include <GL/freeglut.h>
#include <math.h>

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);//窗口背景设为白色
    glMatrixMode(GL_PROJECTION);//设置投影参数
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void TRIANGLE(float i, float j, int r)
{
    float PI = 3.14;
    GLfloat ax = 0;
    GLfloat ay = r;
    GLfloat bx = r*cos(18 * PI / 180);
    GLfloat by = r*sin(18 * PI / 180);
    GLfloat cx = r*cos(54 * PI / 180);
    GLfloat cy = -r*sin(54 * PI / 180);
    GLfloat dx = -cx;
    GLfloat dy = cy;
    GLfloat ex = -bx;
    GLfloat ey = by;

    glColor3f(1.0, 1.0, 1.0);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(0.8353, 0.01686, 0.1176);
    glBegin(GL_QUADS);
    glVertex2i(0, 0);
    glVertex2i(0, 80);
    glVertex2i(240, 80);
    glVertex2i(240, 0);
    glEnd();

    glColor3f(0.0, 0.2235, 0.6510);
    glBegin(GL_QUADS);
    glVertex2i(0, 80);
    glVertex2i(0, 160);
    glVertex2i(80, 160);
    glVertex2i(80, 80);
    glEnd();

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_QUADS);
    glVertex2i(80, 80);
    glVertex2i(80, 160);
    glVertex2i(240, 160);
    glVertex2i(240, 80);
    glEnd();

    TRIANGLE(40, 120, 20);
    glFlush();
}

void main(int argc, char**argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Chilean flag");
    init();
    glutDisplayFunc(flagSegment);
    glutMainLoop();
}