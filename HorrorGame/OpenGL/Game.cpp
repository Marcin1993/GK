#include "Game.h"

Game::Game(int* _argc, char** _argv, const char* title, int width, int height, bool fullscreen)
{
	initComplete = false;

	// set pointer from command line
	argc = _argc;
	argv = _argv;

	// set properties of game window
	window.width = width;
	window.height = height;

	window.title = title;

	this->fullscreen = fullscreen;
}

Game::~Game()
{

}


void Game::initialize()
{
	window.fov_angle = 45;
	window.z_near = 0.1;
	window.z_far = 500.0;

	// set initial value for different variable
	shift_down = false;
	fps_mode = false;
	moveAllowed = true;
	viewport_width = 0;
	viewport_height = 0;
	mouse_left_down = false;
	mouse_right_down = false;
	for (int i = 0; i < 256; ++i)
		array_keys[i] = false;

	// movement setting
	normal_speed = 0.20; //0.15
	sprint_speed_enable = 0.0;
	sprint_speed_modifier = 0.2;
	translation_speed = normal_speed + sprint_speed_enable * sprint_speed_modifier;
	rotation_speed = M_PI / 180 * 0.2;

	// set game environment
	try
	{
		gameEnvironment = new GameEnvironment();
	}
	catch (Exception e)
	{
		MessageBoxA(NULL, "Oops, something went wrong :(\nPlease press OK and restart game", "Error", MB_OK | MB_ICONERROR | MB_SYSTEMMODAL);
		exit(0);
	}
	gameEnvironment->setWindowSize(window.width, window.height);
	pauseTextCounter = 0;
	initComplete = true;
}


void Game::run()
{
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(window.width, window.height);
	glutCreateWindow(window.title);

	if (fullscreen)
		glutFullScreen();

	initialize();
	
	glutIgnoreKeyRepeat(1);

	glEnable(GL_NORMALIZE);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS); // mo¿e byæ GL_LEQUAL, GL_LESS chyba lepsze

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);        
	glEnable(GL_LIGHTING);        
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	setupDisplayCallback();
	setupReshapeCallback();
	setupMouseCallback();
	setupMouseMotionCallback();
	setupMousePassiveMotionCallback();
	setupIdleCallback();
	setupKeyboardCallback();
	setupKeyboardUpCallback();
	setupTimerCallback();

	glutMainLoop();
}

// true - init complete, otherwise false
bool Game::checkInitStatus()
{
	return initComplete;
}


////////////////////////////////////////////////////////////
//														  //
// Callbacks and other functions for correct work of glut // 
//														  //
////////////////////////////////////////////////////////////

void Game::display() 
{
	glClearColor(0.0, 0.0, 0.0, 1.0); //clear the screen to black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear the color buffer and the depth buffer
	glLoadIdentity();

	if (!fps_mode)
	{
		if (pauseTextCounter++ >= 0 && pauseTextCounter < 30)
		{
			glDisable(GL_TEXTURE_2D);
			glDisable(GL_LIGHTING);
			glMatrixMode(GL_PROJECTION);
			glPushMatrix();
			glLoadIdentity();
			gluOrtho2D(0.0, window.width, 0.0, window.height);
			glMatrixMode(GL_MODELVIEW);
			glPushMatrix();
			glLoadIdentity();
			glColor3f(1.0f, 0.0f, 0.0f);
			glRasterPos2i(window.width / 2 - 170, (window.height / 2));
			std::string s = "PAUSE!!! Press spacebar to continue...";
			void * font = GLUT_BITMAP_TIMES_ROMAN_24;//GLUT_BITMAP_HELVETICA_18;
			glutBitmapString(font, (const unsigned char*)s.c_str());
			glMatrixMode(GL_PROJECTION);
			glPopMatrix();
			glMatrixMode(GL_MODELVIEW);
			glPopMatrix();
			glEnable(GL_LIGHTING);
			glEnable(GL_TEXTURE_2D);
		}
		else if (pauseTextCounter > 60)
		{
			pauseTextCounter = 0;
		}
	}

	camera.Refresh();
	gameEnvironment->setCameraPosition(camera.GetPos());
	gameEnvironment->setCameraDirection(camera.GetDir());
	gameEnvironment->setCameraYaw(camera.GetYaw());
	gameEnvironment->setCameraPitch(camera.GetPitch());
	gameEnvironment->setTypeMove(typeMove);
	gameEnvironment->setPauseState(!fps_mode);
	gameEnvironment->setMouseButtonsState(mouse_left_down, mouse_right_down);
	moveAllowed = gameEnvironment->getMovableCamera();
	gameEnvironment->draw();

	glFlush();
	glutSwapBuffers(); //swap the buffers
}

void Game::displayCallback()
{
	currentInstance->display();
}

void Game::setupDisplayCallback()
{
	currentInstance = this;
	::glutDisplayFunc(Game::displayCallback);
}

void Game::idleCallback()
{
	currentInstance->display();
}

void Game::setupIdleCallback()
{
	currentInstance = this;
	::glutIdleFunc(Game::idleCallback);
}

void Game::reshape(int w, int h) 
{
	viewport_width = w;
	viewport_height = h;

	glViewport(0, 0, (GLsizei)w, (GLsizei)h); //set the viewport to the current window specifications
	glMatrixMode(GL_PROJECTION); //set the matrix to projection

	glLoadIdentity();
	gluPerspective(window.fov_angle, (GLfloat)w / (GLfloat)h, window.z_near, window.z_far); //set the perspective (angle of sight, width, height, ,depth)
	glMatrixMode(GL_MODELVIEW); //set the matrix back to model
}

