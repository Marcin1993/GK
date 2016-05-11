#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>

#define _USE_MATH_DEFINES
#define M_PI 3.14159265358979323846
#include <cmath>

#include "Camera.h"
#include "Model.h"
#include "Texture.h"
#include "GameEnvironment.h"

/** struct describes properties of game window **/
typedef struct {
	int width;			// width of game window
	int height;			// height of game window
	const char* title;		// title of game window

	float fov_angle;	// field of view
	float z_near;		// draw distance near
	float z_far;		// draw distance far
} glutWindow;

class Game;
static Game* currentInstance;
class Game
{
private:
	int* argc;
	char** argv;

	glutWindow window;
	Camera camera;
	GameEnvironment* gameEnvironment;

	bool initComplete;
	bool fullscreen;
	int pauseTextCounter;

	int viewport_width;
	int viewport_height;

	bool mouse_left_down;
	bool mouse_right_down;

	bool fps_mode;
	float rotation_speed;

	bool shift_down;
	bool array_keys[256];

	float normal_speed;
	float sprint_speed_enable;
	float sprint_speed_modifier;
	float translation_speed;

	short typeMove;
	bool moveAllowed;

	void initialize();
	void close();
	
	void display();
	static void displayCallback();
	void setupDisplayCallback();
	static void idleCallback();
	void setupIdleCallback();
	
	void reshape(int w, int h);
	static void reshapeCallback(int w, int h);
	void setupReshapeCallback();

	void mouse(int button, int state, int x, int y);
	static void mouseCallback(int button, int state, int x, int y);
	void setupMouseCallback();

	void mouseMotion(int x, int y);
	static void mouseMotionCallback(int x, int y);
	void setupMouseMotionCallback();
	static void mousePassiveMotionCallback(int x, int y);
	void setupMousePassiveMotionCallback();

	void keyboard(unsigned char key, int x, int y);
	static void keyboardCallback(unsigned char key, int x, int y);
	void setupKeyboardCallback();

	void keyboardUp(unsigned char key, int x, int y);
	static void keyboardUpCallback(unsigned char key, int x, int y);
	void setupKeyboardUpCallback();

	void timer(int value);
	static void timerCallback(int value);
	void setupTimerCallback();

public:
	Game(int* _argc, char** _argv, const char* title, int width, int height, bool fullscreen);
	~Game();

	void run();
	bool checkInitStatus();
};