#include "includes.h"
#include "keycodes.h"

Player* p;
bool pause = false;
bool help = true;
bool wasdLogger[4];

bool input::isPaused(){
	return pause;
}

bool input::isHelp(){
	return help;
}

bool* input::getWASD(){
	return wasdLogger;
}

void input::setPlayer(Player& player){
	p = &player;
}

void input::consolidated_keyboard(int key, int x, int y, bool down_event)
{
	switch (key)
	{
	case 'p':
		if (down_event){
			pause = !pause;
			std::cout << ((pause) ? "Paused" : "Resumed") << std::endl;
			for (int i = 0; i < 5; i++){
				p->dir[i] = false;
			}
		}
		if (!pause){
			int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
			int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
			glutWarpPointer(centerX, centerY);
			
		}
		break;
	case 'w':
		if (!pause){
			p->dir[0] = down_event;
		}
		break;
	case 'a':
		if (!pause){
			p->dir[1] = down_event;
		}
		break;
	case 's':
		if (!pause){
			p->dir[2] = down_event;
		}
		break;
	case 'd':
		if (!pause){
			p->dir[3] = down_event;
		}
		break;
	case ' ':
		if (!pause){
			p->dir[4] = down_event;
		}
		break;
	case 'h':
		if (down_event){
			help = !help;
		}
		break;
	case 27:
		exit(0);
		break;
	/*case '@' | KEY_SHIFT:
		std::cout << "You pressed shift and @" << std::endl;
		break;
	case '2':
		std::cout << "You pressed 2" << std::endl;
		break;
	case 'A' | KEY_SHIFT:
		std::cout << "You pressed shift and A" << std::endl;
		break;
	case KEY_UP_ARROW:
		std::cout << "You pressed up arrow" << std::endl;
		break;
	case KEY_CONTROL | 'a':
		std::cout << "You pressed ctrl and a" << std::endl;
		break;
	case KEY_ALTERNATE | 'a':
		std::cout << "You pressed alt and a" << std::endl;
		break;
	case KEY_ALTERNATE | KEY_SHIFT | '@':
		std::cout << "You pressed alt and 2" << std::endl;*/
	}
	//std::cout << key << " " << (int)key << " " << x << " " << y << std::endl;

	
}

int normal_transform(int key)
{
	int modifiers = glutGetModifiers() << ((sizeof(int) * 8) - 3);
	key |= modifiers;
	if (modifiers & KEY_CONTROL)
	{
		key += 96;
	}
	return key;
}

void input::handle_normal_keyboard_down(unsigned char key, int x, int y)
{
	consolidated_keyboard(normal_transform(key), x, y, true);
}

void input::handle_normal_keyboard_up(unsigned char key, int x, int y)
{
	consolidated_keyboard(normal_transform(key), x, y, false);
}

void input::handle_special_keyboard_down(int key, int x, int y)
{
	key |= KEY_CLASS_SPECIAL;
	consolidated_keyboard(key, x, y, true);
}

void input::handle_special_keyboard_up(int key, int x, int y)
{
	key |= KEY_CLASS_SPECIAL;
	consolidated_keyboard(key, x, y, false);
}

void input::handle_mouse(int button, int state, int x, int y)
{
	std::cout << button << " " << state << " " << x << " " << y << std::endl;
}

void input::handle_mouse_movement(int x, int y)
{
	static bool ignore = false;
	if (!pause){
		if (!ignore){
			int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
			int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
			//std::cout << x << ", " << y << std::endl;
			if (x == centerX && y == centerY){
				return;
			}
			int xChange = x - centerX;
			int yChange = centerY - y;
			p->addYaw(xChange / 3.0f);
			p->addPitch(yChange / 5.0f);
			//std::cout << xChange << " " << yChange << " " << std::endl;

			//glutPostRedisplay();
			glutWarpPointer(centerX, centerY);
			ignore = true;
			return;
		}
		ignore = false;
	}
}

void input::init()
{
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(input::handle_normal_keyboard_down);
	glutKeyboardUpFunc(input::handle_normal_keyboard_up);
	glutSpecialFunc(input::handle_special_keyboard_down);
	glutSpecialUpFunc(input::handle_special_keyboard_up);
	glutMouseFunc(input::handle_mouse);
	glutPassiveMotionFunc(input::handle_mouse_movement);

	int centerX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	int centerY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	glutWarpPointer(centerX, centerY);
}