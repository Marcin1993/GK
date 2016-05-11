#include "ObjLoader.h"


ObjLoader::ObjLoader(const char * path)
{
	this->path = path;

	try
	{
		loadObjFile();
	}
	catch (LoadingFileError e)
	{
		MessageBoxA(NULL, e.type().c_str(), "Error", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
	}
	catch (ParserError e)
	{
		MessageBoxA(NULL, e.type().c_str(), "Error", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
	}
	catch (Exception e)
	{
		MessageBoxA(NULL, "Oops, something went wrong :(\nPlease press OK and restart game", "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		exit(0);
	}
}


ObjLoader::~ObjLoader()
{
	surfaces_vector.clear();
}


void ObjLoader::loadObjFile() throw(Exception)
{
	FILE *objFile;

	if ((objFile = openFile(path, "r")) != NULL)
	{
		std::cout << "Otwieranie pliku obj" << std::endl;

		std::vector<Point3D<float>> temp_vertex;
		std::vector<Point2D<float>> temp_vertex_texture;
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
			else if (strcmp(lineHeader, "vt") == 0)
			{
				float u, v;
				fscanf(objFile, "%f %f %f\n", &u, &v);
				temp_vertex_texture.push_back(Point2D<float>(u, v));
			}
			else if (strcmp(lineHeader, "vn") == 0)
			{
				float x, y, z;
				fscanf(objFile, "%f %f %f\n", &x, &y, &z);
				temp_vertex_normal.push_back(Point3D<float>(x, y, z));
			}
			else if (strcmp(lineHeader, "f") == 0)
			{
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(objFile, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0],
					&uvIndex[0],
					&normalIndex[0],

					&vertexIndex[1],
					&uvIndex[1],
					&normalIndex[1],

					&vertexIndex[2],
					&uvIndex[2],
					&normalIndex[2]);
				if (matches != 9)
				{
					fclose(objFile);
					throw ParserError(std::string("File can't be read by this parser!\nTry input .obj file in triangle convention.\nPath of file:\n") + path);
				}

				surface *surface_temp = new surface;

				surface_temp->vertex.push_back(temp_vertex[vertexIndex[0] - 1]);
				surface_temp->vertex.push_back(temp_vertex[vertexIndex[1] - 1]);
				surface_temp->vertex.push_back(temp_vertex[vertexIndex[2] - 1]);

				surface_temp->vertex_texture.push_back(temp_vertex_texture[uvIndex[0] - 1]);
				surface_temp->vertex_texture.push_back(temp_vertex_texture[uvIndex[1] - 1]);
				surface_temp->vertex_texture.push_back(temp_vertex_texture[uvIndex[2] - 1]);

				surface_temp->vertex_normal.push_back(temp_vertex_normal[normalIndex[0] - 1]);
				surface_temp->vertex_normal.push_back(temp_vertex_normal[normalIndex[1] - 1]);
				surface_temp->vertex_normal.push_back(temp_vertex_normal[normalIndex[2] - 1]);

				surfaces_vector.push_back(*surface_temp);
				
				delete surface_temp;
			}
		}
		// Clean the temp's variables.
		temp_vertex.clear();
		temp_vertex_normal.clear();
		temp_vertex_texture.clear();

		fclose(objFile);
	}
	else
	{
		throw LoadingFileError(std::string("Can not found .obj file!\nPath of file:\n") + path);
	}
}
	

FILE* ObjLoader::openFile(const char *path, const char *mode)
{
	return fopen(path, mode);
}


std::vector<surface> ObjLoader::getSurfacesVector()
{
	return surfaces_vector;
}


int ObjLoader::getSurfaceVectorSize()
{
	return this->surfaces_vector.size();
}