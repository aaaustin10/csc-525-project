#include "includes.h"
#include "keycodes.h"

void input::consolidated_keyboard(int key, int x, int y, bool down_event)
{
	switch (key)
	{
	case '@' | KEY_SHIFT:
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
		std::cout << "You pressed alt and 2" << std::endl;
	}
	std::cout << key << " " << (int)key << " " << x << " " << y << std::endl;
}

int normal_transform(int key)
{
	int modifiers = glutGetModifiers() << (sizeof(int) * 8) - 3;
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

void input::init()
{
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(input::handle_normal_keyboard_down);
	glutKeyboardUpFunc(input::handle_normal_keyboard_up);
	glutSpecialFunc(input::handle_special_keyboard_down);
	glutSpecialUpFunc(input::handle_special_keyboard_up);
	glutMouseFunc(input::handle_mouse);
}