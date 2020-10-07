#include <windows.h>
#include <GL/gl.h>
#include <glut.h>

GLfloat vertex[8][3];
GLfloat normals[8][3];
GLfloat normalFace[6][3];
GLint faces[6][4];

GLfloat center[3];

bool toggleNormal = false;

int globalDepth = 1;

void SetCube(void) {

	center[0] = 0.5;
	center[1] = 0.5;
	center[2] = 0.5;

	vertex[0][0] = 0.0;
	vertex[0][1] = 0.0;
	vertex[0][2] = 0.0;

	vertex[1][0] = 1.0;
	vertex[1][1] = 0.0;
	vertex[1][2] = 0.0;

	vertex[2][0] = 1.0;
	vertex[2][1] = 0.0;
	vertex[2][2] = 1.0;

	vertex[3][0] = 0.0;
	vertex[3][1] = 0.0;
	vertex[3][2] = 1.0;

	vertex[4][0] = 0.0;
	vertex[4][1] = 1.0;
	vertex[4][2] = 0.0;

	vertex[5][0] = 1.0;
	vertex[5][1] = 1.0;
	vertex[5][2] = 0.0;

	vertex[6][0] = 1.0;
	vertex[6][1] = 1.0;
	vertex[6][2] = 1.0;

	vertex[7][0] = 0.0;
	vertex[7][1] = 1.0;
	vertex[7][2] = 1.0;

	faces[0][0] = 0;
	faces[0][1] = 1;
	faces[0][2] = 2;
	faces[0][3] = 3;

	faces[1][0] = 4;
	faces[1][1] = 5;
	faces[1][2] = 1;
	faces[1][3] = 0;

	faces[2][0] = 7;
	faces[2][1] = 4;
	faces[2][2] = 0;
	faces[2][3] = 3;

	faces[3][0] = 6;
	faces[3][1] = 7;
	faces[3][2] = 3;
	faces[3][3] = 2;

	faces[4][0] = 5;
	faces[4][1] = 6;
	faces[4][2] = 2;
	faces[4][3] = 1;

	faces[5][0] = 7;
	faces[5][1] = 6;
	faces[5][2] = 5;
	faces[5][3] = 4;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 3; j++)
			normals[i][j] = vertex[i][j] - center[j];

	normalFace[0][0] = 0.0;
	normalFace[0][1] = -1.0;
	normalFace[0][2] = 0.0;

	normalFace[1][0] = 0.0;
	normalFace[1][1] = 0.0;
	normalFace[1][2] = -1.0;

	normalFace[2][0] = -1.0;
	normalFace[2][1] = 0.0;
	normalFace[2][2] = 0.0;

	normalFace[3][0] = 0.0;
	normalFace[3][1] = 0.0;
	normalFace[3][2] = 1.0;

	normalFace[4][0] = 1.0;
	normalFace[4][1] = 0.0;
	normalFace[4][2] = 0.0;

	normalFace[5][0] = 0.0;
	normalFace[5][1] = 1.0;
	normalFace[5][2] = 0.0;
}

void init(void)
{
	// Define material properties
	GLfloat mat_spec[] = { 3000.0, 3000.0, 3000.0, 1.0 };
	GLfloat mat_shiny[] = { 100.0 };
	GLfloat mat_surf[] = { 1.0, 1.0, 0.0, 0.0 };

	// Set light properties...
	GLfloat white_light[] = { 0.0, 1.0, 0.0, 1.0 };
	// and create two lights at two positions
	GLfloat light_pos0[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat light_pos1[] = { -1.0, -1.0, 1.0, 0.0 };

	// Set clear (background) color
	glClearColor(0.0, 0.0, 0.0, 0.0);

	// Set shading model to use
	glShadeModel(GL_SMOOTH);

	// Set material properties, as defined above
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shiny);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_surf);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_surf);

	// Finish setting up the two lights (position, and component values (specular and diffuse))
	glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

	glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white_light);

	// Enable lighting
	glEnable(GL_LIGHTING);
	// Activate (enable) lights
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	// Enable depth testing (for hidden surface removal)
	glEnable(GL_DEPTH_TEST);

	SetCube();
}

