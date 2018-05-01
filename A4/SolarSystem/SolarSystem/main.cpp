#define FREEGLUT_STATIC
#pragma comment(lib,"freeglut_staticd.lib")

#include <cmath>
#include <cstdlib>
#include <cstdio>

#include <gl\freeglut.h>

#include "tga.h"
#include "solarsystem.h"
#include "camera.h"
#include "globals.h"

//the screen size
int screenWidth, screenHeight;

//The TGA texture containing the star field and moon texture
TGA *stars, *moon;
//toggles if orbits are drawn
bool showOrbits = true;
//holds the index of the last planet that was selected with the 1 to 9 number keys 
int planetSelectd = 1;

//The main instance of the solar system
SolarSystem solarSystem;

//The instance of the camera
Camera camera;

//These control the simulation of time
float time;
float timeSpeed;

//holds the state of the controls for the camera - when true, the key for that control is being pressed
struct ControlStates
{
    bool forward, backward, left, right, yawLeft, yawRight;
}controls;

//time function called every 10ms or more
void timer(int)
{
    glutPostRedisplay();//标记当前窗口需要重新绘制
    glutTimerFunc(10, timer, 0);//limit frame drawing to 100fps
}

//creates a random number up to the max specified 
float random(float max)
{
    return (float)(std::rand() % 1000)*max*0.001;
}

