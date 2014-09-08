#include "includes.h"

void handle_normal_keyboard_down(unsigned char key, int x, int y)
{
	std::cout << key << " " << (int)key << " " << x << " " << y << " down" << std::endl;
}

void handle_normal_keyboard_up(unsigned char key, int x, int y)
{
	std::cout << key << " " << (int)key << " " << x << " " << y << " up" << std::endl;
}

void handle_special_keyboard_down(int key, int x, int y)
{
	std::cout << (int)key << " " << x << " " << y << std::endl;
}

void handle_special_keyboard_up(int key, int x, int y)
{
	std::cout << (int)key << " " << x << " " << y << std::endl;
}

void handle_mouse(int button, int state, int x, int y)
{
	std::cout << button << " " << state << " " << x << " " << y << std::endl;
}