#pragma once
#include <iostream>
#include <GL/freeglut.h>
#include "Exception.h"

// Struct of bitmap file.
struct BitMapFile
{
	int width;
	int height;
	unsigned char *data;
};

class Texture
{
private:
	const char *path;

	// Data read from the header of the BMP file 
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageSize;

	FILE* openFile(const char *path, const char *mode);

public:
	Texture(const char *path);
	~Texture();

	BitMapFile* getBitmapData();
};