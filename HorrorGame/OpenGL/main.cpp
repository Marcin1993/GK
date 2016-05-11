#include <iostream>

#include "MainGameMenu.h"
#include "Game.h"

using namespace OpenGL;

[STAThreadAttribute]
int _tWinMain(array<System::String ^> ^args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MainGameMenu());
	return 0;
}