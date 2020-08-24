#include <Windows.h>
#include <GL/gl.h>
#include <glut.h>
float p1[3];
float p2[3];
float p3[3];

float pointSize = 4.0F;
float lineWidth = 2.0F;
int color = 0;
int selectPoint = 0;

void init(void) {
	//Set clear background color (rgba)
	//RGB 0 to 1
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//Set shading model to use
	//glShadeModel(GL_SMOOTH);

	////DEFIN MATERIAL PROPERTIES (for objects in scene)
	//GLfloat mat_spec[] = { 0.393548, 0.271906, 0.166721, 1.0};
	//GLfloat mat_shiny[] = { 0.2 };
	//GLfloat mat_amb[] = { 0.2125, 0.1275, 0.054, 1.0};
	//GLfloat mat_dif[] = { 0.5, 0.5, 0.5, 1.0 };


	//glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
	//glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiny);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);

	////DEFINE LIFHT PROPERTIES (for lights in scene)
	//GLfloat while_light[] = { 1.0, 1.0, 1.0, 1.0 };
	//GLfloat light_pos[] = { 1.0, 1.0, 1.0, 0.0 };
	//GLfloat light_pos_1[] = { -1.0, -1.0, 1.0, 0.0 };

	////SET LIGHT PROPERTIES
	//glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, while_light);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, while_light);

	//glLightfv(GL_LIGHT1, GL_POSITION, light_pos_1);
	//glLightfv(GL_LIGHT1, GL_DIFFUSE, while_light);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, while_light);

	////Activate (enable) lights
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);

	////Enable lighting
	//glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);

	//Enable depth testing (for hidden surface removal)

	//for (int i = 0; i < 3; i++) {
	 int i = 0;
		p1[0] = 50.0 + i * 50.0;
		p1[1] = 60.0 + i * 50.0;
		p1[2] = 0.0;
	
		i = 1;
		p2[0] = 50.0 + i * 50.0;
		p2[1] = 60.0 + i * 50.0;
		p2[2] = 0.0;

		i = 2;
		p3[0] = 50.0 + i * 50.0;
		p3[1] = 60.0 + i * 50.0;
		p3[2] = 0.0;
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
	
	glPointSize(pointSize);

	if (color == 0)
		glColor3f(1.0, 0.0, 0.0);
	else if(color == 1)
		glColor3f(0.0, 1.0, 0.0);
	if (color == 2)
		glColor3f(0.0, 0.0, 1.0);

	glBegin(GL_POINTS);
		glVertex3fv(p1);
	glEnd();
	
	glBegin(GL_POINTS);
		glVertex3fv(p2);
	glEnd();
	
	glBegin(GL_POINTS);
		glVertex3fv(p3);
	glEnd();
	
	glLineWidth(lineWidth);
	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_LINES);
		glVertex3fv(p1);
		glVertex3fv(p2);

		glVertex3fv(p2);
		glVertex3fv(p3);
	glEnd();

	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_TRIANGLES);
		glVertex3fv(p1);
		glVertex3fv(p2);
		glVertex3fv(p3);
	glEnd();

	//glFlush();
	glutSwapBuffers();
}

void reshape(int _widht, int _height) {
	//Set the viewport size, based on function input

	glViewport(0, 0, (GLsizei)_widht, (GLsizei)_height);

	//Set the projction matrix based on input size
	glMatrixMode(GL_PROJECTION);
	//first set as identity
	//then set perspective projection parmeters based on aspect ratio
	glLoadIdentity();
	//gluPerspective(20.0, (GLfloat)_widht / (GLfloat)_height, 0.10, 20.0);
	gluOrtho2D(0, 400, 0, 400);

	//Set the model view matrix to identity
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Set the "look at" point - where the "camera" is and where it is "pointed"
	//gluLookAt(10.0, 5.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	case 's':
		pointSize -= 1.0;
		if (pointSize == 0.0)
			pointSize = 1.0;
		glutPostRedisplay();
		break;
	
	case 'S':
		pointSize += 1.0;
		if (pointSize >= 10.0)
			pointSize = 9.0;
		glutPostRedisplay;
		break;
	}
}

void processSpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		color += 1;
		if (color == 3)
			color = 0;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		color -= 1;
		if (color == -1)
			color = 2;
		glutPostRedisplay();
		break;
	}
}

void mouse(int btn, int state, int x, int y) {
	if (state == GLUT_DOWN) 
	{
		if (btn == GLUT_LEFT_BUTTON) 
		{
			if (selectPoint == 0) 
			{
				p1[0] = x;
				p1[1] = y;
				selectPoint = 1;
			}
			else if (selectPoint == 1) 
			{
				p2[0] = x;
				p2[1] = y;
				selectPoint = 2;
			}
			else if (selectPoint == 2) 
			{
				p3[0] = x;
				p3[1] = y;
				selectPoint = 0;
			}

			glutPostRedisplay();
		}
	}
}

void idle(void)
{
	p1[0] += 0.1;
	p2[0] += 0.1;
	p3[0] += 0.1;

	p1[1] -= 0.1;
	p2[1] -= 0.1;
	p3[1] -= 0.1;

	glutPostRedisplay();
}

int main(int argc, char** argv) {
	//GLUT INITIALIZATION
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL Teapot");

	//Additional initialization
	init();

	//Register callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);
	glutSpecialFunc(processSpecialKeys);
	glutMouseFunc(mouse);

	//Do main loop
	glutMainLoop();

	//Exit
	return 0;
}