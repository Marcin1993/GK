#pragma once
#include <iostream>
#include <string>
#include <Windows.h>

class Exception
{
protected:
	std::string error_type;
public:
	Exception(std::string err) : error_type(err) { }
	std::string type()
	{
		return error_type;
	}
};

class LoadingFileError : public Exception
{
public:
	LoadingFileError(std::string err) : Exception(err) { }
};

class ParserError : public Exception
{
public:
	ParserError(std::string err) : Exception(err) { }
};

class InitFmodError : public Exception
{
public:
	InitFmodError(std::string err) : Exception(err) { }
};

class SoundError : public Exception
{
public:
	SoundError(std::string err) : Exception(err) { }
};