#pragma once

#include <iostream>
#include <vector>
#include "Point.h"
#include "Exception.h"


struct frameSurface
{
	std::vector<Point3D<float>> animation_vertex;
	std::vector<Point3D<float>> animation_vertex_normal;
};


class Animation
{
private:
	float **frame_vertex_info;

	int frame_count;
	float ***animation_vertex_info;
	//std::vector<animationFrame> temporary_animation;
	std::vector<float**> temporary_animation;
	std::vector<frameSurface> temporary_surfaces_vector;

	//singleAnimation animations;

	std::string getFrameName(std::string file_name, unsigned int frame_counter);
	int loadObjFile(const char *path);
	//animationFrame* convertFrame();
	float** convertFrame();

	Animation* getAnimation();
public:
	Animation();
	
	void loadAnimation(const char *single_file_name);
	FILE* openFile(const char *path, const char *mode);
	
	int getFrameCount();
	float*** getSingleAnimation();
};