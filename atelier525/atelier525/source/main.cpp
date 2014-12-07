#include "includes.h"
Player player;
Camera camera;
float speed = 5.0f; // meters per second
GLbyte autumn[512][512][3];
static GLuint texName;

std::chrono::time_point<std::chrono::system_clock> start, end;
std::chrono::duration<double> frameTime; // frametime.count() within tick() or render_frame() will get time per tick in seconds

rendering renderer;

void render_frame(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	camera.apply();

	renderer.draw();
	renderer.grid();

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

	std::string path;
	const int max_path_size = 1000;
	char buf[max_path_size];
	if (GetCurrentDirectoryA(max_path_size, buf) == 0)
	{
		std::cout << "Getting the current directory failed maybe max_path is too small?" << std::endl;
	}
	path.append(buf);
	path.append("\\data\\");
	SetCurrentDirectoryA(path.c_str());
	renderer.read_obj("scene.obj");

	// player default position 0, 0, 0,
	input::setPlayer(player);
	camera.attachTo(player);

	player.setSpeed(speed);

	SetCurrentDirectoryA(buf); // this needs to be addressed
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
	

	player.move(frameTime.count());

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