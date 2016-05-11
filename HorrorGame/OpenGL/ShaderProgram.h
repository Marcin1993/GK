#pragma once

#include "Shader.h"
#include <GL/glew.h>
#include <string>

using namespace std;

class ShaderProgram
{
private:
	int id; 
public:
	ShaderProgram();
	~ShaderProgram();

	void createProgram();
	void deleteProgram();

	bool addShader(Shader* shader);
	bool linkProgram();

	void useProgram();

	int getID();

};