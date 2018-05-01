#include "solarsystem.h"
#include <cmath>
SolarSystem::SolarSystem()
{

}

//calculate the positions and logic of all planets
void SolarSystem::calculatePositions(float time)
{
    for (int i = 0; i < planets.size()-1; i++)
    {
        planets[i].calculatePosition(time);
    }
    float normalVectorPluto[] = { cos(27.14), 0.0f, sin(27.14) };
    planets[planets.size() - 1].calculatePosition(time, normalVectorPluto);
}

//Add a planet with the given data
void SolarSystem::addPlanet(float distanceFromSun, float orbitTime, float rotationTime, float radius, GLuint textureHandle)
{
    planets.push_back(Planet(distanceFromSun, orbitTime, rotationTime, radius, textureHandle));
}

//add a moon to the specified planet
void SolarSystem::addMoon(int planetIndex, float distanceFromPlanet, float orbitTime, float rotationTime,float radius, GLuint textureHandle)
{
    planets[planetIndex].addMoon(distanceFromPlanet, orbitTime, rotationTime, radius, textureHandle);
}

//render the planets with opengl
void SolarSystem::render()
{
    for (int i = 0; i < planets.size(); i++)
    {
        planets[i].render();
    }
}

//render the drawing  of the orbits
void SolarSystem::renderOrbits()
{
    for (int i = 0; i < planets.size()-1; i++)
    {
        planets[i].renderOrbit();
    }
    float normalVectorPluto[] = { cos(27.14),0.0f, sin(27.14) };
    planets[planets.size() - 1].renderOrbit(normalVectorPluto);
}

//get the position in 3d space units of  the given planet(specified by its index in the list) and put it into the 3d vector vec
void SolarSystem::getPlanetPosition(int index, float* vec)
{
    planets[index].getPosition(vec);
}

//get the radius of the planet at the given index in the planets list
float SolarSystem::getRadiusOfPlanet(int index)
{
    return planets[index].getRadius();
}