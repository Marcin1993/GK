#include "Shader.h"
#include "ShaderProgram.h"
#include <GL/glew.h>

ShaderProgram::ShaderProgram()
{

}

ShaderProgram::~ShaderProgram()
{
	deleteProgram();
}

void ShaderProgram::createProgram()
{
	id = glCreateProgram();
}

void ShaderProgram::deleteProgram()
{
	glDeleteProgram(id);
}

int ShaderProgram::getID()
{
	return id;
}

bool ShaderProgram::addShader(Shader* shader)
{
	glAttachShader(id, shader->getID());
	return true;
}

bool ShaderProgram::linkProgram()
{
	glLinkProgram(id);

	int linkStatus;

	glGetProgramiv(id, GL_LINK_STATUS, &linkStatus);
	if (linkStatus == GL_FALSE){
		int maxLength;
		int length;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);
		char* log = new char[maxLength];
		glGetProgramInfoLog(id, maxLength, &length, log);
		return false;
	}
	else return true;
}

void ShaderProgram::useProgram()
{
	glUseProgram(id);
}