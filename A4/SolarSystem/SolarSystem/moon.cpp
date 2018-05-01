#define FREEGLUT_STATIC
#pragma comment(lib,"freeglut_staticd.lib")
#include "moon.h"
#include <cmath>

#include <gl\freeglut.h>
#include "globals.h"

Moon::Moon(float distanceFromPlanet, float orbitTime, float rotationTime,float radius, GLuint textureHandle)
{
    this->distanceFromPlanet = distanceFromPlanet;
    this->orbitTime = orbitTime;
    this->rotationTime = rotationTime;
    this->radius = radius;
    this->textureHandle = textureHandle;
}

//Calculate its position in 3d space relative to the planet in the orbit using the given time value
void Moon::calculatePosition(float time)
{
    //find the angle of orientation of the orbit around the planet
    float angle = time*3.1415926f / orbitTime;

    //use trig to find the position in space relative to the planet
    position[0] = sin(angle)*distanceFromPlanet;
    position[1] = cos(angle)*distanceFromPlanet;
    position[2] = 0;

    //find the rotation of the moon around its axis
    rotation = time * 360 / rotationTime;
}

//Render it to the screen
void Moon::render(void)
{
    glPushMatrix();

    //bind the moons texture
    glBindTexture(GL_TEXTURE_2D, textureHandle);

    //translate to the right position and rotate for the moons spinning
    glTranslatef(position[0] * distanceScale, position[1] * distanceScale, position[2] * distanceScale);
    glRotatef(-rotation, 0.0f, 0.0f, 1.0f);
    
    //render as a GLU sphere quadric object 
    GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, true);
    gluQuadricNormals(quadric, GLU_SMOOTH);

    gluSphere(quadric, radius*planetSizeScale, 30, 30);

    glPopMatrix();
}

//render this planets orbit circle
void Moon::renderOrbit(void)
{
    //draw a line strip
    glBegin(GL_LINE_STRIP);

    //load round from 0 to 2pi and draw around the radius of the orbit using trig
    for (float angle = 0.0f; angle < 3.1415926 * 2; angle += 0.1f)
    {
        glVertex3f(sin(angle)*distanceFromPlanet*distanceScale, cos(angle)*distanceFromPlanet*distanceScale, 0.0f);
    }
    glVertex3f(0.0f, distanceFromPlanet*distanceScale, 0.0f);
    
    glEnd();
}