#pragma once

#include<string>

class Shader
{
private:
	int id;
	int type;
	const char * program;

public:
	Shader();
	~Shader();

	bool loadShader(std::string file, int type);
	int getID();
	void deleteShader();

};

