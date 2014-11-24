#include "includes.h"
Player player;
Camera camera;
float speed = 2.5f; // meters per second
GLbyte autumn[512][512][3];
static GLuint texName;

std::chrono::time_point<std::chrono::system_clock> start, end;
std::chrono::duration<double> frameTime; // frametime.count() within tick() or render_frame() will get time per tick in seconds


void render_frame(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	camera.apply();

	glBegin(GL_QUADS);
	{
		// front wall
		glColor3f(1, 1, 0.6); // Dark Blue Square
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

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glBindTexture(GL_TEXTURE_2D, texName);
	glBegin(GL_QUADS);
		glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);
		glTexCoord3f(-1.0, 1.0f, 1.0f); glVertex3f(-1.0, 1.0f, 1.0f);
		glTexCoord3f(-1.0f, -1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
		glTexCoord3f(1.0f, -1.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
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


	// player default position 0, 0, 0,
	input::setPlayer(player);
	camera.attachTo(player);


	FileReader file_autumn("../atelier525/source/autumn.dat");
	if (!file_autumn.init())
	{
		std::cout << "Could not open file." << std::endl;
		exit(0);
	}
	file_autumn.get_array(autumn, 512 * 512 * 3 * sizeof(GLbyte));

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(1, &texName);
	glBindTexture(GL_TEXTURE_2D, texName);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 512,
		512, 0, GL_RGB, GL_UNSIGNED_BYTE,
		autumn);
	
	glShadeModel(GL_SMOOTH);                            // Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);                // black Background
	glClearDepth(1.0f);                                    // Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
	glDepthFunc(GL_LEQUAL);                                // The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);    // Really Nice Perspective Calculations
}

void tick(void){
	end = std::chrono::system_clock::now();
	frameTime = end - start;

	if (frameTime.count() < 0.01){
		return;
	}
	start = std::chrono::system_clock::now();
	

	static float vAcc = 0;
	static bool grounded = true;


	player.setDist(frameTime.count() * speed);
	bool* wasd = input::getWASD();
	//if forward and not backward go forward, if left or right pressed but not both or neither strafe
	if (wasd[0]){
		if (!wasd[2]){
			if (wasd[1] != wasd[3]){
				player.setDist(player.getDist() / 2);
			}
			player.goForward();
		}
	}
	if (wasd[2]){
		if (!wasd[0]){
			if (wasd[1] != wasd[3]){
				player.setDist(player.getDist() / 2);
			}
			player.goBackward();
		}
	}
	if (wasd[1]){
		if (!wasd[3]){
			player.goLeft();
		}
	}
		
	if (wasd[3]){
		if (!wasd[1]){
			player.goRight();
		}
	}
	
	render_frame();
	
	
}

int main(int argc, char **argv)
{
	// window init
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Atelier");

	myInit();

	input::init();

	
	start = std::chrono::system_clock::now();


	glutReshapeFunc(resize);
	glutDisplayFunc(render_frame);
	glutIdleFunc(tick);
    glutMainLoop();

    return 0;
}