//adds a moon to the selected planet
void addMoon()
{
    //make a moon using random values
    solarSystem.addMoon(planetSelectd, (500 + random(1500))*solarSystem.getRadiusOfPlanet(planetSelectd), 10 + random(100), 0.5 + random(20), solarSystem.getRadiusOfPlanet(planetSelectd)*(0.2f + random(0.2f)), moon->getTextureHandle());
}

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_TEXTURE_2D);

    //set up lighting
    glEnable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    GLfloat matSpecular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat matAmbience[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat matShininess[] = { 20.0 };
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);
    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbience);

    GLfloat lightAmbient[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat lightDiffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lightSpecular[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    //load all image data
    stars = new TGA("images/stars.tga");
    moon = new TGA("images/moon.tga");

    TGA* sun = new TGA("images/sun.tga");
    TGA* mercury = new TGA("images/mercury.tga");
    TGA* venus = new TGA("images/venus.tga");
    TGA* earth = new TGA("images/earth.tga");
    TGA* mars = new TGA("images/mars.tga");
    TGA* jupiter = new TGA("images/jupiter.tga");
    TGA* saturn = new TGA("images/saturn.tga");
    TGA* uranus = new TGA("images/uranus.tga");
    TGA* neptune = new TGA("images/neptune.tga");
    TGA* pluto = new TGA("images/pluto.tga");

    //add all the planets with accurate data.Distance measured in km,time measured in earth days
    solarSystem.addPlanet(0, 1, 25.38f, 696000, sun->getTextureHandle());//sun
    solarSystem.addPlanet(58000000, 87.97f, 59, 2440, mercury->getTextureHandle());//mercury
    solarSystem.addPlanet(108200000, 225, 243, 6052, venus->getTextureHandle());//venus
    solarSystem.addPlanet(149600000, 365, 1, 6371, earth->getTextureHandle());//earth
    solarSystem.addPlanet(227939100, 687, 1.03f, 3397, mars->getTextureHandle());//mars
    solarSystem.addPlanet(778500000, 4332, 0.4139, 69911, jupiter->getTextureHandle()); // jupiter
    solarSystem.addPlanet(1433000000, 10759, 0.44375, 58232, saturn->getTextureHandle()); // saturn
    solarSystem.addPlanet(2877000000, 30685, 0.718056, 25362, uranus->getTextureHandle()); // uranus
    solarSystem.addPlanet(4503000000, 60188, 0.6713, 24622, neptune->getTextureHandle()); // neptune

    solarSystem.addPlanet(140638000, 365, 6.39, 8137, pluto->getTextureHandle()); // pluto

    solarSystem.addMoon(3, 7000000, 27.3, 27.3, 1738, moon->getTextureHandle()); // test moon for the earth
    
    //set up time
    time = 2.552f;
    timeSpeed = 0.1f;
    
    //reset controls 
    controls.forward = false;
    controls.backward = false;
    controls.left = false;
    controls.right = false;
    controls.yawLeft = false;
    controls.yawRight = false;

    timer(0);
}

void drawCube(void);

void display(void)
{
    //update the logic and simulation
    time += timeSpeed;
    solarSystem.calculatePositions(time);

    if (controls.forward) camera.forward();
    if (controls.backward) camera.backward();
    if (controls.left) camera.left();
    if (controls.right) camera.right();
    if (controls.yawLeft) camera.yawLeft();
    if (controls.yawRight) camera.yawRight();

    //clear the buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    //set up the perspective matrix for rendering the 3d world
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0f, (float)screenWidth / (float)screenHeight, 0.001f, 500.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //perform the camera orientation transform
    camera.transformOrientation();

    //draw the skybox
    glBindTexture(GL_TEXTURE_2D, stars->getTextureHandle());
    drawCube();
    
    //perform the camera translation transform
    camera.transformTranslation();

    GLfloat lightPosition[] = { 0.0, 0.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    //render the solar system
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);

    solarSystem.render();
    glDisable(GL_LIGHTING);

    //possibly render orbits
    if (showOrbits)
        solarSystem.renderOrbits();

    glDisable(GL_DEPTH_TEST);

    glFlush();
    glutSwapBuffers();
}
void keyDown(unsigned char key, int x, int y)
{
    //check for numerical keys
    if (key > '0' && key <= '9')
    {
        //point at the specified planet
        float vec[3];
        solarSystem.getPlanetPosition(key - '0', vec);
        camera.pointAt(vec);

        //select that planet
        planetSelectd = key - '0';
    }

    switch (key)
    {
    case'-':
        timeSpeed /= 2;
        break;
    case '=':
        timeSpeed *= 2;
        break;
    case '[':
        planetSizeScale /= 1.2;
        break;
    case ']':
        planetSizeScale *= 1.2;
        break;
    case 'o':
        showOrbits = !showOrbits;
        break;
    case'm':
        addMoon();
        break;
    case 'r':
        camera.setDefault();
        break;
    case ',':
        camera.slowDown();
        break;
    case '.':
        camera.speedUp();
        break;
    case 'w':
        controls.forward = true;
        break;
    case's':
        controls.backward = true;
        break;
    case 'a':
        controls.left = true;
        break;
    case 'd':
        controls.right=true;
        break;           
    case 'q':
        controls.yawLeft = true;
        break;
    case 'e':
        controls.yawRight = true;
        break;
    }
}

void keyUp(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        controls.forward = false;
        break;
    case's':
        controls.backward = false;
        break;
    case 'a':
        controls.left = false;
        break;
    case 'd':
        controls.right = false;
        break;
    case 'q':
        controls.yawLeft = false;
        break;
    case 'e':
        controls.yawRight = false;
        break;
    }
}

void reshape(int w, int h)
{
    screenWidth = w;
    screenHeight = h;
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 700);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();   
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyDown);
    glutKeyboardUpFunc(keyUp);
    glutMainLoop();
    return 0;
}

void drawCube(void)
{
    glBegin(GL_QUADS);
    // new face
    glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f);
    // new face
    glTexCoord2f(0.0f, 0.0f);	glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);	glVertex3f(1.0f, -1.0f, 1.0f);
    // new face
    glTexCoord2f(0.0f, 0.0f);	glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);	glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);	glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(0.0f, 1.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
    // new face
    glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, 1.0f);
    glTexCoord2f(1.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, -1.0f);
    // new face
    glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, 1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, 1.0f, 1.0f);
    // new face
    glTexCoord2f(0.0f, 0.0f);	glVertex3f(-1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 0.0f);	glVertex3f(1.0f, -1.0f, -1.0f);
    glTexCoord2f(1.0f, 1.0f);	glVertex3f(1.0f, -1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f);	glVertex3f(-1.0f, -1.0f, 1.0f);

    glEnd();
}
