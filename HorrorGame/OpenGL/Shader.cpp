#include "Shader.h"
#include <GL/glew.h>
#include <GL/wglew.h>
#include <string>
#include <vector>

Shader::Shader()
{
}

Shader::~Shader()
{
	deleteShader();
}

bool Shader::loadShader(std::string dir, int type)
{
	std::string source;
	FILE *file = fopen(dir.c_str(), "rb");

	if (!file)
	{
		return false;
	}

	char* line = new char[255];

	while (fgets(line, 255, file)){
		source.append(line);
		source.append(" ");
	}

	program = new const char [source.size()];
	program = source.c_str();

	id = glCreateShader(type);

	glShaderSource(id, 1, &program , NULL);
	glCompileShader(id);

	int iCompilationStatus;
	glGetShaderiv(id, GL_COMPILE_STATUS, &iCompilationStatus);

	if (iCompilationStatus == GL_FALSE)
	{
		int maxLength;
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
		char* log = new char[maxLength];
		glGetShaderInfoLog(id, maxLength, &length, log);
		return false;
	}
	this->type = type;
	return true;
}

int Shader::getID()
{
	return id;
}

void Shader::deleteShader()
{
	glDeleteShader(id);
	delete[] program;
}
