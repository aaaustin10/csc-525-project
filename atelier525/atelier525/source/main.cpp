#include "includes.h"
Player *player = (Player*) malloc(1);
Camera *camera = (Camera*) malloc(1);

void render_frame(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	camera->apply();

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


	
	player->setPosition(0.0f, 0.0f, 0.0f);

	
	camera->attachTo(player);
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

	input::init();

	glutReshapeFunc(resize);
	glutDisplayFunc(render_frame);
    glutMainLoop();

    return 0;
}