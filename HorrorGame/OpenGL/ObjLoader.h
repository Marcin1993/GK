#pragma once
#include <iostream>
#include <vector>
#include <GL/freeglut.h>
#include "Point.h"
#include "Exception.h"

struct surface
{
	std::vector<Point3D<float>> vertex;
	std::vector<Point2D<float>> vertex_texture;
	std::vector<Point3D<float>> vertex_normal;
};

class ObjLoader
{
	std::vector<surface> surfaces_vector; 
	const char *path;
	void loadObjFile();
	FILE* openFile(const char *path, const char *mode);

public:
	ObjLoader(const char * path);
	~ObjLoader();

	std::vector<surface> getSurfacesVector();
	int getSurfaceVectorSize();
};

