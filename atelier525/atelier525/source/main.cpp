#include "includes.h"

// start input.cpp //////////////////////////////////////////////
//void handle_normal_keyboard_down(unsigned char key, int x, int y);
//void handle_normal_keyboard_up(unsigned char key, int x, int y);
//void handle_special_keyboard_down(int key, int x, int y);
//void handle_special_keyboard_up(int key, int x, int y);
//void handle_mouse(int button, int state, int x, int y);
//void handle_mouse_movement(int x, int y);
// end input.cpp ////////////////////////////////////////////////

void render_frame(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glColor3f(0.2, 0.2, 0.6);
	glBegin(GL_TRIANGLES);
	{
		glVertex3f(-0.5, -0.5, 0.0);
		glVertex3f(0.5, 0.0, 0.0);
		glVertex3f(0.0, 0.5, 0.0);
	}
	glEnd();

	glutSwapBuffers();
}

int main(int argc, char **argv)
{
	// window init
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutCreateWindow("Atelier");

	// HI
	MasterIO mInOut = MasterIO();

	// keyboard handling
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(mInOut.handle_normal_keyboard_down);
	glutKeyboardUpFunc(mInOut.handle_normal_keyboard_up);
	glutSpecialFunc(mInOut.handle_special_keyboard_down);
	glutSpecialUpFunc(mInOut.handle_special_keyboard_up);

	glutMouseFunc(mInOut.handle_mouse);
	glutPassiveMotionFunc(mInOut.handle_mouse_movement);

	glutDisplayFunc(render_frame);

    glutMainLoop();

    return 0;
}