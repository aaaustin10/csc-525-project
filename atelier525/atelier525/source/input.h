#ifndef INPUT_H
	#define INPUT_H

	class input
	{
		public:
			static void consolidated_keyboard(int key, int x, int y, bool is_down);
			static void handle_normal_keyboard_down(unsigned char key, int x, int y);
			static void handle_normal_keyboard_up(unsigned char key, int x, int y);
			static void handle_special_keyboard_down(int key, int x, int y);
			static void handle_special_keyboard_up(int key, int x, int y);
			static void handle_mouse(int button, int state, int x, int y);
			static void init();
	};
#endif // INPUT_H