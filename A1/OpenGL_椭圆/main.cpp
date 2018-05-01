//÷–µ„À„∑®
#include<stdlib.h>
#include<math.h>
#include<iostream.h>
#include<GL/glut.h>
inline int round (const float a){return int (a+0.5);}
GLint xCenter=0;
GLint yCenter=0;
GLint x=100;
GLint y=50;

void setPixel(GLint xC, GLint yC)
{
	glBegin(GL_POINTS);
		glVertex2i(xC,yC);
	glEnd();
}

void ellipseMidepoint (int xCenter ,int yCenter ,int Rx,int Ry)
{
	int Rx2 = Rx * Rx;
	int Ry2 = Ry * Ry;
	int twoRx2 = 2 * Rx2;
	int twoRy2 = 2 * Ry2;
	int p;
	int x = 0;
	int y = Ry;
	int px= 0;
	int py = twoRx2 * y;
	void ellipsePlotPoints(int ,int ,int,int );
	ellipsePlotPoints(xCenter,yCenter,x,y);
	p= round(Ry2 - (Rx2 * Ry)+(0.25 * Rx2));
	while(px<py){
		x++;
		px+=twoRy2;
		if(p<0)
			p+=Ry2+px;
		else{
			y--;
			py-=twoRx2;
			p+=Ry2+px-py;
		}
		ellipsePlotPoints(xCenter,yCenter,x,y);
	}

	p = round(Ry2 *(x+0.5)*(x+0.5)+Rx2*(y-1)*(y-1)-Rx2*Ry2);
	while(y>0){
		y--;
		py -=twoRx2;
		if(p>0)
			p+=Rx2-py;
		else{
			x++;
			px +=twoRy2;
			p += Rx2 - py +px;
		}
		ellipsePlotPoints(xCenter,yCenter,x,y);
	}
}

void ellipsePlotPoints(int xCenter,int yCenter,int x,int y)
{
	setPixel(xCenter+x, yCenter+y);
	setPixel(xCenter-x, yCenter+y);
	setPixel(xCenter+x, yCenter-y);
	setPixel(xCenter-x, yCenter-y);		
}


void init()
{
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,200.0,0.0,150.0);
}

void lineSegment()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0,0.0,0.0);
    ellipseMidepoint(xCenter,yCenter,x,y);
	glFlush();
 }
void reshape(int w, int h)
{
	glViewport(0.0,0.0,w,h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float aspectRatio=(GLfloat)w/(GLfloat)h;
	if(w<=h)
	gluOrtho2D(-100.0, 100.0, -100.0/aspectRatio, 100.0/aspectRatio);
	//glOrtho(-600.0, 600.0, -600.0/aspectRatio, 600.0/aspectRatio, 5.0, -5.0);
	//gluPerspective(90.0,aspectRatio,5.0,5.0);
	else
	//gluPerspective(90.0,aspectRatio,5.0,5.0);
	gluOrtho2D(-100.0*aspectRatio, 100.0*aspectRatio, -100.0, 100.0);
	//glOrtho(-600.0*aspectRatio, 600.0*aspectRatio, -600.0, 600.0, 5.0, -5.0);



	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); 
}
void main(int argc, char** argv)
{
    
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(800,600);
	glutCreateWindow("ª≠Õ÷‘≤");

	init();
	glutDisplayFunc(lineSegment);
	glutReshapeFunc(reshape);
	glutMainLoop();

}