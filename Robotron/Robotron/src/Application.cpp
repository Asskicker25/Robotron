#include "Robotron.h"

int main(int argc, char* argv[])
{
	Robotron game;

	Debugger::print = false;

	game.InitializeWindow(1366, 768);

	game.Render();

	return -1;
}