#include "Animation.h"


Animation::Animation()
{
}


// Gets single frame name.
std::string Animation::getFrameName(std::string file_name, unsigned int frame_counter)
{
	std::string frame_name = file_name;
	std::string counter_string;
	std::string tmp_string;

	tmp_string = std::to_string(frame_counter);

	int j = 0;
	for (int i = 0; i < 6; ++i)
	{
		if (i < (6 - tmp_string.size()))
		{
			counter_string += "0";
		}
		else
		{
			counter_string += tmp_string[j];
			++j;
		}
	}

	return (frame_name + "_" + counter_string + ".obj");
}


// Converts single temporary frame form vector to struct animatinFrame.
float** Animation::convertFrame()
{
	int frame_face_count = temporary_surfaces_vector.size();
	frame_vertex_info = new float*[frame_face_count];

	for (int i = 0; i < frame_face_count; ++ i)
	{
		frame_vertex_info[i] = new float[18];

		/* Fill vertex 0-2 first, 3-5 second, 6-8 third */
		frame_vertex_info[i][0] = temporary_surfaces_vector[i].animation_vertex[0].getX();
		frame_vertex_info[i][1] = temporary_surfaces_vector[i].animation_vertex[0].getY();
		frame_vertex_info[i][2] = temporary_surfaces_vector[i].animation_vertex[0].getZ();
		frame_vertex_info[i][3] = temporary_surfaces_vector[i].animation_vertex[1].getX();
		frame_vertex_info[i][4] = temporary_surfaces_vector[i].animation_vertex[1].getY();
		frame_vertex_info[i][5] = temporary_surfaces_vector[i].animation_vertex[1].getZ();
		frame_vertex_info[i][6] = temporary_surfaces_vector[i].animation_vertex[2].getX();
		frame_vertex_info[i][7] = temporary_surfaces_vector[i].animation_vertex[2].getY();
		frame_vertex_info[i][8] = temporary_surfaces_vector[i].animation_vertex[2].getZ();

		/* Fill vertex normal 9-11 first, 12-14 second, 15-17 third */
		frame_vertex_info[i][9] = temporary_surfaces_vector[i].animation_vertex_normal[0].getX();
		frame_vertex_info[i][10] = temporary_surfaces_vector[i].animation_vertex_normal[0].getY();
		frame_vertex_info[i][11] = temporary_surfaces_vector[i].animation_vertex_normal[0].getZ();
		frame_vertex_info[i][12] = temporary_surfaces_vector[i].animation_vertex_normal[1].getX();
		frame_vertex_info[i][13] = temporary_surfaces_vector[i].animation_vertex_normal[1].getY();
		frame_vertex_info[i][14] = temporary_surfaces_vector[i].animation_vertex_normal[1].getZ();
		frame_vertex_info[i][15] = temporary_surfaces_vector[i].animation_vertex_normal[2].getX();
		frame_vertex_info[i][16] = temporary_surfaces_vector[i].animation_vertex_normal[2].getY();
		frame_vertex_info[i][17] = temporary_surfaces_vector[i].animation_vertex_normal[2].getZ();
	}

	return frame_vertex_info;
}


// Loading single .obj
int Animation::loadObjFile(const char *path)
{
	FILE *objFile;

	if ((objFile = openFile(path, "r")) != NULL)
	{
		std::cout << "Otwieranie pliku obj: " << path << std::endl;

		std::vector<Point3D<float>> temp_vertex;
		std::vector<Point3D<float>> temp_vertex_normal;

		while (1)
		{
			char lineHeader[128];
			// Read the first word of the line.
			int res = fscanf(objFile, "%s", lineHeader);

			// End Of File. Quit the loop.
			if (res == EOF)
				break;

			// else : parse lineHeader
			if (strcmp(lineHeader, "v") == 0)
			{
				float x, y, z;
				fscanf(objFile, "%f %f %f\n", &x, &y, &z);
				temp_vertex.push_back(Point3D<float>(x, y, z));
			}
			/*
			else if (strcmp(lineHeader, "vt") == 0)
			{
				float u, v;
				fscanf(objFile, "%f %f %f\n", &u, &v);
				temp_vertex_texture.push_back(Point2D<float>(u, v));
			}
			*/
			else if (strcmp(lineHeader, "vn") == 0)
			{
				float x, y, z;
				fscanf(objFile, "%f %f %f\n", &x, &y, &z);
				temp_vertex_normal.push_back(Point3D<float>(x, y, z));
			}
			else if (strcmp(lineHeader, "f") == 0)
			{
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(objFile, "%d//%d %d//%d %d//%d\n", &vertexIndex[0],
																			  //&uvIndex[0],
																		   	  &normalIndex[0],

																			  &vertexIndex[1],
																			  //&uvIndex[1],
																			  &normalIndex[1],

																			  &vertexIndex[2],
																			  //&uvIndex[2],
																			  &normalIndex[2]);
				if (matches != 6)
				{
					throw Exception("File can't be read by this parser! Try input .obj file in triangle convention.\n");
				}
				frameSurface *surface_temp = new frameSurface;

				surface_temp->animation_vertex.push_back(temp_vertex[vertexIndex[0] - 1]);
				surface_temp->animation_vertex.push_back(temp_vertex[vertexIndex[1] - 1]);
				surface_temp->animation_vertex.push_back(temp_vertex[vertexIndex[2] - 1]);

				/*
				surface_temp->animation_vertex_texture.push_back(temp_vertex_texture[uvIndex[0] - 1]);
				surface_temp->animation_vertex_texture.push_back(temp_vertex_texture[uvIndex[1] - 1]);
				surface_temp->animation_vertex_texture.push_back(temp_vertex_texture[uvIndex[2] - 1]);
				*/

				surface_temp->animation_vertex_normal.push_back(temp_vertex_normal[normalIndex[0] - 1]);
				surface_temp->animation_vertex_normal.push_back(temp_vertex_normal[normalIndex[1] - 1]);
				surface_temp->animation_vertex_normal.push_back(temp_vertex_normal[normalIndex[2] - 1]);

				temporary_surfaces_vector.push_back(*surface_temp);

				delete surface_temp;			
			}
		}

		// Clean the temp's variables.
		temp_vertex.clear();
		temp_vertex_normal.clear();
		//temp_vertex_texture.clear();

		fclose(objFile);
		return 1;
	}
	else
	{
		// Can not found .obj file!
		return 0;
	}
}

// Loading a whole animation.
void Animation::loadAnimation(const char *single_file_name)
{
	//std::vector<surface> surfaces_vector;
	unsigned int frame_counter = 1;
	std::string tmp_frame_name = getFrameName(single_file_name, frame_counter);
	std::cout << tmp_frame_name << std::endl;

	const char *frame_name = tmp_frame_name.c_str();
 
	while (loadObjFile(frame_name))
	{
		temporary_animation.push_back(convertFrame());

		++frame_counter;
		tmp_frame_name = getFrameName(single_file_name, frame_counter);
		frame_name = tmp_frame_name.c_str();

		temporary_surfaces_vector.clear();
	}

	frame_count = frame_counter;
	animation_vertex_info = new float**[frame_count];
	for (int i = 0; i < (frame_counter - 1); ++ i)
	{
		animation_vertex_info[i] = temporary_animation[i];
	}
}


FILE* Animation::openFile(const char *path, const char *mode)
{
	return fopen(path, mode);
}


int Animation::getFrameCount()
{
	return frame_count;
}


float*** Animation::getSingleAnimation()
{
	return animation_vertex_info;
}