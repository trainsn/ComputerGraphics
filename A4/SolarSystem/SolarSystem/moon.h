#ifndef SN_MOON_H
#define SN_MOON_H

#include <gl\freeglut.h>

class Moon
{
private:
    //distance from its planet; 
    float distanceFromPlanet;

    //time it takes to complete 1 orbit 
    float orbitTime;

    //time it takes to spin 360 degrees 
    float rotationTime;

    //radius of the moon itself
    float radius;

    //the texture used for rendering 
    GLuint textureHandle;

    //its position in 3d space relative to the planet
    float position[3];
    //its rotation around its axis
    float rotation;

public:
    //Distance is in units of km and time is in units of earth days
    Moon(float distanceFromPlanet, float orbitTime, float rotationTime, float radius,GLuint textureHandle);

    //Calculate its position in 3d space relative to the planet in the orbit using the given time value 
    void calculatePosition(float time);

    //Rendering it the the screen
    void render(void);

    //Rendering this moons orbit circle 
    void renderOrbit(void);
};
#endif