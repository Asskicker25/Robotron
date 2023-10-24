#include "Robotron.h"

int main(int argc, char* argv[])
{
	Robotron game;

	Debugger::print = true;

	game.InitializeWindow(800, 600);

	game.Render();

	return -1;
}