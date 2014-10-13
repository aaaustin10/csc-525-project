#ifndef KEYCODES_H
	#define KEYCODES_H

	#define KEY_BACKSPACE 8
	#define KEY_RETURN 13
	#define KEY_ESCAPE 27
	#define KEY_DELETE 127

	// bit masks
	#define KEY_ALTERNATE 0x80000000
	#define KEY_CONTROL 0x40000000
	#define KEY_SHIFT 0x20000000
	#define ANY_MODIFYER_KEY 0xe0000000

	// All the special keys have the
	// KEY_CLASS_SPECIAL value added to the glut default
	// this is for simplicity in detection
	#define KEY_CLASS_SPECIAL 0x10000000
	#define KEY_F1 0x10000001
	#define KEY_F2 0x10000002
	#define KEY_F3 0x10000003
	#define KEY_F4 0x10000004
	#define KEY_F5 0x10000005
	#define KEY_F6 0x10000006
	#define KEY_F7 0x10000007
	#define KEY_F8 0x10000008
	#define KEY_F9 0x10000009
	#define KEY_F10 0x1000000a
	#define KEY_F11 0x1000000b
	#define KEY_F12 0x1000000c
	#define KEY_LEFT_ARROW 0x10000064
	#define KEY_UP_ARROW 0x10000065
	#define KEY_RIGHT_ARROW 0x10000066
	#define KEY_DOWN_ARROW 0x10000067
	#define KEY_PAGE_UP 0x10000068
	#define KEY_PAGE_DOWN 0x10000069
	#define KEY_HOME 0x1000006a
	#define KEY_END 0x1000006b
	#define KEY_INSERT 0x1000006c
#endif //KEYCODES_H