#include <windows.h>
#include <GL/gl.h>
#include <glut.h>
#include <time.h>
#include <math.h>

///////////////////////////// MOON CLASS /////////////////////////////////////////////////
class Disk {
private:
	float year;
	float day;
	float yearInc;
	float dayInc;

	float initialX;
	float initialY;
	float initialZ;

	float space;

	static bool doAuto;

public:
	Disk();
	void DrawDisk();
	void ChangeInc(float);
	static void DoAuto(bool);
	void InitialPos(float, float, float);
	void Space(float);
};

Disk::Disk() {
	yearInc = 0.05f;
	dayInc = 0.25f;

	year = 0.0;
	day = 0.0;

	space = 0;

	initialX = 0;
	initialY = 0;
	initialZ = 0;
}

void Disk::DrawDisk() {
	glPushMatrix();
	glScaled(1.0, 0.01, 1.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	//glutWireTorus(0.15, 0.3, 10, 10);
	glutSolidTorus(.7, space + .3, 10, 30);
	glPopMatrix();
}

void Disk::ChangeInc(float _inc) {
	yearInc += _inc;
	dayInc += _inc;
}

void Disk::DoAuto(bool _doAuto) {
	doAuto = _doAuto;
}
bool Disk::doAuto = false;

void Disk::InitialPos(float _initialX, float _initialY, float _initialZ) {
	initialX = _initialX;
	initialY = _initialY;
	initialZ = _initialZ;
}

void Disk::Space(float _space) {
	space = _space;
}
////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////// MOON CLASS /////////////////////////////////////////////////
class Moon {
private:
	float year;
	float day;
	float yearInc;
	float dayInc;

	float initialX;
	float initialY;
	float initialZ;

	float space;

	static bool doAuto;
	static bool seeOrbits;

public:
	Moon();
	void DrawMoon();
	void ChangeInc(float);
	void InitialPos(float, float, float);
	void Space(float);
	static void DoAuto(bool);
	static void SeeOrbits(bool);
};

Moon::Moon() {
	yearInc = 0.1f;
	dayInc = 0.5f;

	year = 0.0;
	day = 0.0;

	space = 0;

	initialX = 0;
	initialY = 0;
	initialZ = 0;
}

void Moon::DrawMoon() {
	glPushMatrix();
	if (seeOrbits)
		glutWireTorus(space, 0.0, 40, 1);
	glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
	glTranslated(initialX, initialY, initialZ);
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0);
	glutSolidSphere(1.0, 50, 50);
	glPopMatrix();

	if (doAuto) {
		year = (GLfloat)(((GLint)(year * 100.f + yearInc * 100.f)) % 36000) / 100.0f;
		day = (GLfloat)(((GLint)(day * 100.f + dayInc * 100.f)) % 36000) / 100.0f;
	}
}

void Moon::ChangeInc(float _inc) {
	yearInc += _inc;
	dayInc += _inc;
}

void Moon::DoAuto(bool _doAuto) {
	doAuto = _doAuto;
}
bool Moon::doAuto = false;

void Moon::SeeOrbits(bool _seeOrbits) {
	seeOrbits = _seeOrbits;
}
bool Moon::seeOrbits = false;

void Moon::InitialPos(float _initialX, float _initialY, float _initialZ) {
	initialX = _initialX;
	initialY = _initialY;
	initialZ = _initialZ;
}

void Moon::Space(float _space) {
	space = _space;
}
////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////// PLANET CLASS /////////////////////////////////////////////////
class Planet {
private:
	float year;
	float day;
	float yearInc;
	float dayInc;

	float size;
	int moonCount;
	int diskCount;

	static bool doAuto;
	static bool seeOrbits;

	Moon* moons;
	Disk* disks;

public:
	Planet();
	Planet(int, int, float, float, float);
	void DrawPlanet(float, float, float);
	void ChangeInc(float);
	void Axes();
	static void DoAuto(bool);
	static void SeeOrbits(bool);
};

Planet::Planet() {
	moonCount = 0;
	diskCount = 0;
	size = 1;

	year = 0.0;
	day = 0.0;

	yearInc = 0.05f;
	dayInc = 0.25f;

	moons = NULL;
	disks = NULL;
}

Planet::Planet(int _moons, int _disks, float _size, float _yearInc, float _dayInc) {
	moonCount = _moons;
	diskCount = _disks;
	size = _size;

	yearInc = _yearInc;
	dayInc = _dayInc;

	year = 0.0;
	day = 0.0;

	moons = new Moon[_moons];
	disks = new Disk[_disks];

	for (int i = 0; i < moonCount; i++) {
		float space = size + 5;
		float tempX = space, tempY = 0.0f, tempZ = 0.0f;

		moons[i].Space(space);

		float random;

		switch (i)
		{
		case 0:
			random = rand() % 72;
			break;
		case 1:
			random = 220 + rand() % 72;
			break;
		case 2:
			random = 76 + rand() % 72;
			break;
		case 3:
			random = 292 + rand() % 72;
			break;
		case 4:
			random = 148 + rand() % 72;
			break;

		default:
			random = 0.0f;
			break;
		}

		tempX = cos(random) * space;
		tempZ = sin(random) * space;
		moons[i].InitialPos(tempX, tempY, tempZ);
	}
}