void Game::reshapeCallback(int w, int h)
{
	currentInstance->reshape(w, h);
}

void Game::setupReshapeCallback()
{
	currentInstance = this;
	::glutReshapeFunc(Game::reshapeCallback);
}

void Game::mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN) 
	{
		if (button == GLUT_LEFT_BUTTON) 
			mouse_left_down = true;
		else if (button == GLUT_RIGHT_BUTTON) 
			mouse_right_down = true;
	}
	else if (state == GLUT_UP) 
	{
		if (button == GLUT_LEFT_BUTTON) 
			mouse_left_down = false;
		else if (button == GLUT_RIGHT_BUTTON) 
			mouse_right_down = false;
	}
}

void Game::mouseCallback(int button, int state, int x, int y)
{
	currentInstance->mouse(button, state, x, y);
}

void Game::setupMouseCallback()
{
	currentInstance = this;
	::glutMouseFunc(Game::mouseCallback);
}

void Game::mouseMotion(int x, int y)
{
	static bool just_warped = false;

	if (just_warped) 
	{
		just_warped = false;
		return;
	}

	if (fps_mode) 
	{
		int dx = x - viewport_width / 2;
		int dy = y - viewport_height / 2;

		if (dx) 
			camera.RotateYaw(rotation_speed*dx);

		if (dy) 
			camera.RotatePitch(rotation_speed*dy);

		glutWarpPointer(viewport_width / 2, viewport_height / 2);

		just_warped = true;
	}
}

void Game::mouseMotionCallback(int x, int y)
{
	currentInstance->mouseMotion(x, y);
}

void Game::setupMouseMotionCallback()
{
	currentInstance = this;
	::glutMotionFunc(mouseMotionCallback);
}

void Game::mousePassiveMotionCallback(int x, int y)
{
	currentInstance->mouseMotion(x, y);
}

void Game::setupMousePassiveMotionCallback()
{
	currentInstance = this;
	::glutPassiveMotionFunc(mousePassiveMotionCallback);
}

void Game::keyboard(unsigned char key, int x, int y)
{
	if (key == 27) 
	{
		close();
	}

	if (key == ' ') 
	{
		fps_mode = !fps_mode;

		if (fps_mode) 
		{
			glutSetCursor(GLUT_CURSOR_NONE);
			glutWarpPointer(viewport_width / 2, viewport_height / 2);
		}
		else 
		{
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
	}

	array_keys[key] = true;
}

void Game::keyboardCallback(unsigned char key, int x, int y)
{
	currentInstance->keyboard(key, x, y);
}

void Game::setupKeyboardCallback()
{
	currentInstance = this;
	::glutKeyboardFunc(keyboardCallback);
}

void Game::keyboardUp(unsigned char key, int x, int y)
{
	array_keys[key] = false;
}

void Game::keyboardUpCallback(unsigned char key, int x, int y)
{
	currentInstance->keyboardUp(key, x, y);
}

void Game::setupKeyboardUpCallback()
{
	currentInstance = this;
	::glutKeyboardUpFunc(keyboardUpCallback);
}

void Game::timer(int value)
{
	bool noSprint, noKey1, noKey2;
	typeMove = MOVE_STOP;

	if (fps_mode && moveAllowed)
	{
		if (mouse_right_down)
		{
			sprint_speed_enable = 1.0;
			typeMove = MOVE_RUN;
			noSprint = false;
		}
		else
		{
			sprint_speed_enable = 0.0;
			noSprint = true;
		}
		translation_speed = normal_speed + sprint_speed_enable * sprint_speed_modifier;

		if(!gameEnvironment->getCollisionStatus())
		{
			Point3D<float> cameraPosition = camera.GetPos();
			gameEnvironment->setLastNoCollision(
				cameraPosition.getX(),
				cameraPosition.getY(),
				cameraPosition.getZ());

			if ((array_keys['w'] || array_keys['W']))
			{
				camera.Move(translation_speed);
				if (noSprint)
					typeMove = MOVE_NORMAL;
				noKey1 = false;
			}
			else if (array_keys['s'] || array_keys['S'])
			{
				camera.Move(-translation_speed);
				if (noSprint)
					typeMove = MOVE_NORMAL;
				noKey1 = false;
			}
			else
				noKey1 = true;

			if (array_keys['a'] || array_keys['A'])
			{
				camera.Strafe(translation_speed);
				if (noSprint)
					typeMove = MOVE_NORMAL;
				noKey2 = false;
			}
			else if (array_keys['d'] || array_keys['D'])
			{
				camera.Strafe(-translation_speed);
				if (noSprint)
					typeMove = MOVE_NORMAL;
				noKey2 = false;
			}
			else
				noKey2 = true;
		}
		else
		{
			std::cout << "kolizja!" << std::endl;
			Point3D<float> lastNoCollision = gameEnvironment->getLastNoCollision();
			camera.SetPos(
				lastNoCollision.getX(),
				lastNoCollision.getY(),
				lastNoCollision.getZ());
		}
	}

	if (noKey1 && noKey2 && !noSprint)
		typeMove = MOVE_STOP;

	setupTimerCallback();
}

void Game::timerCallback(int value)
{
	currentInstance->timer(value);
}

void Game::setupTimerCallback()
{
	currentInstance = this;
	::glutTimerFunc(1, timerCallback, 0);
}

void Game::close()
{
	glutDestroyWindow(1);
}