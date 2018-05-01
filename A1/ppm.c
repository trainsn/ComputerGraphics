/* ppm.c */

#include <stdio.h>
#include <assert.h>
#include <string.h>

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

static int PPMWriteImage(const char* filePath, const unsigned char* buffer, unsigned int width, unsigned int height)
{
	FILE* fp;
	unsigned int total = width * height * 3;

	assert(filePath != NULL);
	assert(buffer != NULL);

	fp = fopen(filePath, "wb");
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
	unsigned int i = WIDTH * HEIGHT;
	unsigned char (*p)[3] = &testImage[0][0];

	/* color the testImage red */
	while (i-- > 0)
	{
		memcpy(p++, red, sizeof(red));
	}

	PPMWriteImage("test.ppm", &testImage[0][0][0], WIDTH, HEIGHT);
	return 0;
}
