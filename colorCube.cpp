#include <Windows.h>
#include <GL/gl.h>
#include <glut.h>

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
	GLfloat mat_dif[] = { 0.5, 0.5, 0.5, 1.0 };


	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiny);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);

	//DEFINE LIFHT PROPERTIES (for lights in scene)
	GLfloat while_light[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_pos[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat light_pos_1[] = { -1.0, -1.0, 1.0, 0.0 };

	//SET LIGHT PROPERTIES
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, while_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, while_light);

	glLightfv(GL_LIGHT1, GL_POSITION, light_pos_1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, while_light);
	glLightfv(GL_LIGHT1, GL_SPECULAR, while_light);

	//Activate (enable) lights
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	//Enable lighting
	glEnable(GL_LIGHTING);

	//Enable depth testing (for hidden surface removal)
	glEnable(GL_DEPTH_TEST);
}

void CreateTriangle(float fposX, float fposY, float fposZ, float sposX, float sposY, float sposZ, float tposX, float tposY, float tposZ) {
	glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.2, 0.0);
		glVertex3f(fposX, fposY, fposZ);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(sposX, sposY, sposZ);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(tposX, tposY, tposZ);
	glEnd();
}

void CreateCube() {
	//bottom
					//fpz		 | spy           | tpx
	CreateTriangle(0, 0.0, 0.75, 0.75, 0.0, 0.0, 0, 0.0, 0);
	CreateTriangle(0, 0, 0.75, 0.75, 0, 0, 0.75, 0, 0.75);
	//leftSide
	CreateTriangle(0, 0, 0.75, 0, 0.75, 0, 0, 0, 0);
	CreateTriangle(0, 0, 0.75, 0, 0.75, 0, 0, 0.75, 0.75);

	//rightSide
	CreateTriangle(0.75, 0.75, 0, 0, 0.75, 0, 0, 0, 0);
	CreateTriangle(0.75, 0.75, 0, 0.75, 0, 0, 0, 0, 0);

	//top
	CreateTriangle(0.75, 0.75, 0.0, 0.0, 0.75, 0.75, 0.0, 0.75, 0.0);
	CreateTriangle(0.75, 0.75, 0.0, 0.0, 0.75, 0.75, 0.75, 0.75, 0.75);

	//rightFrontSide
	CreateTriangle(0.75, 0.75, 0.0, 0.75, 0.0, 0.75, 0.75, 0.0, 0.0);
	CreateTriangle(0.75, 0.75, 0.0, 0.75, 0.0, 0.75, 0.75, 0.75, 0.75);

	//leftFrontSide
	CreateTriangle(0.0, 0.0, 0.75, 0.0, 0.75, 0.75, 0.75, 0.75, 0.75);
	CreateTriangle(0.0, 0.0, 0.75, 0.75, 0.0, 0.75, 0.75, 0.75, 0.75);
}

void CreateRectangle() {
	//buttom
	CreateTriangle(0.0, 0.0, 0.75, 0.75, 0.0, 0.0, 0.0, 0.0, 0.0);
	CreateTriangle(0.0, 0.0, 0.75, 0.75, 0.0, 0.0, 0.75, 0.0, 0.75);
	//leftSide
	CreateTriangle(0.0, 0.0, 0.75, 0.0, 1.75, 0.0, 0.0, 0.0, 0.0);
	CreateTriangle(0.0, 0.0, 0.75, 0.0, 1.75, 0.0, 0.0, 1.75, 0.75);

	//rightSide
	CreateTriangle(0.75, 1.75, 0.0, 0.0, 0.75, 0.0, 0.0, 0.0, 0.0);
	CreateTriangle(0.75, 1.75, 0.0, 0.75, 0.0, 0.0, 0.0, 0.0, 0.0);

	//top
	CreateTriangle(0.75, 1.75, 0.0, 0.0, 1.75, 0.75, 0.0, 1.75, 0.0);
	CreateTriangle(0.75, 1.75, 0.0, 0.0, 1.75, 0.75, 0.75, 1.75, 0.75);

	//rightFrontSide
	CreateTriangle(0.75, 1.75, 0.0, 0.75, 0.0, 0.75, 0.75, 0.0, 0.0);
	CreateTriangle(0.75, 1.75, 0.0, 0.75, 0.0, 0.75, 0.75, 1.75, 0.75);

	//leftFrontSide
	CreateTriangle(0.0, 0.0, 0.75, 0.0, 1.75, 0.75, 0.75, 1.75, 0.75);
	CreateTriangle(0.0, 0.0, 0.75, 0.75, 0.0, 0.75, 0.75, 1.75, 0.75);
}

