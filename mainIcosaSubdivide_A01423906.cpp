#include <windows.h>
#include <GL/gl.h>
#include <glut.h>
#include <math.h>

#define X 0.525731112119133606
#define Z 0.850650808352039932

bool toggleNormal = false;

int globalDepth;
float rotation = 0;

static GLfloat vertdata[12][3] = {
	{-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},
	{0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},
	{Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0}
};
static GLfloat normalsFace[20][3];
static GLuint facedata[20][3] = {
	{1,4,0}, {4,9,0}, {4,5,9}, {8,5,4}, {1,8,4},
	{1,10,8}, {10,3,8}, {8,3,5}, {3,2,5}, {3,7,2},
	{3,10,7}, {10,6,7}, {6,11,7}, {6,0,11}, {6,1,0},
	{10,1,6}, {11,0,9}, {2,11,9}, {5,2,9}, {11,2,7}
};

void SetNormals(void) { //normals = vertex * 0.5
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 3; j++)
			normalsFace[i][j] = vertdata[facedata[i][j]][j] * 0.5;
}

void init(void)
{
	GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat blue_light[] = { 0.0, 0.0, 0.0, 0.0 };

	GLfloat light_pos0[] = { 1.0, 1.0, 1.0, 0.0 };
	GLfloat light_pos1[] = { -1.0, -1.0, 1.0, 0.0 };
	GLfloat light_pos2[] = { 0.0, 1.0, 0.0, 1.0 };

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

	glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, white_light);
	glLightfv(GL_LIGHT1, GL_SPECULAR, white_light);

	glLightfv(GL_LIGHT2, GL_POSITION, light_pos2);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, blue_light);
	glLightfv(GL_LIGHT2, GL_SPECULAR, blue_light);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	glEnable(GL_DEPTH_TEST);
	globalDepth = 1;
	SetNormals();
}

void GetHalfVext(float *newV) {
	float scale = sqrtf(newV[0] * newV[0] + newV[1] * newV[1] + newV[2] * newV[2]);
	newV[0] /=scale;
	newV[1] /=scale;
	newV[2] /=scale;
}

void SetMaterials(void) {
	GLfloat mat_ambient[] = { 0.05375f, 0.05f, 0.06625f, 0.82f };
	GLfloat mat_diffuse[] = { 0.18275f, 0.17f, 0.22525f, 0.82f };
	GLfloat mat_spec[] = { 0.332741f, 0.328634f, 0.346435f, 0.82f };
	GLfloat shine = 238.4f;

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_spec);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);
	glMaterialfv(GL_FRONT, GL_SHININESS, &shine);
}

void subdivide(float *v0, float *v1, float *v2, float *n0, float *n1, float *n2, int _depth) {
	float v01[3], v12[3], v20[3];
	float n01[3], n12[3], n20[3];

	if (_depth == 0) {
		glDisable(GL_LIGHTING);
		glBegin(GL_TRIANGLES);
		SetMaterials();
			glColor3fv(n0);
			glNormal3fv(n0);
			glVertex3fv(v0);

			glColor3fv(n1);
			glNormal3fv(n1);
			glVertex3fv(v1);

			glColor3fv(n2);
			glNormal3fv(n2);
			glVertex3fv(v2);
		glEnd();
		glEnable(GL_LIGHTING);
	}
	else {
		for (int i = 0; i < 3; i++) {
			v01[i] = v0[i] + v1[i];
			v12[i] = v1[i] + v2[i];
			v20[i] = v2[i] + v0[i];
			n01[i] = 0.5 * ((GLfloat)n0[i] + (GLfloat)n1[i]);
			n12[i] = 0.5 * ((GLfloat)n1[i] + (GLfloat)n2[i]);
			n20[i] = 0.5 * ((GLfloat)n2[i] + (GLfloat)n0[i]);
		}

		GetHalfVext(v01);
		GetHalfVext(v12);
		GetHalfVext(v20);

		subdivide(v0, v01, v20, n0, n01, n20, _depth - 1);
		subdivide(v20, v12, v01, n20, n12, n01, _depth - 1);
		subdivide(v01, v1, v12, n01, n1, n12, _depth - 1);
		subdivide(v20, v12, v2, n20, n12, n2, _depth - 1);
	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glRotatef(rotation, 0.0, 1.0, 0.0);

	if(toggleNormal)
		glShadeModel(GL_SMOOTH);
	else
		glShadeModel(GL_FLAT);
	
	for (int i = 0; i < 20; i++)
		subdivide(vertdata[facedata[i][0]], 
				  vertdata[facedata[i][1]], 
			      vertdata[facedata[i][2]], 
			      normalsFace[facedata[i][0]], 
			      normalsFace[facedata[i][1]], 
			      normalsFace[facedata[i][2]], 
			      globalDepth);
	
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0, (GLfloat)w / (GLfloat)h, 0.10, 20.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(6.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
		break;
	case 'x':
		toggleNormal = true;
		break;
	case 'X':
		toggleNormal = false;
		break;
	case '+':
		globalDepth++;
		break;
	case '-':
		globalDepth--;
		if (globalDepth < 0)
			globalDepth = 0;
		break;
	case 'r':
		rotation+= 0.1F;
		break;
	case 'R':
		rotation-=0.1F;
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Cube mesh");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(display);

	glutMainLoop();

	return 0;
}