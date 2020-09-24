#include <Windows.h>
#include <GL/gl.h>
#include <glut.h>

float rotation = 0.0;

void custominitialize(void) {
	//Set clear background color (rgba)
	//RGB 0 to 1
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//Set shading model to use
	glShadeModel(GL_SMOOTH);

	//DEFIN MATERIAL PROPERTIES (for objects in scene)
	GLfloat mat_spec[] = { 0.393548, 0.271906, 0.166721, 1.0};
	GLfloat mat_shiny[] = { 0.2 };
	GLfloat mat_amb[] = { 0.2125, 0.1275, 0.054, 1.0};
	GLfloat mat_dif[] = { 0.714, 0.4284, 0.18144, 1.0 };


	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiny);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);

	//DEFINE LIFHT PROPERTIES (for lights in scene)
	GLfloat while_light[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = { 1.0, 1.0, 1.0, 0.0 };

	//SET LIGHT PROPERTIES
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, while_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, while_light);

	//Activate (enable) lights
	glEnable(GL_LIGHT0);

	//Enable lighting
	glEnable(GL_LIGHTING);

	//Enable depth testing (for hidden surface removal)
	glEnable(GL_DEPTH_TEST);
}

void Aries() {
	glDisable(GL_LIGHTING);
	glPushMatrix();
		glColor3f(0.760, 0.039, 0.098);
		//LEFT
		glTranslated(-2.5, 0.0, 0.0);
		glPushMatrix();
			glRotated(15, 0.0, 0.0, 1.0);
			glScaled(0.25, 0.5, 0.2);
			glutSolidCube(1.0);
		glPopMatrix();

		glTranslated(-0.025, 0.4, 0.0);
		glPushMatrix();
			glRotated(-10, 0.0, 0.0, 1.0);
			glScaled(0.25, 0.5, 0.2);
			glutSolidCube(1.0);
		glPopMatrix();

		glTranslated(0.135, 0.4, 0.0);
		glPushMatrix();
			glRotated(-35, 0.0, 0.0, 1.0);
			glScaled(0.25, 0.5, 0.2);
			glutSolidCube(1.0);
		glPopMatrix();

		glTranslated(0.3, 0.2, 0.0);
		glPushMatrix();
			glRotated(-85, 0.0, 0.0, 1.0);
			glScaled(0.25, 0.5, 0.2);
			glutSolidCube(1.0);
		glPopMatrix();

		glTranslated(0.3, -0.10, 0.0);
		glPushMatrix();
			glRotated(45, 0.0, 0.0, 1.0);
			glScaled(0.25, 0.5, 0.2);
			glutSolidCube(1.0);
		glPopMatrix();

		glTranslated(0.25, -0.35, 0.0);
		glPushMatrix();
			glRotated(20, 0.0, 0.0, 1.0);
			glScaled(0.25, 0.5, 0.2);
			glutSolidCube(1.0);
		glPopMatrix();

		glTranslated(0.175, -1.35, 0.0);
		glPushMatrix();
			glRotated(5, 0.0, 0.0, 1.0);
			glScaled(0.25, 2.5, 0.2);
			glutSolidCube(1.0);
		glPopMatrix();

	//RIGHT

					 //x //y //z
		glTranslated(0.2, 0.0, 0.0);
		glPushMatrix();
			glRotated(-5, 0.0, 0.0, 1.0);
			glScaled(0.25, 2.5, 0.2);
			glutSolidCube(1.0);
		glPopMatrix();

		glTranslated(0.16, 1.35, 0.0);
		glPushMatrix();
			glRotated(-20, 0.0, 0.0, 1.0);
			glScaled(0.25, 0.5, 0.2);
			glutSolidCube(1.0);
		glPopMatrix();

		glTranslated(0.2, 0.30, 0.0);
		glPushMatrix();
			glRotated(-50, 0.0, 0.0, 1.0);
			glScaled(0.25, 0.5, 0.2);
			glutSolidCube(1.0);
		glPopMatrix();

		glTranslated(0.325, 0.14, 0.0);
		glPushMatrix();
			glRotated(95, 0.0, 0.0, 1.0);
			glScaled(0.25, 0.5, 0.2);
			glutSolidCube(1.0);
		glPopMatrix();

		glTranslated(0.26, -0.15, 0.0);
		glPushMatrix();
			glRotated(35, 0.0, 0.0, 1.0);
			glScaled(0.25, 0.5, 0.2);
			glutSolidCube(1.0);
		glPopMatrix();

		glTranslated(0.15, -0.4, 0.0);
		glPushMatrix();
			glRotated(8, 0.0, 0.0, 1.0);
			glScaled(0.25, 0.5, 0.2);
			glutSolidCube(1.0);
		glPopMatrix();

		glTranslated(-0.025, -0.35, 0.0);
		glPushMatrix();
			glRotated(-15, 0.0, 0.0, 1.0);
			glScaled(0.25, 0.5, 0.2);
			glutSolidCube(1.0);
		glPopMatrix();

	glPopMatrix();
	glEnable(GL_LIGHTING);
}

void Tauro() {
	glPushMatrix();
	glutSolidSphere(0.5, 50, 50);
	glPopMatrix();
}

void display(void) {
	//clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glRotated(rotation, 0.0, 1.0, 0.0);
	Tauro();
	//Aries();
	glutSwapBuffers();
}

void reshape(int _widht, int _height) {
	//Set the viewport size, based on function input

	glViewport(0, 0, (GLsizei)_widht, (GLsizei)_height);

	//Set the projction matrix based on input size
	glMatrixMode(GL_PROJECTION);
	//first set as identity
	glLoadIdentity();
	//then set perspective projection parmeters based on aspect ratio
	gluPerspective(20.0, (GLfloat)_widht / (GLfloat)_height, 0.10, 60.0);

	//Set the model view matrix to identity
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Set the "look at" point - where the "camera" is and where it is "pointed"
	gluLookAt(0.0, 0.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 's':
		rotation += 0.5;
		break;
	case 'S':
		rotation -= 0.5;
		break;
	case 27:
		exit(0);
		break;
	}
}

int main(int argc, char** argv) {
	//GLUT INITIALIZATION
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL Teapot");

	//Additional initialization
	custominitialize();

	//Register callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(display);

	//Do main loop
	glutMainLoop();

	//Exit
	return 0;
}