void Cilinder(float _offset) {
	//buttom
	CreateTriangle(0.0, 0.0, 0.75, 0.75, 0.0, 0.0, 0.0, 0.0, 0.0);
	CreateTriangle(0.0, 0.0, 0.75, 0.75, 0.0, 0.0, 0.75, 0.0, 0.75);
	//leftSide
	CreateTriangle(0.0, 0.0, 0.75, 0.0, 1.75, 0.0, 0.0, 0.0, 0.0);
	CreateTriangle(0.0, 0.0, 0.75, 0.0, 1.75, 0.0, 0.0, 1.75, 0.75);

	//rightSide
	CreateTriangle(0.75, 1.75, 0.0, 0.0, 0.75, 0.0, 0.0, 0.0, 0.0);
	CreateTriangle(0.75, 1.75, 0.0, 0.75, 0.0, 0.0, 0.0, 0.0, 0.0);

	//top
	CreateTriangle(0.75, 1.75, 0.0, 0.0, 1.75, 0.75, 0.0, 1.75, 0.0);
	CreateTriangle(0.75, 1.75, 0.0, 0.0, 1.75, 0.75, 0.75, 1.75, 0.75);

	//rightFrontSide
	CreateTriangle(0.75, 1.75, 0.0, 0.75, 0.0, 0.75, 0.75, 0.0, 0.0);
	CreateTriangle(0.75, 1.75, 0.0, 0.75, 0.0, 0.75, 0.75, 1.75, 0.75);

	//leftFrontSide
	CreateTriangle(0.0, 0.0, 0.75, 0.0, 1.75, 0.75, 0.75, 1.75, 0.75);
	CreateTriangle(0.0, 0.0, 0.75, 0.75, 0.0, 0.75, 0.75, 1.75, 0.75);
}

void display(void) {
	//clear the buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glRotated(0.2,0.0,1.0,0.0);
	//Get model - from library
	glEnable(GL_LIGHTING);
	/*glutSolidTeapot(0.80);*/
	glDisable(GL_LIGHTING);

	CreateCube();
	//CreateRectangle(0.0F);




	//glBegin(GL_TRIANGLES);
	//	glColor3f(1.0, 0.0, 0.0);
	//	glVertex3f(1.5, 0.0, 0.0);
	//	glColor3f(0.0, 1.0, 0.0);
	//	glVertex3f(0.0, 1.5, 0.0);
	//	glColor3f(0.0, 0.0, 1.0);
	//	glVertex3f(0.0, 0.0, 1.5);
	//glEnd();
	//
	//glPointSize(4.0);

	glColor3f(1.0,0.0,0.0);
	glLineWidth(3.0);
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(1.5, 0.0, 0.0);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(3.0);
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 1.5, 0.0);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	glLineWidth(3.0);
	glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, 0.0, 1.5);
	glEnd();
	//glutSolidSphere(1.0, 1.55, 2);
	
	//glPointSize(7.0);
	//glBegin(GL_POINTS);
	//	glColor3f(1.0, 1.0, 1.0);
	//	glVertex3f(2.1, 2.2, 2.0);
	//glEnd();

	//glPointSize(7.0);
	//glBegin(GL_POINTS);
	//	glColor3f(1.0, 1.0, 1.0);
	//	glVertex3f(2.0, 2.4, 2.0);
	//glEnd();

	//glPointSize(7.0);
	//glBegin(GL_POINTS);
	//	glColor3f(1.0, 1.0, 1.0);
	//	glVertex3f(1.8, 2.1, 2.0);
	//glEnd();

	//glPointSize(77.0);
	//glBegin(GL_POINTS);
	//	glColor3f(1.0, 1.0, 1.0);
	//	glVertex3f(3.1, 2.6, 2.0);
	//glEnd();



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
	gluPerspective(20.0, (GLfloat)_widht / (GLfloat)_height, 0.10, 20.0);

	//Set the model view matrix to identity
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Set the "look at" point - where the "camera" is and where it is "pointed"
	gluLookAt(10.0, 5.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
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