#include <windows.h>
#include <GL/gl.h>
#include <glut.h>
#include "planet.h"
#include "Moon.h"
#include "Disk.h"

static float year = 0.0f, day = 0.0f, yearinc = 0.05f, dayinc = 0.25f;
static bool doAuto = false;

//First 9 belongs to planets and the rest for the moons

float dayP[9];
float offsetDay[9] = { 0.5, 0.125, 0.07, 0.04, 0.035, 0.007, 0.0004 };
float offsetYear[9] = { 
	0.09, 
	0.08, 
	0.07, 
	0.06, 
	0.05, 
	0.04, 
	0.03, 
	0.025, 
	0.015
};
float yearP[9];
float moonDays[13];
float moonYears[13];

float moonDaysOffset[13] = {
	0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 0.2, 0.8
};

float moonYearOffset[13] = {
	0.5, 0.7, 0.8, 0.6, 0.48, 0.75, 0.45, 0.5, 0.48, 0.67, 0.72, 0.52, 0.45
};

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glDisable(GL_LIGHTNING);
	//begin solar system
	glEnable(GL_LIGHTING);
	glDisable(GL_LIGHTING);


	////Draw Stars
	//for (int i = 0; i < 300; i++) {
	//	glColor3f(1.0, 1.0, 1.0);
	//	glPointSize(3.0);
	//	glBegin(GL_POINTS);
	//		glVertex2f(static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 50)), static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 50)));
	//	glEnd();
	//}


	//Draw Sun
	planet sun(0,1.0, 0);
		sun.SetColor(0.921, 0.768, 0.278);
		sun.SetTranslate(0.0, 0.0, 0.0);
		sun.SetRotations(dayP[0], yearP[0]);
		sun.Draw();

    // mercury Planet 1
    glPushMatrix();
		planet mercury(1, 0.6, 0);
		mercury.SetColor(0.6, 0.423, 0.423);
		mercury.SetRotations(dayP[1], yearP[1]);
		mercury.SetTranslate(2.5, 0.0, 0.0);
		mercury.Draw();

		//Disk
		Disk diskMercury(0.0, 0.0, 0.0);
			diskMercury.SetColor(0.576, 0.121, 0.133);
			diskMercury.SetRotations(90, 1.0, 0.0, 0.0);
			diskMercury.SetDime(0.1, 0.1, 0.1);
			diskMercury.SetRadius(0.5, 26);
			diskMercury.Draw();

	glPopMatrix();

	// Venus 2
	glPushMatrix();
		planet venus(2, 1.0, 1);
		venus.SetColor(0.796, 0.062, 0.062);
		venus.SetRotations(dayP[2], yearP[2]);
		venus.SetTranslate(4.5, 0.0, 0.0);
		//Moons
		venus.SetMoonColor(0.737, 0.662, 0.662);
		venus.SetMoonRotation(0.0, 1.0, 0.0);
		venus.SetMoonSpecs(0.4, 1.5, 0.0, 0.0, 0);
		venus.Draw(moonYears, moonDays);
		//Disk
		Disk diskVenus(0.0, 0.0, 0.0);
			diskVenus.SetColor(0.576, 0.121, 0.133);
			diskVenus.SetRotations(90, 1.0, 0.0, 0.0);
			diskVenus.SetDime(0.1, 0.1, 0.1);
			diskVenus.SetRadius(0.5, 45);
			diskVenus.Draw();

	glPopMatrix();


	// EARTH 3
	glPushMatrix();
		planet earth(3, 0.8, 0);
		earth.SetColor(0.062, 0.352, 0.796);
		earth.SetRotations(dayP[3], yearP[3]);
		earth.SetTranslate(6.5, 0.0, 0.0);
		earth.Draw();
	//Disk
		Disk diskEarth(0.0, 0.0, 0.0);
		diskEarth.SetColor(0.576, 0.121, 0.133);
		diskEarth.SetRotations(90, 1.0, 0.0, 0.0);
		diskEarth.SetDime(0.1, 0.1, 0.1);
		diskEarth.SetRadius(0.5, 65);
		diskEarth.Draw();
	glPopMatrix();

	//Marte 4
	glPushMatrix();
		planet marte(4, 0.75, 2);
		marte.SetColor(0.749, 0.094, 0.094);
		marte.SetRotations(dayP[4], yearP[4]);
		marte.SetTranslate(8.6, 0.0, 0.0);
		//Moons
		marte.SetMoonColor(0.737, 0.662, 0.662);
		marte.SetMoonRotation(0.0, 1.0, 0.0);
		marte.SetMoonSpecs(0.4, 1.5, 0.0, 0.0, 1);
		marte.Draw(moonYears, moonDays);

	//Disk
	Disk diskMarte(0.0, 0.0, 0.0);
		diskMarte.SetColor(0.576, 0.121, 0.133);
		diskMarte.SetRotations(90, 1.0, 0.0, 0.0);
		diskMarte.SetDime(0.1, 0.1, 0.1);
		diskMarte.SetRadius(0.5, 85);
		diskMarte.Draw();
	glPopMatrix();

	//Jupiter 5
	glPushMatrix();
		planet jupiter(5, 2.5, 5);
		jupiter.SetColor(0.894, 0.694, 0.545);
		jupiter.SetRotations(dayP[5], yearP[5]);
		jupiter.SetTranslate(12.5, 0.0, 0.0);
		//Moons
		jupiter.SetMoonColor(0.737, 0.662, 0.662);
		jupiter.SetMoonRotation(0.0, 1.0, 0.0);
		jupiter.SetMoonSpecs(0.4, 4.5, 0.0, 0.0, 2);
		jupiter.Draw(moonYears, moonDays);

	//Disk
	Disk diskJupiter(0.0, 0.0, 0.0);
		diskJupiter.SetColor(0.576, 0.121, 0.133);
		diskJupiter.SetRotations(90, 1.0, 0.0, 0.0);
		diskJupiter.SetDime(0.1, 0.1, 0.1);
		diskJupiter.SetRadius(0.5, 125);
		diskJupiter.Draw();
	glPopMatrix();

	//Jupiter 6
	glPushMatrix();
		planet saturn(6, 2, 2);
		saturn.SetColor(0.776, 0.705, 0.482);
		saturn.SetRotations(dayP[6], yearP[6]);
		saturn.SetTranslate(17.5, 0.0, 0.0);
		//Disk
		saturn.SetDisk(0.0, 0, 0);
		saturn.SetDiskColor(0.576, 0.121, 0.133);
		saturn.SetDiskRotation(45, 0.5, 0.5, 0.0);
		saturn.SetDime(0.1, 0.1, 0.1);
		saturn.SetRadius(0.5, 30);
		//Moons
		saturn.SetMoonColor(0.737, 0.662, 0.662);
		saturn.SetMoonRotation(0.0, 1.0, 0.0);
		saturn.SetMoonSpecs(0.4, 3.5, 0.0, 0.0, 7);
		saturn.Draw(moonYears, moonDays);

	//Disk
	Disk diskSaturn(0.0, 0.0, 0.0);
		diskSaturn.SetColor(0.576, 0.121, 0.133);
		diskSaturn.SetRotations(90, 1.0, 0.0, 0.0);
		diskSaturn.SetDime(0.1, 0.1, 0.1);
		diskSaturn.SetRadius(0.5, 180);
		diskSaturn.Draw();

	glPopMatrix();

	//Jupiter 7
	glPushMatrix();
		planet uranus(7, 1.2, 2);
		uranus.SetColor(0.482, 0.752, 0.776);
		uranus.SetRotations(dayP[7], yearP[7]);
		uranus.SetTranslate(21.5, 0.0, 0.0);
		//Moons
		uranus.SetMoonColor(0.737, 0.662, 0.662);
		uranus.SetMoonRotation(0.2, 1.0, 0.0);
		uranus.SetMoonSpecs(0.4, 2.5, 0.0, 0.0, 9);
		uranus.Draw(moonYears, moonDays);
	//Disk
	Disk diskUranus(0.0, 0.0, 0.0);
		diskUranus.SetColor(0.576, 0.121, 0.133);
		diskUranus.SetRotations(90, 1.0, 0.0, 0.0);
		diskUranus.SetDime(0.1, 0.1, 0.1);
		diskUranus.SetRadius(0.5, 220);
		diskUranus.Draw();

	glPopMatrix();

	//Neptune 8
	glPushMatrix();
		planet neptune(8, 0.8, 1);
		neptune.SetColor(0.101, 0.537, 0.576);
		neptune.SetRotations(dayP[8], yearP[8]);
		neptune.SetTranslate(24.5, 0.0, 0.0);
		//Moon
		neptune.SetMoonColor(0.737, 0.662, 0.662);
		neptune.SetMoonRotation(0.2, 1.0, 0.0);
		neptune.SetMoonSpecs(0.4, 2.5, 0.0, 0.0, 12);
		neptune.Draw(moonYears, moonDays);
	//Disk
	Disk diskNeptune(0.0, 0.0, 0.0);
		diskNeptune.SetColor(0.576, 0.121, 0.133);
		diskNeptune.SetRotations(90, 1.0, 0.0, 0.0);
		diskNeptune.SetDime(0.1, 0.1, 0.1);
		diskNeptune.SetRadius(0.5, 245);
		diskNeptune.Draw();
	glPopMatrix();

	glPopMatrix();

	glutSwapBuffers();

	// Code for automatic movement of planet
	for (int i = 0; i < 22; i++) {
		if (i < 9) {
			yearinc = offsetYear[i];
			dayinc = offsetDay[i];
			day = dayP[i];
			year = yearP[i];
		}
		else {
			yearinc = moonYearOffset[i - 9];
			dayinc = moonDaysOffset[i - 9];
			day = moonDays[i - 9];
			year = moonYears[i - 9];
		}

		if (doAuto) {
			year = (GLfloat)(((GLint)(year * 100.f + yearinc * 100.f)) % 36000) / 100.0f;
			day = (GLfloat)(((GLint)(day * 100.f + dayinc * 100.f)) % 36000) / 100.0f;
		}

		if (i < 9) {
			yearP[i] = year;
			dayP[i] = day;
		}
		else {
			moonYears[i - 9] = year;
			moonDays[i - 9] = day;
		}
	}
}

void reshape(int w, int h)
{
	glViewport( 0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 60.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(20.0, 25.0, 5.0, 0.0, 0.0, 0.0, 0.0, 2.0, 0.0);

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

		// Manual control of day and year movement
		case 'd':
		case 'D':
			day = (GLfloat)((GLint)(day + 1.0f) % 360);
			glutPostRedisplay();
			break;
		case 'y':
		case 'Y':
			year = (GLfloat)((GLint)(year + 5.0f) % 360);
			glutPostRedisplay();
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
			yearinc = yearinc + 0.1f;
		// Make the day move faster
		else if (btn == GLUT_RIGHT_BUTTON)
			dayinc = dayinc + 0.1f;
		// If middle button, then set increment to 0
		else {
			yearinc = 0.0f;
			dayinc = 0.0f;
		}

		glutPostRedisplay();
	}
}

int main (int argc, char** argv)
{
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
