#ifndef SN_PLANET_H
#define SN_PLANET_H

#include <gl\freeglut.h>
#include <vector>
#include "moon.h"

class Planet
{
private:
    //distance from the sun
    float distanceFromSun;

    //time it takes to complete 1 orbit 
    float orbitTime;

    //time it takes to spin 360 degrees
    float rotationTime;

    //radius of the planet itself 
    float radius;

    //the texture used for rendering
    GLuint textureHandle;

    //its position in 3d space
    float position[3];

    //its rotation around its axis
    float rotation;

    //list of moons attached to this planet
    std::vector<Moon> moons;

public:
    //distance is in units of km and time is in units of earth days
    Planet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle);

    //calculate its position in 3d space in the orbit using the given time value
    void calculatePosition(float time);

    //Calculate its position in 3d space in the orbit using the given time value and angle value £¨ÓÐÇã½Ç£©
    void Planet::calculatePosition(float time, float* vec);

    //Render it to the screen
    void render(void);

    //render this planet's orbit circle
    void renderOrbit(void);

    //render this pluto orbit circle
    void Planet::renderOrbit(float* vec);

    //Get its position in 3d world space units(after scaling) and put it into the 3d vector
    void getPosition(float* vec);

    //get the radius of the planet
    float getRadius(void);

    //add a moon to this planet
    void addMoon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius, GLuint textureHandle);
};
#endif

