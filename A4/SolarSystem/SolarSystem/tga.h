#ifndef SN_TGA_H
#define SN_TGA_H

#include <gl\freeglut.h>

//This is a clas that load TGA files into opengl textures
class TGA
{
private:
    //the handle for the texture in opengl
    GLuint textureHandle;
public:
    //Constructs and loads a TGA into opengl from the given image file path
    TGA(char* imagePath);

        //Returns the handle to the texture created from the image,for binding to opengl
        GLuint getTextureHandle(void);
};

#endif