#include "includes.h"

// start input.cpp //////////////////////////////////////////////
void handle_normal_keyboard_down(unsigned char key, int x, int y);
void handle_normal_keyboard_up(unsigned char key, int x, int y);
void handle_special_keyboard_down(int key, int x, int y);
void handle_special_keyboard_up(int key, int x, int y);
void handle_mouse(int button, int state, int x, int y);
// end input.cpp ////////////////////////////////////////////////

void render_frame(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glBegin(GL_QUADS);
	{
		// front wall
		glColor3f(0.2, 0.2, 0.6); // Dark Blue Square
		glVertex4f(-0.5, -0.5, 0.5, 1.0);
		glVertex4f(-0.5, 0.5, 0.5, 1.0);
		glVertex4f(0.5, 0.5, 0.5, 1.0);
		glVertex4f(0.5, -0.5, 0.5, 1.0);

		//right wall
		glColor3f(0.2, 0.6, 0.2); // Dark Green Square
		glVertex4f(0.5, 0.5, 0.5, 1.0);
		glVertex4f(0.5, 0.5, -0.5, 1.0);
		glVertex4f(0.5, -0.5, -0.5, 1.0);
		glVertex4f(0.5, -0.5, 0.5, 1.0);

		// back wall
		glColor3f(0.6, 0.2, 0.2); // Dark Red Square
		glVertex4f(0.5, 0.5, -0.5, 1.0);
		glVertex4f(-0.5, 0.5, -0.5, 1.0);
		glVertex4f(-0.5, -0.5, -0.5, 1.0);
		glVertex4f(0.5, -0.5, -0.5, 1.0);

		// left wall
		glColor3f(0.2, 0.6, 0.6); // Baby Blue Square
		glVertex4f(-0.5, -0.5, 0.5, 1.0);
		glVertex4f(-0.5, 0.5, 0.5, 1.0);
		glVertex4f(-0.5, 0.5, -0.5, 1.0);
		glVertex4f(-0.5, -0.5, -0.5, 1.0);

		// roof
		glColor3f(0.2, 0.2, 0.2); // grey Square
		glVertex4f(-0.5, 0.5, 0.5, 1.0);
		glVertex4f(-0.5, 0.5, -0.5, 1.0);
		glVertex4f(0.5, 0.5, -0.5, 1.0);
		glVertex4f(0.5, 0.5, 0.5, 1.0);

		// floor
		glColor3f(1.0, 1.0, 1.0); // White Square
		glVertex4f(-0.5, -0.5, 0.5, 1.0);
		glVertex4f(0.5, -0.5, 0.5, 1.0);
		glVertex4f(0.5, -0.5, -0.5, 1.0);
		glVertex4f(-0.5, -0.5, -0.5, 1.0);

	}
	glEnd();

	glFlush();
	glutSwapBuffers();
}

void resize(GLint x, GLint y){
	if (y == 0)                                        // Prevent A Divide By Zero By
	{
		y = 1;                                        // Making Height Equal One
	}

	glViewport(0, 0, x, y);                        // Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);                        // Select The Projection Matrix
	glLoadIdentity();                                    // Reset The Projection Matrix
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(100.0f, ((GLfloat)x / (GLfloat)y), 0.1f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);                            // Select The Modelview Matrix
	glLoadIdentity();                                    // Reset The Modelview Matrix
}

void myInit(){

	glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);                // black Background
	glClearDepth(1.0f);                                    // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);                                // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);    // Really Nice Perspective Calculations
}
int main(int argc, char **argv)
{
	// window init
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutCreateWindow("Atelier");

	
	myInit();

	// keyboard handling
	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(handle_normal_keyboard_down);
	glutKeyboardUpFunc(handle_normal_keyboard_up);
	glutSpecialFunc(handle_special_keyboard_down);
	glutSpecialUpFunc(handle_special_keyboard_up);

	glutMouseFunc(handle_mouse);

	glutReshapeFunc(resize);
	glutDisplayFunc(render_frame);

    glutMainLoop();

    return 0;
}