#include "Texture.h"


Texture::Texture(const char *path)
{
	this->path = path;
}


Texture::~Texture()
{
	delete path;
	std::cout << "Destruktor tekstury" << std::endl;
}


BitMapFile* Texture::getBitmapData() throw(Exception)
{
	BitMapFile *bmp = new BitMapFile;

	FILE * texFile;
	if ((texFile = openFile(path, "r")) != NULL)
	{
		std::cout << "Otwieranie pliku z tekstura" << std::endl;
	}
	else
	{
		throw LoadingFileError(std::string("Can not found .bmp file!\nPath of file:\n") + path);
	}

	if (fread(header, 1, 54, texFile) != 54)
	{ // If not 54 bytes read : problem
		fclose(texFile);
		throw ParserError(std::string("Not a correct BMP file!\nPath of file:\n") + path);
	}
	if (header[0] != 'B' || header[1] != 'M')
	{
		fclose(texFile);
		throw ParserError(std::string("Not a correct BMP file!\nPath of file:\n") + path);
	}
	// Read ints from the byte array
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	bmp->width = *(int*)&(header[0x12]);
	bmp->height = *(int*)&(header[0x16]);

	// Some BMP files are misformatted, guess missing information
	if (imageSize == 0)
		imageSize = bmp->width * bmp->height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)
		dataPos = 54; // The BMP header is done that way

	// Create a buffer
	// Actual RGB data
	bmp->data = new unsigned char[imageSize];

	// Read the actual data from the file into the buffer
	fread(bmp->data, 1, imageSize, texFile);

	//Everything is in memory now, the file can be closed
	fclose(texFile);
	std::cout << "Zamykanie pliku z tekstura" << std::endl;

	return bmp;
}


FILE* Texture::openFile(const char *path, const char *mode)
{
	return fopen(path, mode);
}