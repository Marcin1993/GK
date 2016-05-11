#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <Windows.h>
#include <Mmsystem.h>
#include <math.h>
#include <fmod/fmod.hpp>

#include "Animation.h"
#include "Model.h"
#include "Texture.h"
#include "Point.h"
#include "Shader.h"
#include "ShaderProgram.h"

#define PI 3.14159265359

enum TYPE_OF_MOVE
{
	MOVE_STOP,
	MOVE_NORMAL,
	MOVE_RUN
};

class GameEnvironment : public IDrawable
{
private:
	Model *enemyMonster, *enemyMonsterTwo, *flashlight, *level, *table, *terminal, *accesscard;
	Model *gameOverFail, *gameOverSuccess;

	float monsterLastPositionX, monsterLastPositionY, monsterLastPositionZ;
	float monsterSpeed;
	int monsterIsRunning;
	int monsterAnimationId;
	int isMonsterSawPlayer;

	int windowWidth, windowHeight;

	BoundingBox cameraBox;
	Point3D<float> cameraPosition;
	Point3D<float> cameraDirection;
	float cameraYaw, cameraPitch;

	vector<Point3D<float>> levelCollisionX;
	vector<Point3D<float>> levelCollisionZ;
	int collisionVectorSizeX;
	int collisionVectorSizeZ;
	bool isCollision;
	Point3D<float> lastNoCollision;

	bool accesscardIsFound;
	bool leftButtonMouse;
	bool rightButtonMouse;
	bool gameWon;
	bool gameOver;
	bool lightOn;
	int blinkCounter; 
	int blinkDelay;
	int gameOverCounter;

	int enemyMonsterRandomSoundId;
	int enemyMonsterRandomSoundFlag;
	int enemyMonsterRandomSoundCounter;
	int enemyMonsterRandomSoundDelay;

	bool moveAllowed;
	short typeMove;
	bool pause;
	float levelOfRadar;
	int beepCounter;
	int delayBeep;
	float distanceToMonster;
	bool triggerMonsterSounds;
	bool footstepSoundPlayed;
	bool sprintStepEnable;
	FMOD::System *system; 
	FMOD::Sound **sound;		
	FMOD::Channel **channel;

	void addLight();
	void addFog();

	void setCameraBoundingBox();
	void detectCollision(Model* model);
	void loadLevelCollisionDescriptor(const char* path);
	void checkLevelCollisionX();
	void checkLevelCollisionZ();

	float min(float X, float Y, float Z);
	float max(float X, float Y, float Z);

	void countDistanceToMonster();
	void jbCountDistanceToMonster();
	void playRadarSound();
	void playMonsterSounds();
	void playPlayerFootstepSound();
	void playEnemyMonsterRandomSound();
	void checkEndGame();
	void drawHintTextToWin();

	void initVariables();
	void initModels();
	void initSound();
	void initCollision();
	void initShaders();
	
	Shader vertexShader;
	Shader flashlightShader;
	ShaderProgram shaderProgram;
	
public:
	unsigned int frame;

	virtual void draw();
	GameEnvironment();
	~GameEnvironment();
	
	void setWindowSize(int width, int height);
	void setCameraPosition(Point3D<float> cameraPosition);
	void setCameraDirection(Point3D<float> cameraDirection);
	void setCameraYaw(float yaw);
	void setCameraPitch(float pitch);
	void setTypeMove(short type);
	void setPauseState(bool pause);
	void setMouseButtonsState(bool leftButton, bool rightButton);
	bool getCollisionStatus();
	void setLastNoCollision(float x, float y, float z);
	Point3D<float> getLastNoCollision();

	void enemyMonsterRun();
	void enemyMonsterStop();
	void playEnemyMonsterFootstep();
	void isEnemyMonsterSeePlayer();
	void isEnemyMonsterCatchPlayer();
	void enemyMonsterAttack();
	void isEnemyMonsterRunAway();
	void setRandomValue();
	bool getMovableCamera();
};