void subdivide(float *v0, float *v1, float *v2, float *v3, float* n0, float* n1, float* n2, float* n3, int _depth) {
	//Criteria met?

	float v01[3], v12[3], v23[3], v30[3], vc[3];
	float n01[3], n12[3], n23[3], n30[3], nc[3];

	if (_depth == 0) {
		glBegin(GL_QUADS);

		glNormal3fv(n0);
		glVertex3fv(v0);

		glNormal3fv(n1);
		glVertex3fv(v1);

		glNormal3fv(n2);
		glVertex3fv(v2);

		glNormal3fv(n3);
		glVertex3fv(v3);
		
		glEnd();
	}
	else {
		//Calculate new points
		//Calculate new Normals
		for (int i = 0; i < 3; i++) {
			v01[i] = v0[i] + 0.5 * (v1[i] - v0[0]);
			v12[i] = v1[i] + 0.5 * (v2[i] - v1[0]);
			v23[i] = v2[i] + 0.5 * (v3[i] - v2[0]);
			v30[i] = v3[i] + 0.5 * (v0[i] - v3[0]);

			vc[i] = v01[i] + 0.5 * (v23[i] - v01[i]);

			n01[i] = 0.5 * (n0[i] + n1[i]);
			n12[i] = 0.5 * (n1[i] + n2[i]);
			n23[i] = 0.5 * (n2[i] + n3[i]);
			n30[i] = 0.5 * (n3[i] + n0[i]);

			nc[i] = 0.5 * (n01[i] + n23[i]);
		}

		//Recursive call
		subdivide(v0, v01, vc, v30, n0, n01, nc, n30, _depth - 1);
		subdivide(v01, v1, v12, vc, n01, n1, n12, nc, _depth - 1);
		subdivide(vc, v12, v2, v23, nc, n12, n2, n23, _depth - 1);
		subdivide(v30, vc, v23, v3, n30, nc, n23, n3, _depth - 1);
	}
}

void display(void)
{
	// Clear the buffer 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//For each polygon

	for (int i = 0; i < 6; i++) {

		subdivide(vertex[faces[i][0]], vertex[faces[i][1]], vertex[faces[i][2]], vertex[faces[i][3]], normals[faces[i][0]], normals[faces[i][1]], normals[faces[i][2]], normals[faces[i][3]], globalDepth);
		/*glBegin(GL_QUADS);
		if(toggleNormal)
			glNormal3fv(normalFace[i]);

		for (int j = 0; j < 4; j++) {
			if(!toggleNormal)
				glNormal3fv(normals[faces[i][j]]);
			glVertex3fv(vertex[faces[i][j]]);
		}
		glEnd();*/
	}

	
	// Get model - from library
	//glutSolidTeapot(0.80);
	glFlush();
}

void reshape(int w, int h)
{
	// Set the viewport size, based on function input
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	// set the projection matrix based on input size
	glMatrixMode(GL_PROJECTION);
	// first set as identity
	glLoadIdentity();
	// then set perspective projection parameters based on aspect ratio
	gluPerspective(20.0, (GLfloat)w / (GLfloat)h, 0.10, 20.0);

	// Set the model view matrix to identity
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Set the "look at" point
	gluLookAt(6.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		// Use "Esc" key to exit
	case 27:
		exit(0);
		break;
	case 'x':
		toggleNormal = true;
		break;
	case 'X':
		toggleNormal = false;
		break;
	}
}

int main(int argc, char** argv)
{
	// GLUT INITIALIZATION
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Cube mesh");

	// Additional initalization
	init();

	// Register callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);

	// Do main loop
	glutMainLoop();

	// Exit
	return 0;
}