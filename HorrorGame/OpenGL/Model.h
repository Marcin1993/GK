#pragma once
#include <iostream>
#include <vector>
#include <GL/freeglut.h>

#include "IDrawable.h"
#include "ITransformable.h"
#include "Exception.h"
#include "Point.h"
#include "ObjLoader.h"
#include "Texture.h"

#define MAX_NUMBER_OF_TEXTURES 100

struct BoundingBox
{
	Point3D<float> min;
	Point3D<float> max;
};

class Model : public IDrawable, public ITransfomable
{
private:
	float positionX, positionY, positionZ;

	float **vertex_info;
	std::vector<surface> temp_surfaces_vector;
	int surfaces_number;	
	Texture *texture;

	int modelID;
	static int numberOfTextures;
	static GLuint textureID[MAX_NUMBER_OF_TEXTURES];
	
	bool collisionEnable;
	BoundingBox boundingBox;

	//float ***animation;
	float ****animation;
	unsigned int animationCount;
	unsigned int frame_number;
	int really_frame_number;
	
	void loadModel();
	void loadTexture();
	void loadAnimation();
	void setMaterial();

public:
	unsigned int *frame_count;

	Model();
	Model(const char * objPath, const char * texPath, bool collisionEnable);
	~Model();
	virtual void draw();
	virtual void translate(float x, float y, float z);

	float getPositionX();
	float getPositionY();
	float getPositionZ();

	void translate(float x, float y, float z, int animation_id);
	void jbTranslate(float inputX, float inputY, float inputZ);
	void drawWithAni(int animation_id);
	void translateWithAni(float x, float y, float z);

	void setAnimationCount(int animation_count);
	void setAnimation(int animation_id, int input_frame_count, float ***input_animation);
	void setFrameNumber(unsigned int current_frame);
	void setReallyFrameNumber(int number);

	bool getCollisionStatus();
	BoundingBox getBoundingBox();
	void refreshBoundingBox();

	static int getIncNumberOfTextures() { return numberOfTextures++; }
	static GLuint* getTextureIDArray() { return textureID; }
};
