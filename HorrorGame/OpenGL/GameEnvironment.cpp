#include "GameEnvironment.h"

GameEnvironment::GameEnvironment()
{
	std::cout << "Konstruktor gameenvironment" << std::endl;

	initVariables();

	try
	{
		initModels();
	}
	catch (Exception e)
	{
		MessageBoxA(NULL, "Oops, something went wrong :(\nPlease press OK and restart game", "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		exit(0);
	}

	try
	{
		initCollision();
	}
	catch (LoadingFileError e)
	{
		MessageBoxA(NULL, e.type().c_str(), "Error", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
	}
	catch (Exception e)
	{
		MessageBoxA(NULL, "Oops, something went wrong :(\nPlease press OK and restart game", "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		exit(0);
	}

	try
	{
		initSound();
	}
	catch (InitFmodError e)
	{
		MessageBoxA(NULL, e.type().c_str(), "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		exit(0);
	}
	catch (SoundError e)
	{
		MessageBoxA(NULL, e.type().c_str(), "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		exit(0);
	}
	catch (Exception e)
	{
		MessageBoxA(NULL, "Oops, something with sounds went wrong :(\nPlease press OK and restart game", "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		exit(0);
	}

	try
	{
		initShaders();
	}
	catch (LoadingFileError e)
	{
		MessageBoxA(NULL, e.type().c_str(), "Error", MB_OK | MB_ICONWARNING | MB_SYSTEMMODAL);
	}
	catch (Exception e)
	{
		MessageBoxA(NULL, "Oops, something went wrong :(\nPlease press OK and restart game", "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		exit(0);
	}
}


GameEnvironment::~GameEnvironment()
{
	system->release();
	delete enemyMonster;
	delete flashlight;
	delete level;
	delete table;
	delete terminal;
	delete accesscard;
	delete gameOverFail;
	delete gameOverSuccess;
}


void GameEnvironment::initVariables()
{
	srand(time(NULL));

	blinkCounter = 0;
	blinkDelay = 60;
	lightOn = true;
	accesscardIsFound = false;
	gameOver = false;
	gameWon = false;
	gameOverCounter = 0;
	moveAllowed = true;
}


void GameEnvironment::initModels()
{
	enemyMonster = new Model("data/models/monster/alien.obj", "data/models/monster/alien.bmp", true);
	flashlight = new Model("data/models/flashlight/flashlight.obj", "data/models/flashlight/flashlight.bmp", false);
	level = new Model("data/level/level.obj", "data/level/level.bmp", false);
	table = new Model("data/models/table/table.obj", "data/models/table/table.bmp", true);
	terminal = new Model("data/models/terminal/terminal.obj", "data/models/terminal/terminal_texture.bmp", false);
	accesscard = new Model("data/models/accesscard/accesscard.obj", "data/models/accesscard/accesscard.bmp", false);
	gameOverFail = new Model("data/models/end_screeen/end_square.obj", "data/models/end_screeen/game_over_fail2.bmp", false);
	gameOverSuccess = new Model("data/models/end_screeen/end_square.obj", "data/models/end_screeen/game_over_success2.bmp", false);

	int animationCount = 2;
	Animation **ani = new Animation*[animationCount];
	for (int i = 0; i < animationCount; i++)
	{
		ani[i] = new Animation();
	}

	ani[0]->loadAnimation("data/animations/monster/run/run");
	ani[1]->loadAnimation("data/animations/monster/attack/attack");

	enemyMonster->setReallyFrameNumber(ani[0]->getFrameCount());
	enemyMonster->setAnimationCount(animationCount);
	enemyMonster->setAnimation(0, ani[0]->getFrameCount(), ani[0]->getSingleAnimation());
	enemyMonster->setAnimation(1, ani[1]->getFrameCount(), ani[1]->getSingleAnimation());

	monsterAnimationId = 0;
	frame = 0;
	monsterSpeed = 0.0;
	monsterIsRunning = 0;
	isMonsterSawPlayer = 0;
	monsterLastPositionX = -5.0;
	monsterLastPositionY = -7.0;
	monsterLastPositionZ = 45.0;


	table->translate(-52.0, -5.0, -50.0);
	table->refreshBoundingBox();
}


void GameEnvironment::initSound()  throw(Exception)
{
	triggerMonsterSounds = true;
	footstepSoundPlayed = false;
	sprintStepEnable = false;

	beepCounter = 0;
	delayBeep = 100;

	enemyMonsterRandomSoundId = 0;
	enemyMonsterRandomSoundFlag = 0;
	enemyMonsterRandomSoundCounter = 0;

	sound = new FMOD::Sound*[15]; 
	channel = new FMOD::Channel*[15];

	if (FMOD::System_Create(&system) != FMOD_OK)
		throw InitFmodError("Create the main object of fmod failed!\nPlease press OK and restart game.");
	if (system->init(10, FMOD_INIT_NORMAL, NULL) != FMOD_OK)
		throw InitFmodError("Initialization fmod failed!\nPlease press OK and restart game.");
	if (system->createSound("data/audio/monster/attack/alien_attack_ls.wav", FMOD_LOOP_OFF, 0, &sound[0]) != FMOD_OK) // zmiana z &sound
		throw SoundError("Failed to create sound!\nPlease press OK and restart game.\nExpected path of file:\ndata/audio/monster/attack/alien_attack_ls.wav");
	if (system->createSound("data/audio/footstep.wav", FMOD_LOOP_NORMAL, 0, &sound[1]) != FMOD_OK)
		throw SoundError("Failed to create sound!\nPlease press OK and restart game.\nExpected path of file:\ndata/audio/footstep.wav");
	if (system->createSound("data/audio/footstep_run.wav", FMOD_LOOP_NORMAL, 0, &sound[2]) != FMOD_OK)
		throw SoundError("Failed to create sound!\nPlease press OK and restart game.\nExpected path of file:\ndata/audio/footstep_run.wav");
	if (system->createSound("data/audio/ambient.wav", FMOD_LOOP_NORMAL, 0, &sound[3]) != FMOD_OK)
		throw SoundError("Failed to create sound!\nPlease press OK and restart game.\nExpected path of file:\ndata/audio/ambient.wav");
	if (system->createSound("data/audio/monster/attack/alien_attack_hs.wav", FMOD_LOOP_OFF, 0, &sound[4]) != FMOD_OK)
		throw SoundError("Failed to create sound!\nPlease press OK and restart game.\nExpected path of file:\ndata/audio/monster/attack/alien_attack_hs.wav");

	if (system->createSound("data/audio/monster/random/alien_sounds_random_1.wav", FMOD_LOOP_OFF, 0, &sound[5]) != FMOD_OK)
		throw SoundError("Failed to create sound!\nPlease press OK and restart game.\nExpected path of file:\ndata/audio/monster/random/alien_sounds_random_1.wav");
	if (system->createSound("data/audio/monster/random/alien_sounds_random_2.wav", FMOD_LOOP_OFF, 0, &sound[6]) != FMOD_OK)
		throw SoundError("Failed to create sound!\nPlease press OK and restart game.\nExpected path of file:\ndata/audio/monster/random/alien_sounds_random_2.wav");
	if (system->createSound("data/audio/monster/random/alien_sounds_random_3.wav", FMOD_LOOP_OFF, 0, &sound[7]) != FMOD_OK)
		throw SoundError("Failed to create sound!\nPlease press OK and restart game.\nExpected path of file:\ndata/audio/monster/random/alien_sounds_random_3.wav");
	if (system->createSound("data/audio/monster/random/alien_sounds_random_4.wav", FMOD_LOOP_OFF, 0, &sound[8]) != FMOD_OK)
		throw SoundError("Failed to create sound!\nPlease press OK and restart game.\nExpected path of file:\ndata/audio/monster/random/alien_sounds_random_4.wav");
	if (system->createSound("data/audio/monster/random/alien_sounds_random_5.wav", FMOD_LOOP_OFF, 0, &sound[9]) != FMOD_OK)
		throw SoundError("Failed to create sound!\nPlease press OK and restart game.\nExpected path of file:\ndata/audio/monster/random/alien_sounds_random_5.wav");
	if (system->createSound("data/audio/monster/random/alien_sounds_random_6.wav", FMOD_LOOP_OFF, 0, &sound[10]) != FMOD_OK)
		throw SoundError("Failed to create sound!\nPlease press OK and restart game.\nExpected path of file:\ndata/audio/monster/random/alien_sounds_random_6.wav");
	if (system->createSound("data/audio/monster/random/alien_sounds_random_7.wav", FMOD_LOOP_OFF, 0, &sound[11]) != FMOD_OK)
		throw SoundError("Failed to create sound!\nPlease press OK and restart game.\nExpected path of file:\ndata/audio/monster/random/alien_sounds_random_7.wav");
	if (system->createSound("data/audio/monster/random/alien_sounds_random_8.wav", FMOD_LOOP_OFF, 0, &sound[12]) != FMOD_OK)
		throw SoundError("Failed to create sound!\nPlease press OK and restart game.\nExpected path of file:\ndata/audio/monster/random/alien_sounds_random_8.wav");
	if (system->createSound("data/audio/monster/random/alien_sounds_random_9.wav", FMOD_LOOP_OFF, 0, &sound[13]) != FMOD_OK)
		throw SoundError("Failed to create sound!\nPlease press OK and restart game.\nExpected path of file:\ndata/audio/monster/random/alien_sounds_random_9.wav");
	if (system->createSound("data/audio/monster/footstep/alien_footstep_echo.wav", FMOD_LOOP_NORMAL, 0, &sound[14]) != FMOD_OK)
		throw SoundError("Failed to create sound!\nPlease press OK and restart game.\nExpected path of file:\ndata/audio/monster/footstep/alien_footstep_echo.wav");
	else
		system->playSound(sound[3], NULL, false, &channel[3]);
}


void GameEnvironment::initCollision()
{
	collisionVectorSizeX = 0;
	collisionVectorSizeZ = 0;
	loadLevelCollisionDescriptor("data/level/level_descriptor.txt");
}


void GameEnvironment::initShaders()
{
	glewInit();
	if (!vertexShader.loadShader("data/shaders/vertex.txt", GL_VERTEX_SHADER))
		throw LoadingFileError("Can not found shader file!\nExpected path of file:\ndata/shaders/vertex.txt");
	if (!flashlightShader.loadShader("data/shaders/flashlight.txt", GL_FRAGMENT_SHADER))
		throw LoadingFileError("Can not found shader file!\nnExpected path of file:\ndata/shaders/flashlight.txt");
	shaderProgram.createProgram();
	shaderProgram.addShader(&vertexShader);
	shaderProgram.addShader(&flashlightShader);
	shaderProgram.linkProgram();
	shaderProgram.useProgram();
}

void GameEnvironment::draw()
{
	if (blinkCounter++ < blinkDelay)
		;
	else
	{
		blinkDelay = (30 * rand()) / (RAND_MAX + 1.0);
		lightOn = rand() % 2 == 1;
		blinkCounter = 0;

		if (blinkDelay > 15 && !lightOn)
			lightOn = true;
	}

	if (!gameOver && !gameWon)
	{
		if (lightOn || pause)
		{
			// add ambient and directed light
			addLight();

			//add fog
			addFog();

			// flashlight
			glPushMatrix();
			//move with camera
			glTranslated(cameraPosition.getX(), cameraPosition.getY(), cameraPosition.getZ());
			//rotate with camera
			glRotatef(-cameraYaw * 180 / PI, 0, 1, 0);
			glRotatef(-cameraPitch * 180 / PI, 0, 0, 1);
			glScalef(0.25, 0.25, 0.25);
			glTranslatef(1.0, -0.4, +0.7);
			glRotated(60, 0.7, -3.0, 0.5);
			flashlight->draw();
			glPopMatrix();
			
			// level
			glPushMatrix();
			level->draw();
			glPopMatrix();

			//table
			glPushMatrix();
			table->draw();
			glPopMatrix();

			if (!accesscardIsFound)
			{
				//accesscard
				glPushMatrix();
				glTranslatef(-38.0, -1.3, -58.0);
				accesscard->draw();
				glPopMatrix();
			}

			// terminal
			glPushMatrix();
			glScalef(1.0, 0.9, 1.0);
			glTranslatef(-34.5, -1.3, -59);
			terminal->draw();
			glPopMatrix();

			// monster
			glPushMatrix();
				monsterLastPositionZ = (monsterLastPositionZ + monsterSpeed);
				enemyMonster->jbTranslate(monsterLastPositionX, monsterLastPositionY, monsterLastPositionZ);
				glRotated(180, 0, -1.0, 0);

				enemyMonster->setFrameNumber(frame);
				enemyMonster->drawWithAni(monsterAnimationId);
				++frame;
				if (monsterIsRunning)
				{
					monsterSpeed += 0.02;
				}
				else
				{
					monsterSpeed = 0.0;
				}

				if (frame == (enemyMonster->frame_count[monsterAnimationId] - 1))
				{
					frame = 0;
				}
			glPopMatrix();

			glDisable(GL_TEXTURE_2D);
		}

		setCameraBoundingBox();		

		//countDistanceToMonster();
		jbCountDistanceToMonster();

		detectCollision(enemyMonster);
		detectCollision(table);
		//collision with walls
		checkLevelCollisionX();
		checkLevelCollisionZ();

		playRadarSound();
		playPlayerFootstepSound();
		playEnemyMonsterRandomSound();

		isEnemyMonsterSeePlayer();
		isEnemyMonsterCatchPlayer();
		isEnemyMonsterRunAway();
		checkEndGame();

		glFlush();
	}
	else if (gameWon)
	{
		// Add ambient light
		GLfloat ambientColor[] = { 0.85f, 0.85f, 0.85f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
		glPushMatrix();
		//move with camera
		glTranslated(cameraPosition.getX(), cameraPosition.getY(), cameraPosition.getZ());
		//rotate with camera
		glRotatef(-cameraYaw * 180 / PI, 0, 1, 0);
		glRotatef(-cameraPitch * 180 / PI, 0, 0, 1);
		glScalef(0.5, 0.5, 0.5);
		glTranslatef(12.0, -5.0, 0.0);
		glRotated(90, 0.0, 1.0, 0.0);
		gameOverSuccess->draw();
		glPopMatrix();
	}
	else if (gameOver)
	{
		// Add ambient light
		GLfloat ambientColor[] = { 0.85f, 0.85f, 0.85f, 1.0f };
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
		glPushMatrix();
		//move with camera
		glTranslated(cameraPosition.getX(), cameraPosition.getY(), cameraPosition.getZ());
		//rotate with camera
		glRotatef(-cameraYaw * 180 / PI, 0, 1, 0);
		glRotatef(-cameraPitch * 180 / PI, 0, 0, 1);
		glScalef(0.5, 0.5, 0.5);
		glTranslatef(12.0, -5.0, 0.0);
		glRotated(90, 0.0, 1.0, 0.0);
		gameOverFail->draw();
		glPopMatrix();
	}
}


void GameEnvironment::setCameraPosition(Point3D<float> cameraPosition)
{
	this->cameraPosition = cameraPosition;
}


void GameEnvironment::setCameraDirection(Point3D<float> cameraDirection)
{
	this->cameraDirection = cameraDirection;
}


void GameEnvironment::setCameraYaw(float yaw)
{
	this->cameraYaw = yaw;
}


void GameEnvironment::setCameraPitch(float pitch)
{
	this->cameraPitch = pitch;
}


void GameEnvironment::setTypeMove(short type)
{
	this->typeMove = type;
}


void GameEnvironment::setPauseState(bool pause)
{
	this->pause = pause;
}


void GameEnvironment::addFog()
{
	GLfloat density = 0.025;
	GLfloat fogColor[4] = { 0.00, 0.00, 0.00, 1.0 };

	glEnable(GL_FOG);
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, density);
	glHint(GL_FOG_HINT, GL_NICEST);
}


void GameEnvironment::addLight()
{
	// Add ambient light
	GLfloat ambientColor[] = { 0.02f, 0.02f, 0.02f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

	// Add directed light
	GLfloat lightColor1[] = { 1, 1, 1, 1 };
	GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	
	// Coming from the camera position
	// Pointing at the camera direction
	GLfloat lightPos1[] = { cameraPosition.getX(), cameraPosition.getY(), cameraPosition.getZ() };
	GLfloat spotDirection[] = { cameraDirection.getX(), -cameraDirection.getY(), cameraDirection.getZ() };

	glLightfv(GL_LIGHT1, GL_AMBIENT, black);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, black);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotDirection);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 30.0f);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45.0f);
}


void GameEnvironment::setCameraBoundingBox()
{
	float cameraBoundWidthX = 0.5, cameraBoundWidthZ = 1.5;
	float cameraX = cameraPosition.getX(), cameraZ = cameraPosition.getZ();

	cameraBox.min.setX(cameraX - cameraBoundWidthX);
	cameraBox.min.setZ(cameraZ - cameraBoundWidthZ);
	cameraBox.max.setX(cameraX + cameraBoundWidthX);
	cameraBox.max.setZ(cameraZ + cameraBoundWidthZ);
}

// method for collision detection
void GameEnvironment::detectCollision(Model* model)
{
	//collision with models
	if (model->getCollisionStatus())
	{
		bool isCollisionPartA, isCollisionPartB;

		isCollisionPartA = (cameraBox.min.getX() <= model->getBoundingBox().max.getX() &&
			cameraBox.min.getZ() <= model->getBoundingBox().max.getZ());
		isCollisionPartB = (cameraBox.max.getX() > model->getBoundingBox().min.getX() &&
			cameraBox.max.getZ() > model->getBoundingBox().min.getZ());

		if (isCollisionPartA && isCollisionPartB)
		{
			this->isCollision = true;
			if (model == table && leftButtonMouse)
				accesscardIsFound = true;
		}
		else
			this->isCollision = false;
	}
	else
		this->isCollision = false;
}

//loads information about level from the descriptor
void GameEnvironment::loadLevelCollisionDescriptor(const char* path)  throw(Exception)
{
	FILE* file = fopen(path, "r");		// open in read-only mode
	
	if (file == NULL)
		throw LoadingFileError(std::string("File with descriptor of collision not found!\nMaybe collision will not work!\nPath of file:\n") + path);
	
	Point3D<float> tempVertex[3];

	while (1)
	{
		char tmp[20];
		if (fscanf(file, "%s", tmp) == EOF)
			break;
		
		float x, y, z;
		// set first 3 vertices
		x = atof(tmp);
		tempVertex[0].setX(x);
		fscanf(file, "\t%f", &y);
		tempVertex[0].setY(y);
		fscanf(file, "\t%f\n", &z);
		tempVertex[0].setZ(z);

		fscanf(file, "%f", &x);
		tempVertex[1].setX(x);
		fscanf(file, "\t%f", &y);
		tempVertex[1].setY(y);
		fscanf(file, "\t%f\n", &z);
		tempVertex[1].setZ(z);
			
		fscanf(file, "%f", &x);
		tempVertex[2].setX(x);
		fscanf(file, "\t%f", &y);
		tempVertex[2].setY(y);
		fscanf(file, "\t%f\n\n\n\n", &z);
		tempVertex[2].setZ(z);

		// checking if it's not a floor or ceiling
		if (tempVertex[0].getY() == tempVertex[1].getY() &&
			tempVertex[0].getY() == tempVertex[2].getY())
			continue;
		
		Point3D<float> tempVertex2;

		// checking if the wall is parallel to X-axis
		if (tempVertex[0].getX() == tempVertex[1].getX() &&
			tempVertex[0].getX() == tempVertex[2].getX()){

			//X - X, Y - minZ, Z - maxZ
			tempVertex2.setX(tempVertex[0].getX());
			tempVertex2.setY(min(tempVertex[0].getZ(), tempVertex[1].getZ(), tempVertex[2].getZ()));
			tempVertex2.setZ(max(tempVertex[0].getZ(), tempVertex[1].getZ(), tempVertex[2].getZ()));

			levelCollisionX.push_back(tempVertex2);
			++collisionVectorSizeX;
		}
		// the wall is parallel to Z-axis
		else{
			//X - Z, Y - minX, Z - maxX
			tempVertex2.setX(tempVertex[0].getZ());
			tempVertex2.setY(min(tempVertex[0].getX(), tempVertex[1].getX(), tempVertex[2].getX()));
			tempVertex2.setZ(max(tempVertex[0].getX(), tempVertex[1].getX(), tempVertex[2].getX()));

			levelCollisionZ.push_back(tempVertex2);
			++collisionVectorSizeZ;
		}
	}

	fclose(file);
}

//sets isCollision to true if there's collision with a wall parallel to X-axis
void GameEnvironment::checkLevelCollisionX()
{
	float posX = cameraPosition.getX();
	float posZ = cameraPosition.getZ();

	float boxWidth = 2.0;

	for (int i = 0; i < collisionVectorSizeX; i++){
		if (abs(posX - levelCollisionX[i].getX()) <= boxWidth){
			// minZ <= posZ <= maxZ
			if (posZ >= levelCollisionX[i].getY() && posZ <= levelCollisionX[i].getZ()){
				isCollision = true;
				break;
			}
		}
	}
}

//sets isCollision to true if there's collision with a wall parallel to Z-axis
void GameEnvironment::checkLevelCollisionZ()
{
	float posX = cameraPosition.getX();
	float posZ = cameraPosition.getZ();
	
	float boxWidth = 2.0;

	for (int i = 0; i < collisionVectorSizeZ; i++){
		if (abs(posZ - levelCollisionZ[i].getX()) <= boxWidth){
			// minX <= posX <= maxX
			if (posX >= levelCollisionZ[i].getY() && posX <= levelCollisionZ[i].getZ()){
				isCollision = true;
				break;
			}
		}
	}
}

//sets coordinates of the last position without collision to given values
void GameEnvironment::setLastNoCollision(float x, float y, float z)
{
	lastNoCollision.setX(x);
	lastNoCollision.setY(y);
	lastNoCollision.setZ(z);
}

//returns the last position without collision
Point3D<float> GameEnvironment::getLastNoCollision()
{
	return lastNoCollision;
}

//true if collision is detected, false otherwise
bool GameEnvironment::getCollisionStatus()
{
	return this->isCollision;
}

//calculate distance between monster and camera
void GameEnvironment::countDistanceToMonster()
{
	float deltaX = enemyMonster->getBoundingBox().max.getX() - cameraPosition.getX();
	float deltaY = enemyMonster->getBoundingBox().max.getY() - cameraPosition.getY();
	float deltaZ = enemyMonster->getBoundingBox().max.getZ() - cameraPosition.getZ();
	distanceToMonster = (float)sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
}


void GameEnvironment::jbCountDistanceToMonster()
{
	float deltaX = enemyMonster->getPositionX() - cameraPosition.getX();
	float deltaY = enemyMonster->getPositionY() - cameraPosition.getY();
	float deltaZ = enemyMonster->getPositionZ() - cameraPosition.getZ();
	distanceToMonster = (float)sqrt((deltaX * deltaX) + (deltaY * deltaY) + (deltaZ * deltaZ));
}


void GameEnvironment::playRadarSound()
{
	if (!pause)
	{
		if (distanceToMonster < 40)
		{
			levelOfRadar = 1.0;
			delayBeep = 30;
		}
		else if (distanceToMonster >= 40 && distanceToMonster < 80)
		{
			levelOfRadar = 0.8;
			delayBeep = 60;
		}
		else if (distanceToMonster >= 80 && distanceToMonster < 120)
		{
			levelOfRadar = 0.6;
			delayBeep = 90;
		}
		else if (distanceToMonster >= 120 && distanceToMonster < 160)
		{
			levelOfRadar = 0.4;
			delayBeep = 120;
		}
		else if (distanceToMonster >= 160 && distanceToMonster < 200)
		{
			levelOfRadar = 0.2;
			delayBeep = 150;
		}
		else
		{
			levelOfRadar = 0.0;
			delayBeep = 200;
		}

		if (beepCounter++ > delayBeep)
		{
			sndPlaySound(L"data/audio/beep.wav", SND_ASYNC);
			std::cout << "beep " << distanceToMonster << "\n";
			beepCounter = 0;
		}
	}
}


void GameEnvironment::playMonsterSounds()
{
	if (triggerMonsterSounds)
	{
		system->playSound(sound[0], NULL, false, &channel[0]);
		system->playSound(sound[4], NULL, false, &channel[4]);

		triggerMonsterSounds = false;
	}
}


void GameEnvironment::playPlayerFootstepSound()
{
	if (typeMove == MOVE_NORMAL && !footstepSoundPlayed)
	{
		std::cout << "normal\n"; 
			channel[1]->setPaused(true);
		system->playSound(sound[1], NULL, false, &channel[1]);
		footstepSoundPlayed = true; 
		sprintStepEnable = true;
	}
	else if (typeMove == MOVE_RUN && sprintStepEnable)
	{
		std::cout << "sprint\n";
		channel[1]->setPaused(true);
		system->playSound(sound[2], NULL, false, &channel[1]); 
		sprintStepEnable = false;
		footstepSoundPlayed = false;
	}
	else if (typeMove == MOVE_STOP)
	{
		channel[1]->setPaused(true);
		footstepSoundPlayed = false;
		sprintStepEnable = false;
	}
}


void GameEnvironment::playEnemyMonsterRandomSound()
{
	if (!enemyMonsterRandomSoundFlag)
	{
		enemyMonsterRandomSoundId = 9;
		setRandomValue();

		enemyMonsterRandomSoundDelay = rand();
		//while ((enemyMonsterRandomSoundDelay < 400))
		//{
		//	enemyMonsterRandomSoundDelay = (rand() / 100);
		//}
		enemyMonsterRandomSoundFlag = 1;
	}

	if ((enemyMonsterRandomSoundFlag) && ((enemyMonsterRandomSoundCounter > (enemyMonsterRandomSoundDelay / 20))))
	{
		system->playSound(sound[5 + enemyMonsterRandomSoundId], NULL, false, &channel[5 + enemyMonsterRandomSoundId]);
		enemyMonsterRandomSoundId = 9;
		enemyMonsterRandomSoundCounter = 0;
		enemyMonsterRandomSoundFlag = 0;
		//enemyMonsterRandomSoundDelay = (30 * rand());
	}
	++ enemyMonsterRandomSoundCounter;
}


//return min of 3
float GameEnvironment::min(float X, float Y, float Z)
{
	float min = X;

	if (min > Y)
		min = Y;
	if (min > Z)
		min = Z;

	return min;
}

//return max of 3
float GameEnvironment::max(float X, float Y, float Z)
{
	float max = X;
	if (max < Y)
		max = Y;
	if (max < Z)
		max = Z;

	return max;
}


void GameEnvironment::setMouseButtonsState(bool leftButton, bool rightButton)
{
	leftButtonMouse = leftButton;
	rightButtonMouse = rightButton;
}


void GameEnvironment::enemyMonsterRun()
{
	monsterIsRunning = 1;
	playEnemyMonsterFootstep();
	//monster_speed = speed;
}


void GameEnvironment::enemyMonsterStop()
{
	monsterIsRunning = 0;
	channel[14]->setPaused(true);
}


void GameEnvironment::playEnemyMonsterFootstep()
{
	system->playSound(sound[14], NULL, false, &channel[14]);
}


void GameEnvironment::isEnemyMonsterSeePlayer()
{
	if ((!isMonsterSawPlayer) && (distanceToMonster < 100))
	{
		isMonsterSawPlayer = 1;
		enemyMonsterRun();
	}
}


void GameEnvironment::isEnemyMonsterCatchPlayer()
{
	// Setup monster distance if he catch player.
	if ((distanceToMonster < 20) && (distanceToMonster < 19))
	{
		enemyMonsterStop();
		enemyMonsterAttack();
	}
}


void GameEnvironment::enemyMonsterAttack()
{
	monsterAnimationId = 1;
	playMonsterSounds();

	moveAllowed = false;
	// END GAME: YOU FAILED!

	if (gameOverCounter++ > 60)
		gameOver = true;
}


void GameEnvironment::isEnemyMonsterRunAway()
{
	if (distanceToMonster > 400)
	{
		enemyMonsterStop();
	}
}


void GameEnvironment::setRandomValue()
{
	while ((enemyMonsterRandomSoundId < 0) || (enemyMonsterRandomSoundId > 8))
	{
		enemyMonsterRandomSoundId = rand();
	}
}


void GameEnvironment::checkEndGame()
{
	bool conditionToWinPartA = (cameraBox.min.getX() <= -28 && cameraBox.min.getZ() <= -330);
	bool conditionToWinPartB = (cameraBox.max.getX() > -34 && cameraBox.max.getZ() > -335);

	if ( conditionToWinPartA && conditionToWinPartB &&
		 accesscardIsFound && leftButtonMouse)		// the game is won
	{
		gameWon = true;
	}
	else if (conditionToWinPartA && conditionToWinPartB && !leftButtonMouse)
	{
		drawHintTextToWin();
	}
}


void GameEnvironment::drawHintTextToWin()
{
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(0.0, windowWidth, 0.0, windowHeight);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 0.0f, 0.0f);
	glRasterPos2i(windowWidth / 2 - 240, (windowHeight / 2));
	std::string s = "If you have an access card press LMB to exit level";
	void * font = GLUT_BITMAP_TIMES_ROMAN_24;//GLUT_BITMAP_HELVETICA_18;
	glutBitmapString(font, (const unsigned char*)s.c_str());
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
}


void GameEnvironment::setWindowSize(int width, int height)
{
	windowWidth = width;
	windowHeight = height;
}


bool GameEnvironment::getMovableCamera()
{
	return moveAllowed;
}