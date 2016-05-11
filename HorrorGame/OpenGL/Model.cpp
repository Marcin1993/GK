#include "Model.h"


int Model::numberOfTextures = 0;
GLuint Model::textureID[MAX_NUMBER_OF_TEXTURES];


Model::Model()
{
}


Model::Model(const char * objPath, const char * texPath, bool collisionEnable)
{
	ObjLoader *objLoader = new ObjLoader(objPath);
	temp_surfaces_vector = objLoader->getSurfacesVector();
	surfaces_number = objLoader->getSurfaceVectorSize();  // load vector size for better performance 
	delete objLoader;

	texture = new Texture(texPath);
	this->modelID = numberOfTextures++;

	this->collisionEnable = collisionEnable;

	try
	{
		loadModel();
	}
	catch (Exception e)
	{
		MessageBoxA(NULL, "Oops, something went wrong :(\nPlease press OK and restart game", "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		exit(0);
	}

		//winno byc ok
		this->positionX = 0;
		this->positionY = 0;
		this->positionZ = 0;

		this->frame_number = 0; 
		float ****temp = new float***[1];
		temp[0] = new float**[1];
		temp[0][0] = this->vertex_info;
		this->animation = temp;

	try
	{
		loadTexture();
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


Model::~Model()
{
	// delete vertex_info
	for (int i = 0; i < surfaces_number; i++)
		delete[] vertex_info[i];

	delete[] vertex_info;
}


void Model::loadModel()
{
	vertex_info = new float* [surfaces_number];

	// set temporary min and max before initializing vertex_info
	if (collisionEnable)
	{
		boundingBox.min.setX(temp_surfaces_vector[0].vertex[0].getX());
		boundingBox.min.setZ(temp_surfaces_vector[0].vertex[0].getZ());
		boundingBox.max.setX(temp_surfaces_vector[1].vertex[0].getX());
		boundingBox.max.setZ(temp_surfaces_vector[1].vertex[0].getZ());
	}

	for (int i = 0; i < surfaces_number; ++i)
	{
		vertex_info[i] = new float[24];

		/* Fill vertex 0-2 first, 3-5 second, 6-8 third */
		vertex_info[i][0] = temp_surfaces_vector[i].vertex[0].getX();
		vertex_info[i][1] = temp_surfaces_vector[i].vertex[0].getY();
		vertex_info[i][2] = temp_surfaces_vector[i].vertex[0].getZ();
		vertex_info[i][3] = temp_surfaces_vector[i].vertex[1].getX();
		vertex_info[i][4] = temp_surfaces_vector[i].vertex[1].getY();
		vertex_info[i][5] = temp_surfaces_vector[i].vertex[1].getZ();
		vertex_info[i][6] = temp_surfaces_vector[i].vertex[2].getX();
		vertex_info[i][7] = temp_surfaces_vector[i].vertex[2].getY();
		vertex_info[i][8] = temp_surfaces_vector[i].vertex[2].getZ();

		/* Fill vertex texture 9-10 first, 11-12 second, 13-14 third */
		vertex_info[i][9] = temp_surfaces_vector[i].vertex_texture[0].getX();
		vertex_info[i][10] = temp_surfaces_vector[i].vertex_texture[0].getY();
		vertex_info[i][11] = temp_surfaces_vector[i].vertex_texture[1].getX();
		vertex_info[i][12] = temp_surfaces_vector[i].vertex_texture[1].getY();
		vertex_info[i][13] = temp_surfaces_vector[i].vertex_texture[2].getX();
		vertex_info[i][14] = temp_surfaces_vector[i].vertex_texture[2].getY();

		/* Fill vertex normal 15-17 first, 18-20 second, 21-23 third */
		vertex_info[i][15] = temp_surfaces_vector[i].vertex_normal[0].getX();
		vertex_info[i][16] = temp_surfaces_vector[i].vertex_normal[0].getY();
		vertex_info[i][17] = temp_surfaces_vector[i].vertex_normal[0].getZ();
		vertex_info[i][18] = temp_surfaces_vector[i].vertex_normal[1].getX();
		vertex_info[i][19] = temp_surfaces_vector[i].vertex_normal[1].getY();
		vertex_info[i][20] = temp_surfaces_vector[i].vertex_normal[1].getZ();
		vertex_info[i][21] = temp_surfaces_vector[i].vertex_normal[2].getX();
		vertex_info[i][22] = temp_surfaces_vector[i].vertex_normal[2].getY();
		vertex_info[i][23] = temp_surfaces_vector[i].vertex_normal[2].getZ();

		// searching min and max for bounding box
		if (collisionEnable)
		{
			// min for x
			if (boundingBox.min.getX() > vertex_info[i][0])
				boundingBox.min.setX(vertex_info[i][0]);
			if (boundingBox.min.getX() > vertex_info[i][3])
				boundingBox.min.setX(vertex_info[i][3]);
			if (boundingBox.min.getX() > vertex_info[i][6])
				boundingBox.min.setX(vertex_info[i][6]);

			// min for z
			if (boundingBox.min.getZ() > vertex_info[i][2])
				boundingBox.min.setZ(vertex_info[i][2]);
			if (boundingBox.min.getZ() > vertex_info[i][5])
				boundingBox.min.setZ(vertex_info[i][5]);
			if (boundingBox.min.getZ() > vertex_info[i][8])
				boundingBox.min.setZ(vertex_info[i][8]);

			// max for x
			if (boundingBox.max.getX() < vertex_info[i][0])
				boundingBox.max.setX(vertex_info[i][0]);
			if (boundingBox.max.getX() < vertex_info[i][3])
				boundingBox.max.setX(vertex_info[i][3]);
			if (boundingBox.max.getX() < vertex_info[i][6])
				boundingBox.max.setX(vertex_info[i][6]);

			// max for z
			if (boundingBox.max.getZ() < vertex_info[i][2])
				boundingBox.max.setZ(vertex_info[i][2]);
			if (boundingBox.max.getZ() < vertex_info[i][5])
				boundingBox.max.setZ(vertex_info[i][5]);
			if (boundingBox.max.getZ() < vertex_info[i][8])
				boundingBox.max.setZ(vertex_info[i][8]);
		}
	}

	// Clean the temp's variables.
	temp_surfaces_vector.clear();
}


void Model::loadTexture()
{
	// Local storage for bmp image data.
	BitMapFile *image[1];

	// Load the texture.
	image[0] = texture->getBitmapData();
	
	// Activate texture index textureID 
	glGenTextures(1, &textureID[this->modelID]);
	glBindTexture(GL_TEXTURE_2D, textureID[this->modelID]); 
	glEnable(GL_COLOR_MATERIAL);

	// Set texture parameters for wrapping.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture parameters for filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Set texture mode
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// Specify an image as the texture to be bound with the currently active texture index.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image[0]->width, image[0]->height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, image[0]->data);
}


void Model::draw()
{
	setMaterial();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID[this->modelID]);

	for (int i = 0; i < surfaces_number; ++i)
	{
		glBegin(GL_TRIANGLES);
			glTexCoord2f(vertex_info[i][9], vertex_info[i][10]);
			glNormal3f(vertex_info[i][15], vertex_info[i][16], vertex_info[i][17]);
			glVertex3f(vertex_info[i][0], vertex_info[i][1], vertex_info[i][2]);

			glTexCoord2f(vertex_info[i][11], vertex_info[i][12]);
			glNormal3f(vertex_info[i][18], vertex_info[i][19], vertex_info[i][20]);
			glVertex3f(vertex_info[i][3], vertex_info[i][4], vertex_info[i][5]);

			glTexCoord2f(vertex_info[i][13], vertex_info[i][14]);
			glNormal3f(vertex_info[i][21], vertex_info[i][22], vertex_info[i][23]);
			glVertex3f(vertex_info[i][6], vertex_info[i][7], vertex_info[i][8]);
		glEnd();	
	} 

	glDisable(GL_TEXTURE_2D);
}


void Model::drawWithAni(int animation_id)
{
	setMaterial();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureID[this->modelID]);

	for (int i = 0; i < surfaces_number; ++i)
	{
		glBegin(GL_TRIANGLES);
			glNormal3f(vertex_info[i][15], vertex_info[i][16], vertex_info[i][17]);
			glTexCoord2f(vertex_info[i][9], vertex_info[i][10]);
			glVertex3f(animation[animation_id][frame_number][i][0], animation[animation_id][frame_number][i][1], animation[animation_id][frame_number][i][2]);
			glTexCoord2f(vertex_info[i][11], vertex_info[i][12]);
			glVertex3f(animation[animation_id][frame_number][i][3], animation[animation_id][frame_number][i][4], animation[animation_id][frame_number][i][5]);
			glTexCoord2f(vertex_info[i][13], vertex_info[i][14]);
			glVertex3f(animation[animation_id][frame_number][i][6], animation[animation_id][frame_number][i][7], animation[animation_id][frame_number][i][8]);
		glEnd();
	}

	glDisable(GL_TEXTURE_2D);
}


void Model::translate(float x, float y, float z)
{
	for (int i = 0; i < surfaces_number; ++i)
	{
		vertex_info[i][0] += x;
		vertex_info[i][1] += y;
		vertex_info[i][2] += z;
		vertex_info[i][3] += x;
		vertex_info[i][4] += y;
		vertex_info[i][5] += z;
		vertex_info[i][6] += x;
		vertex_info[i][7] += y;
		vertex_info[i][8] += z;
	}
}

void Model::translateWithAni(float x, float y, float z)
{
	int frameCount;

	for (int i = 0; i < animationCount; i++){
		
		frameCount = frame_count[i] - 1;

		for (int j = 0; j < frameCount; j++){
			for (int k = 0; k < surfaces_number; k++){
				animation[i][j][k][0] += x;
				animation[i][j][k][1] += y;
				animation[i][j][k][2] += z;
				animation[i][j][k][3] += x;
				animation[i][j][k][4] += y;
				animation[i][j][k][5] += z;
				animation[i][j][k][6] += x;
				animation[i][j][k][7] += y;
				animation[i][j][k][8] += z;	
			}
		}
	}
	refreshBoundingBox();
}


void Model::translate(float x, float y, float z, int animation_id)
{
	for (int j = 0; j < really_frame_number-1; j++)
	{
		for (int i = 0; i < surfaces_number; ++i)
		{
			animation[animation_id][j][i][0] += x;
			animation[animation_id][j][i][1] += y;
			animation[animation_id][j][i][2] += z;
			animation[animation_id][j][i][3] += x;
			animation[animation_id][j][i][4] += y;
			animation[animation_id][j][i][5] += z;
			animation[animation_id][j][i][6] += x;
			animation[animation_id][j][i][7] += y;
			animation[animation_id][j][i][8] += z;
		}
	}
}


void Model::refreshBoundingBox()
{
	boundingBox.min.setX(vertex_info[0][0]);
	boundingBox.min.setZ(vertex_info[0][2]);
	boundingBox.max.setX(vertex_info[0][0]);
	boundingBox.max.setZ(vertex_info[0][2]);

	for (int i = 0; i < surfaces_number; ++i)
	{
		// min for x
		if (boundingBox.min.getX() > vertex_info[i][0])
			boundingBox.min.setX(vertex_info[i][0]);
		if (boundingBox.min.getX() > vertex_info[i][3])
			boundingBox.min.setX(vertex_info[i][3]);
		if (boundingBox.min.getX() > vertex_info[i][6])
			boundingBox.min.setX(vertex_info[i][6]);

		// min for z
		if (boundingBox.min.getZ() > vertex_info[i][2])
			boundingBox.min.setZ(vertex_info[i][2]);
		if (boundingBox.min.getZ() > vertex_info[i][5])
			boundingBox.min.setZ(vertex_info[i][5]);
		if (boundingBox.min.getZ() > vertex_info[i][8])
			boundingBox.min.setZ(vertex_info[i][8]);

		// max for x
		if (boundingBox.max.getX() < vertex_info[i][0])
			boundingBox.max.setX(vertex_info[i][0]);
		if (boundingBox.max.getX() < vertex_info[i][3])
			boundingBox.max.setX(vertex_info[i][3]);
		if (boundingBox.max.getX() < vertex_info[i][6])
			boundingBox.max.setX(vertex_info[i][6]);

		// max for z
		if (boundingBox.max.getZ() < vertex_info[i][2])
			boundingBox.max.setZ(vertex_info[i][2]);
		if (boundingBox.max.getZ() < vertex_info[i][5])
			boundingBox.max.setZ(vertex_info[i][5]);
		if (boundingBox.max.getZ() < vertex_info[i][8])
			boundingBox.max.setZ(vertex_info[i][8]);
	}
}


void Model::setMaterial()
{
	float MatAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	float MatDiffuse[] = { 0.5f, 0.8f, 0.3f, 1.0f };
	float MatSpecular[] = { 0.99f, 0.99f, 0.99f, 0.1f };
	float MatShininess = 128.0;
	float black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glColor3f(1, 1, 1);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MatAmbient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MatDiffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpecular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, MatShininess);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
}


void Model::setAnimationCount(int animation_count)
{
	this->frame_count = new unsigned int[animation_count];
	this->animation = new float***[animation_count];
	animationCount = animation_count;
}


void Model::setAnimation(int animation_id, int input_frame_count, float ***input_animation)
{
	frame_count[animation_id] = input_frame_count;
	animation[animation_id] = input_animation;
}


void Model::setFrameNumber(unsigned int current_frame)
{
	frame_number = current_frame;
}


void Model::setReallyFrameNumber(int number)
{
	really_frame_number = number;
}


BoundingBox Model::getBoundingBox()
{
	return boundingBox;
}


bool Model::getCollisionStatus()
{
	return this->collisionEnable;
}


// Using between glPushMatrix() and glPopMatrix()
void Model::jbTranslate(float inputX, float inputY, float inputZ)
{
	this->positionX = inputX;
	this->positionY = inputY;
	this->positionZ = inputZ;

	glTranslatef(inputX, inputY, inputZ);
}


float Model::getPositionX()
{
	return this->positionX;
}


float Model::getPositionY()
{
	return this->positionY;
}


float Model::getPositionZ()
{
	return this->positionZ;
}