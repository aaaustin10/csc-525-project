#include "includes.h"


MasterIO::MasterIO():
lastXPos(0),
lastYPos(0)
{

}
MasterIO::~MasterIO()
{

}


// ===========Keyboard Stuff=============


void MasterIO::handle_normal_keyboard_down(unsigned char key, int x, int y)
{
	std::cout << key << " " << (int)key << " " << x << " " << y << " down" << std::endl;
}

void MasterIO::handle_normal_keyboard_up(unsigned char key, int x, int y)
{
	std::cout << key << " " << (int)key << " " << x << " " << y << " up" << std::endl;
}

void MasterIO::handle_special_keyboard_down(int key, int x, int y)
{
	std::cout << (int)key << " " << x << " " << y << std::endl;
}

void MasterIO::handle_special_keyboard_up(int key, int x, int y)
{
	std::cout << (int)key << " " << x << " " << y << std::endl;
}



// ===========Mouse Stuff=============


void MasterIO::handle_mouse(int button, int state, int x, int y)
{
	std::cout << button << " " << state << " " << x << " " << y << std::endl;
}

void MasterIO::handle_mouse_movement(int x, int y)
{
	int xChange = lastXPos - x;
	int yChange = lastYPos - y;
	lastXPos = x;
	lastYPos = y;
	std::cout << xChange << " " << yChange << " " << std::endl;
}
