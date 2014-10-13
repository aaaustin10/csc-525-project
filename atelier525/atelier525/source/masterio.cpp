#include "includes.h"


MasterIO::MasterIO()
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

void MasterIO::handle_mouse_movement(int x, int y, Player *p)
{
	int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	std::cout << x << ", " << y << std::endl;
	if (x == centerX && y == centerY){
		return;
	}
	int xChange = x - centerX;
	int yChange = centerY - y;
	p->addYaw(xChange/3.0f);
	p->addPitch(yChange/5.0f);
	std::cout << xChange << " " << yChange << " " << std::endl;
	glutPostRedisplay();
	glutWarpPointer(centerX, centerY);
}
