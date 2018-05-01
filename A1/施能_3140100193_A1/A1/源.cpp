#include <stdio.h>
#include <assert.h>
#include <string.h>
inline int Round(const float a){ return int(a + 0.5); }
int xCenter;
int yCenter;
int Rx;
int Ry;
int temp[128][256] = { 0 };

/*
* int PPMWriteImage(const char* filePath, const unsigned char* buffer, unsigned int width, unsigned int height)
* Parameters:
*     filePath: target image file path.
*     buffer: image data buffer, RGB order, 8 bits per channel, 24 bits per pixel.
*     width: image width.
*     height: image height.
* Return:
*     1 (success), 0 (error)
*/
void ellipsePlotPoints (int xCenter,int yCenter,int x,int y)
{
    temp[yCenter + y][xCenter + x] = 1;
    temp[yCenter + y][xCenter - x] = 1;
    temp[yCenter - y][xCenter + x] = 1;
    temp[yCenter - y][xCenter - x] = 1;
}
void ellipseMidepoint(int xCenter, int yCenter, int Rx, int Ry)
{
    int Rx2 = Rx*Rx;
    int Ry2 = Ry*Ry;
    int twoRx2 = 2 * Rx2;
    int twoRy2 = 2 * Ry2;
    int p;
    int x = 0;
    int y = Ry;
    int px = 0;
    int py = twoRx2*y;

    ellipsePlotPoints(xCenter, yCenter, x, y);
    p = Round(Ry2 - (Rx2*Ry) + (0.25*Rx2));
    while (px < py)
    {
        x++;
        px += twoRy2;
        if (p < 0)
            p += Ry2 + px;
        else {
            y--;
            py -= twoRx2;
            p += Ry2 + px - py;
        }
        ellipsePlotPoints(xCenter, yCenter, x, y);
    }

    p = Round(Ry2*(x + 0.5)*(x + 0.5) + Rx2*(y - 1)*(y - 1) - Rx2 * Ry2);
    while (y > 0)
    {
        y--;
        py -= twoRx2;
        if (p>0)
            p += Rx2 - py;
        else {
            x++;
            px += twoRy2;
            p += Rx2 - py + px;
        }
        ellipsePlotPoints(xCenter, yCenter, x, y);
    }
}
static int PPMWriteImage(const char* filePath, const unsigned char* buffer, unsigned int width, unsigned int height)
{
    errno_t err;
    FILE* fp;
    unsigned int total = width * height * 3;

    assert(filePath != NULL);
    assert(buffer != NULL);

    err = fopen_s(&fp,filePath, "wb");
    if (fp == NULL)
    {
        fprintf(stderr, "Open target image file [%s] failed!\n", filePath);
        return 0;
    }

    /* Write file header */
    fprintf(fp, "P3 %u %u 255\n", width, height);

    /* Write file content */
    while (total-- > 0)
    {
        fprintf(fp, " %u", *buffer++);
    }

    fclose(fp);
    return 1;
}


int main(void)
{
    const int WIDTH = 256;
    const int HEIGHT = 128;

    const unsigned char red[3] = { 255, 0, 0 };
    unsigned char testImage[HEIGHT][WIDTH][3];
    unsigned char(*p)[3] = &testImage[0][0];
    int i, j;

    printf_s("please input center(x,y),Ra,Rb\n");
    scanf_s("%d%d%d%d", &xCenter, &yCenter, &Rx, &Ry);   
    if ((-Rx + xCenter<0) || (Rx + xCenter>WIDTH) || (-Ry + yCenter<0) || (Ry + yCenter)>HEIGHT)
    {
        printf_s("your input is not permitted");
        return 0;
    }
    
    ellipseMidepoint(xCenter, yCenter, Rx, Ry);
    for (i = 0; i < HEIGHT; i++)
    {
        for (j = 0; j < WIDTH; j++)
        {
            if (temp[i][j])
                memcpy(p++, red, sizeof(red));
            else
                p++;
        }
    }
        
    PPMWriteImage("test.ppm", &testImage[0][0][0], WIDTH, HEIGHT);
    return 0;
}
