#define  FREEGLUT_STATIC
#pragma comment(lib,"freeglut_staticd.lib")
#include "planet.h"
#include <cmath>

#include <gl\freeglut.h>
#include "globals.h"

float planetSizeScale = 0.000005f;
//sets vec to (x,y,z)
void vectorSet1(float* vec, float x, float y, float z)
{
    vec[0] = x;
    vec[1] = y;
    vec[2] = z;
}

//adds v2 to v1
void vectorAdd1(float* v1, float* v2)
{
    v1[0] += v2[0];
    v1[1] += v2[1];
    v1[2] += v2[2];
}

//multiplies vec by the scalar
void vectorMul1(float* vec, float scalar)
{
    vec[0] *= scalar;
    vec[1] *= scalar;
    vec[2] *= scalar;
}

//finds the magnitude of a vec 
float lengthOfVec1(float *vec)
{
    return sqrtf(vec[0] * vec[0] + vec[1] * vec[1] + vec[2] * vec[2]);
}

//normalizes a vector to maginitude 1
void normalizeVec1(float* vec)
{
    vectorMul1(vec, 1 / lengthOfVec1(vec));
}

Planet::Planet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
    this->distanceFromSun = distanceFromSun;
    this->orbitTime = orbitTime;
    this->rotationTime = rotationTime;
    this->radius = radius;
    this->textureHandle = textureHandle;

}

//Calculate its position in 3d space in the orbit using the given time value
void Planet::calculatePosition(float time)
{
    //find the angle of orientation of the orbit around the sun
    float angle = time*3.1415926f / orbitTime;

    //use trig to find the position in space
    position[0] = sin(angle)*distanceFromSun;
    position[1] = cos(angle)*distanceFromSun;
    position[2] = 0;

    //find the rotation of the planet around the axis
    rotation = time * 360 / rotationTime;

    //calculate positions of the planet around its axis
    for (int i = 0; i < moons.size(); i++)
    {
        moons[i].calculatePosition(time);
    }
}

//Calculate its position in 3d space in the orbit using the given time value and angle value £¨ÓÐÇã½Ç£©
void Planet::calculatePosition(float time,float* vec)
{
    //find the angle of orientation of the orbit around the sun
    float angle = time*3.1415926f / orbitTime;

    float u[] = { vec[1], -vec[0], 0 };
    normalizeVec1(u);
    float v[] = { vec[0] * vec[2], vec[1] * vec[2], -vec[0] * vec[0] - vec[1] * vec[1] };
    normalizeVec1(v);
    
    //use trig to find the position in space
    position[0] = (u[0] * cos(angle) + v[0] * sin(angle))*distanceFromSun;
    position[1] = (u[1] * cos(angle) + v[1] * sin(angle))*distanceFromSun;
    position[2] = (u[2] * cos(angle) + v[2] * sin(angle))*distanceFromSun;

    //find the rotation of the planet around the axis
    rotation = time * 360 / rotationTime;

    //calculate positions of the planet around its axis
    for (int i = 0; i < moons.size(); i++)
    {
        moons[i].calculatePosition(time);
    }
}

//Render it to the screen
void Planet::render(void)
{
    glPushMatrix();

    //translate to the right position
    glTranslatef(position[0] * distanceScale, position[1] * distanceScale, position[2] * distanceScale);

    //draw the moons 
    for (int i = 0; i < moons.size(); i++)
        moons[i].render();
    //rotate for the planet's spin
    glRotatef(rotation, 0.0f, 0.0f, 1.0f);

    //bing the planets texture
    glBindTexture(GL_TEXTURE_2D, textureHandle);

    //render as a GLU sphere quadrict object 
    GLUquadricObj* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, true);
    gluQuadricNormals(quadric, GLU_SMOOTH);

    if (distanceFromSun< 0.001f)//if this is the sun,don't render it too big and disable lighting 
    {
        float radiusScaled = radius*planetSizeScale;
        if (radiusScaled > 0.5f)
            radiusScaled = 0.5f;
        glDisable(GL_LIGHTING);
        gluSphere(quadric, radiusScaled, 30, 30);
        glEnable(GL_LIGHTING);
    }
    else
    {
        gluSphere(quadric, radius*planetSizeScale, 30, 30);
    }
    glPopMatrix();
} 

//render this planet orbit circle
void Planet::renderOrbit(void)
{
    //draw a line strip
    glBegin(GL_LINE_STRIP);

    //loop round from 0 to 2*pi and draw around the radius of the orbit using trig
    for (float angle = 0.0f; angle < 2 * 3.1415926f; angle += 0.05f)
    {
        glVertex3f(sin(angle)*distanceFromSun*distanceScale, cos(angle)*distanceFromSun*distanceScale, 0.0f);
    }
    glVertex3f(0.0f, distanceFromSun*distanceScale,0.0f);
    glEnd();

    //render the moon's orbit
    glPushMatrix();
    //translate to the center of this planet to draw the moon orbit around it 
    glTranslatef(position[0] * distanceScale, position[1] * distanceScale, position[2] * distanceScale);
    //draw all moon orbits
    for (int i = 0; i < moons.size(); i++)
    {
        moons[i].renderOrbit();
    }
    glPopMatrix();
}

//render this pluto orbit circle
void Planet::renderOrbit(float* vec)
{
    float posx, posy, posz;

    float u[] = { vec[1], -vec[0], 0 };
    normalizeVec1(u);
    float v[] = { vec[0] * vec[2], vec[1] * vec[2], -vec[0] * vec[0] - vec[1] * vec[1] };
    normalizeVec1(v);

    //draw a line strip
    glBegin(GL_LINE_STRIP);

    //loop round from 0 to 2*pi and draw around the radius of the orbit using trig
    for (float angle = 0.0f; angle < 2 * 3.1415926f; angle += 0.05f)
    {
        posx = (u[0] * cos(angle) + v[0] * sin(angle))*distanceFromSun*distanceScale;
        posy = (u[1] * cos(angle) + v[1] * sin(angle))*distanceFromSun*distanceScale;
        posz = (u[2] * cos(angle) + v[2] * sin(angle))*distanceFromSun*distanceScale;
//          posx = (u[0] * cos(angle) + v[0] * sin(angle));
//                  posy = (u[1] * cos(angle) + v[1] * sin(angle));
//                  posz = (u[2] * cos(angle) + v[2] * sin(angle));
        glVertex3f(posx,posy,posz);
    }
    posx = u[0]*distanceFromSun*distanceScale;
    posy = u[1]*distanceFromSun*distanceScale;
    posz = u[2]*distanceFromSun*distanceScale;
//     posx = u[0];
//     posy = u[1];
//     posz = u[2];
    glVertex3f(posx,posy,posz);
    glEnd();

    //render the moon's orbit
    glPushMatrix();
    //translate to the center of this planet to draw the moon orbit around it 
    glTranslatef(position[0] * distanceScale, position[1] * distanceScale, position[2] * distanceScale);
    //draw all moon orbits
    for (int i = 0; i < moons.size(); i++)
    {
        moons[i].renderOrbit();
    }
    glPopMatrix();
}

//get its position in 3d world space units(after scaling) and put it in the 3d vector
void Planet::getPosition(float* vec)
{
    vec[0] = position[0] * distanceScale;
    vec[1] = position[1] * distanceScale;
    vec[2] = position[2] * distanceScale;
}

//get the radius of this planet
float Planet::getRadius(void)
{
    return radius;
}

//add a moon to this planet
void Planet::addMoon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
    moons.push_back(Moon(distanceFromPlanet, orbitTime, rotationTime, radius, textureHandle));
}