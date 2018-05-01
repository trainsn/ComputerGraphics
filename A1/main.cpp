#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

typedef  float Color[3];

inline int round (const float a)
{
    return int (a + 0.5);
}
void setPixel(GLint x,  GLint y)
{
    glColor3f (1.0, 0, 0);        //图形以红色画出
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
    glFlush();
}

void ellipsePlotPoints (int xCenter, int yCenter, int x, int y)
{
    setPixel (xCenter + x, yCenter + y);
    setPixel (xCenter - x, yCenter + y);
    setPixel (xCenter + x, yCenter - y);
    setPixel (xCenter - x, yCenter - y);
}
void ellipseMidpoint (void)
{
    int xCenter=400,  yCenter=400,  Rx=150, Ry=200;
    int Rx2 = Rx * Rx;
    int Ry2 = Ry * Ry;
    int twoRx2 = 2 * Rx2;
    int twoRy2 = 2 * Ry2;
    int p;
    int x = 0;
    int y = Ry;
    int px = 0;
    int py = twoRx2 * y;
    void ellipsePlotPoints (int, int, int, int);
    glClear (GL_COLOR_BUFFER_BIT);
    /* Plot the initial point in each quadrant. */
    ellipsePlotPoints (xCenter, yCenter, x, y);
    /* Region 1 */
    p = round (Ry2 - (Rx2 * Ry) + (0.25 * Rx2));
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
        ellipsePlotPoints (xCenter, yCenter, x, y);
    }
    /* Region 2 */
    p = round (Ry2 * (x+0.5) * (x+0.5) + Rx2 * (y-1) * (y-1) - Rx2 * Ry2);
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
        ellipsePlotPoints (xCenter, yCenter, x, y);
    }
}


void init (void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0);  // Set display-window color to white.
    glMatrixMode (GL_PROJECTION);       // Set projection parameters.
    gluOrtho2D (0.0, 900.0, 0.0, 900.0);

}

void myDraw(void)
{
    ellipseMidpoint();       // Send graphics to display window.
    Color fillColor= {0.0,0,1.0},borderColor= {1.0,0,0};
}

int main (int argc, char** argv)
{
    glutInit (&argc, argv);                         // Initialize GLUT.
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);   // Set display mode.
    glutInitWindowPosition (50, 100);   // Set top-left display-window position.
    glutInitWindowSize (800, 800);      // Set display-window width and height.
    glutCreateWindow ("Draw a Ellipse"); // Create display window.
    init ( );                            // Execute initialization procedure.
    glutDisplayFunc (myDraw);       // Send graphics to display window.
    glutMainLoop ( );                    // Display everything and wait.
    return 0;
}

