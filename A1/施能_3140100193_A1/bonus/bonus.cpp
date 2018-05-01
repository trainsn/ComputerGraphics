#define FREEGLUT_STATIC
#pragma comment(lib,"freeglut_staticd.lib")

#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<GL/freeglut.h>

typedef  float Color[3];

inline int Round(const float a)
{
    return int(a + 0.5);
}
void setPixel(GLint x, GLint y)
{
    glColor3f(1.0, 0, 0);        //图形以红色画出
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void ellipsePlotPoints(int xCenter, int yCenter, int x, int y)
{
    setPixel(xCenter + x, yCenter + y);
    setPixel(xCenter - x, yCenter + y);
    setPixel(xCenter + x, yCenter - y);
    setPixel(xCenter - x, yCenter - y);
}
void ellipseMidpoint(void)
{
    int xCenter = 400, yCenter = 400, Rx = 150, Ry = 200;
    int Rx2 = Rx * Rx;
    int Ry2 = Ry * Ry;
    int twoRx2 = 2 * Rx2;
    int twoRy2 = 2 * Ry2;
    int p;
    int x = 0;
    int y = Ry;
    int px = 0;
    int py = twoRx2 * y;
    void ellipsePlotPoints(int, int, int, int);
    glClear(GL_COLOR_BUFFER_BIT);
    /* Plot the initial point in each quadrant. */
    ellipsePlotPoints(xCenter, yCenter, x, y);
    /* Region 1 */
    p = Round(Ry2 - (Rx2 * Ry) + (0.25 * Rx2));
    while (px < py)
    {
        x++;
        px += twoRy2;
        if (p < 0)
            p += Ry2 + px;
        else
        {
            y--;
            py -= twoRx2;
            p += Ry2 + px - py;
        }
        ellipsePlotPoints(xCenter, yCenter, x, y);
    }
    /* Region 2 */
    p = Round(Ry2 * (x + 0.5) * (x + 0.5) + Rx2 * (y - 1) * (y - 1) - Rx2 * Ry2);
    while (y > 0)
    {
        y--;
        py -= twoRx2;
        if (p > 0)
            p += Rx2 - py;
        else
        {
            x++;
            px += twoRy2;
            p += Rx2 - py + px;
        }
        ellipsePlotPoints(xCenter, yCenter, x, y);
    }
}


void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);  // 将屏幕设置为白色
    glMatrixMode(GL_PROJECTION);       // 设置投影参数
    gluOrtho2D(0.0, 900.0, 0.0, 900.0);

}

void myDraw(void)
{
    ellipseMidpoint();      
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);                         // 初始化
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);   // 设置显示模式
    glutInitWindowPosition(50, 100);   // 设置屏幕位置
    glutInitWindowSize(800, 800);      // 设置屏幕大小
    glutCreateWindow("Draw a Ellipse"); // 生成屏幕
    init();                            
    glutDisplayFunc(myDraw);       
    glutMainLoop();                   
    return 0;
}

