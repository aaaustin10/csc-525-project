#ifndef MASTERIO_H
#define MASTERIO_H
class Player;
class MasterIO
{
public:
	MasterIO();
	~MasterIO();
	void handle_normal_keyboard_down(unsigned char key, int x, int y);
	void handle_normal_keyboard_up(unsigned char key, int x, int y);
	void handle_special_keyboard_down(int key, int x, int y);
	void handle_special_keyboard_up(int key, int x, int y);

	void handle_mouse(int button, int state, int x, int y);
	void handle_mouse_movement(int x, int y, Player* p);

private:
	int lastXPos, lastYPos;

};

#endif