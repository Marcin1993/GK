#pragma once

class ITransfomable
{
public:
	virtual ~ITransfomable() {};
	//virtual void rotate(float angle, float x, float y, float z) = 0;
	//virtual void scale(float x, float y, float z) = 0;
	virtual void translate(float x, float y, float z) = 0;
};