void Planet::DrawPlanet(float space, float x, float z) {

	glPushMatrix();
	if (seeOrbits)
		glutWireTorus(space, 0.0, 40, 1);
	//Rotate on the sun
	glRotatef((GLfloat)year, 0.0, 1.0, 0.0);
	glTranslated(x, 0.0, z);

	for (int i = 0; i < moonCount; i++) {
		glPushMatrix();
		glTranslated(0.0, 0.0, 0.0);
		glScaled(0.5, 0.5, 0.5);
		moons[i].DrawMoon();
		glPopMatrix();
	}

	//Rotate on itself
	glRotatef((GLfloat)day, 0.0, 1.0, 0.0);

	if (seeOrbits)
		Axes();
	glutSolidSphere(size, 40, 40);

	for (int i = 0; i < diskCount; i++) {
		glColor3f(0.6, 0.6, 0.6);
		disks[i].Space(size + 1 + i);
		disks[i].DrawDisk();
	}

	glPopMatrix();

	moons->DoAuto(doAuto);
	moons->SeeOrbits(seeOrbits);

	if (doAuto) {
		year = (GLfloat)(((GLint)(year * 100.f + yearInc * 100.f)) % 36000) / 100.0f;
		day = (GLfloat)(((GLint)(day * 100.f + dayInc * 100.f)) % 36000) / 100.0f;
	}
}

void Planet::ChangeInc(float _inc) {
	yearInc += _inc;
	dayInc += _inc;
	for (int i = 0; i < moonCount; i++) {
		moons[i].ChangeInc(_inc);
	}
}

void Planet::Axes() {
	glBegin(GL_LINES);
	glVertex3f(-size * 2, 0.0, 0.0);
	glVertex3f(size * 2, 0.0, 0.0);
	glEnd();
}

void Planet::DoAuto(bool _doAuto) {
	doAuto = _doAuto;
}
bool Planet::doAuto = false;

void Planet::SeeOrbits(bool _seeOrbits) {
	seeOrbits = _seeOrbits;
}
bool Planet::seeOrbits = false;
////////////////////////////////////////////////////////////////////////////////////////////

					//    Separación	    Coordenas random
Planet planets[8];  //    con el sol	 sobre la circunferencia                       
float posInicial[8][3] = { {08.0,			0.0,		0.0},
							{11.0,			0.0,		0.0},
							{15.0,			0.0,		0.0},
							{19.0,			0.0,		0.0},
							{24.0,			0.0,		0.0},
							{31.0,			0.0,		0.0},
							{35.0,			0.0,		0.0},
							{39.0,			0.0,		0.0} };

static bool doAuto = false;
static bool seeOrbits = false;

//Asignar coordenadas random dentro de sus orbitas
void reColocar() {
	for (int planeta = 0; planeta < 8; planeta++) {
		float angulo = 1 + rand() % 360;
		posInicial[planeta][1] = cos(angulo) * posInicial[planeta][0];
		posInicial[planeta][2] = sin(angulo) * posInicial[planeta][0];
	}
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);

	planets[0] = Planet(0, 0, 0.6, 0.15f, 0.25f);
	planets[1] = Planet(1, 0, 1.0, 0.13f, 0.23f);
	planets[2] = Planet(0, 0, 0.8, 0.11f, 0.21f);
	planets[3] = Planet(2, 0, 0.75, 0.09f, 0.19f);
	planets[4] = Planet(5, 0, 2.5, 0.07f, 0.17f);
	planets[5] = Planet(2, 1, 2.0, 0.05f, 0.15f);
	planets[6] = Planet(2, 0, 1.2, 0.03f, 0.13f);
	planets[7] = Planet(1, 0, 0.8, 0.02f, 0.11f);

	reColocar();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glPushMatrix();
	glRotated(22.0, 0.0, 0.0, 1.0);
	glColor3f(1.0, 1.0, 0.0);
	glutSolidSphere(5.0, 40, 40);

	for (int i = 0; i < 8; i++) {
		switch (i) {
		case 0:
			glColor3f(1.0, 0.0, 0.0);
			break;
		case 1:
			glColor3f(1.0, 0.5, 0.0);
			break;
		case 2:
			glColor3f(0.69, 1.0, 1.0);
			break;
		case 3:
			glColor3f(0.3, 0.0, 0.0);
			break;
		case 4:
			glColor3f(0.76, 0.34, 0.19);
			break;
		case 5:
			glColor3f(0.95, 0.64, 0.37);
			break;
		case 6:
			glColor3f(0.21, 0.76, 1.0);
			break;
		case 7:
			glColor3f(0.0, 0.39, 0.56);
			break;
		}

		planets[i].DrawPlanet(posInicial[i][0], posInicial[i][1], posInicial[i][2]);
	}

	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 40.0, 55.0, 0.0, -9.0, 0.0, 0.0, 1.0, 1.0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':
	case 'A':
		// Toggle automatic movement of planet
		if (doAuto)
			doAuto = false;
		else
			doAuto = true;
		planets->DoAuto(doAuto);
		break;
	case 'r':
	case 'R':
		// Change the planets position
		reColocar();
		glutPostRedisplay();
		break;
		// Manual control of day and year movement
	case 's':
	case 'S':
		// Toggle visibility of the orbits
		if (seeOrbits)
			seeOrbits = false;
		else
			seeOrbits = true;
		planets->SeeOrbits(seeOrbits);
		break;
	case 0x1B:
	case 'q':
	case 'Q':
		exit(0);
		break;
	default:
		break;
	}
}

void mouse(int btn, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		// Make the year move faster
		if (btn == GLUT_LEFT_BUTTON)
			for (int i = 0; i < 8; i++)
				planets[i].ChangeInc(0.02);


		// Make the day move faster
		else if (btn == GLUT_RIGHT_BUTTON)
			for (int i = 0; i < 8; i++)
				planets[i].ChangeInc(-0.02);


		glutPostRedisplay();
	}
}

int main(int argc, char** argv)
{

	srand(time(NULL));

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Solar System Example");
	init();

	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);

	glutMainLoop();
	return 0;
}
