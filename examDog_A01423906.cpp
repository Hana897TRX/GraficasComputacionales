#include <windows.h>
#include <GL/gl.h>
#include <glut.h>
#include <GL/glu.h>

// Global variables for each of the your angles
 float angleT = 0.0;
 float angleH = 0.0;

// Set the increment
static float angleInc = 3.0;

float baseHeight = 5.0;
float linkLength = 3.0;

float H1 = 0.0, H2 = 0.0, J = 0.0, N = 0.0, LA1 = 0.0, LA2 = 0.0, LA3= 0.0, LB1 = 0.0, LB2 = 0.0, LB3 = 0.0;

void drawCylinder(GLdouble baseRadius,
	GLdouble topRadius,
	GLdouble height,
	GLint slices,
	GLint stacks)
{
	GLUquadricObj* qobj;
	qobj = gluNewQuadric();
	gluQuadricDrawStyle(qobj, GLU_LINE); // GLU_SOLID
	gluCylinder(qobj, baseRadius, topRadius, height,
		slices, stacks);
}

void Axes(void)
{
	glDisable(GL_LIGHTING);
	glLineWidth(2.0);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(2.0, 0.0, 0.0);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 2.0, 0.0);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 2.0);
	glEnd();

	glEnable(GL_LIGHTING);
}

typedef struct treenode
{
	//GLfloat m[16];
	void (*transform)();
	void (*draw)();
	struct treenode *sibling;
	struct treenode *child;
} treenode;

void traverse(treenode *root)
{
	// Check to see if this node is null (error checking)
	//if(root == NULL)
	//	return;

	// Apply transformation for current node and draw
	// Continue with depth-first search (go to children)
	glPushMatrix();

	root->transform();
	root->draw();

	// Check for children
	// NOTE that transformation is still applied
	if(root->child != NULL)
		traverse(root->child);
	
	glPopMatrix();
	
	// Check for siblings
	if(root->sibling != NULL)
		traverse(root->sibling);
}

// Alternate cylinder for drawing
void glutSolidCylinder (float r, float h, int n, int m)
{
    glPushMatrix ();
    glRotatef (90,1.0f, 0.0f, 0.0f);
    glTranslatef (0.0F, 0.0F,-h / 2);
    GLUquadricObj * qobj = gluNewQuadric ();
    gluQuadricDrawStyle (qobj, GLU_FILL);
    gluCylinder (qobj, r, r, h, n, m);
    gluDeleteQuadric (qobj);
    glPopMatrix ();
}

// Define transforms and render functions here
// -------------------------------------------
// treenode node
treenode root;
treenode torso;
//Neck
treenode neck;
//Head
treenode head;
//Mouth
treenode mouth1;
treenode mouth2;
//LegLB
treenode legLB;
treenode calfLB;
treenode fotLB;
//LegRA
treenode legRA;
treenode calfRA;
treenode fotRA;
//LegLA
treenode legLA;
//LegRA
treenode legRB;

// methods
void EmptyTransform()
{
}

void EmptyRender()
{
}

void TorsoRender()
{
	// Leer arhivo
	// .... cargar puntos, triangulos, colores...
	glPushMatrix();
		glScalef(1.0, 1.0, 2.0);
		glutSolidSphere(2, 30, 30);
	glPopMatrix();

	// baseHeight
	// linkLength 
}

void TorsoTransform()
{
	glRotated(angleT, 0.0, 1.0, 0.0);
	glTranslated(0.0, 1.5, 0.0);
}

//LegLB

void LegLBRender() {
	glPushMatrix();
		//Axes();
		glScaled(0.7, 3.0, 1.0);
		glutSolidCube(1.0);
	glPopMatrix();
}

void LegLBTransform() {
	glTranslated(2.0, 0.0, -2.5);
	glRotated(45 + LB1, 1.0, 0.0, 0.0);
	glTranslated(0.0, -1.0, 0.0);
}

void CalfLBRender() {
	glPushMatrix();
		Axes();
		glScaled(0.7, 3.0, 1.0);
		glutSolidCube(1.0);
	glPopMatrix();
}

void CalfLBTransform() {
	glTranslated(0.0, -1.5, 0.0);
	glRotatef(-90 + LB2, 1.0, 0.0, 0.0);
	glTranslated(0.0, -1.5, 0.0);
}

void FotLBRender() {
	glPushMatrix();
		Axes();
		glScaled(1.1, 0.3, 1.3);
		glutSolidCube(1.0);
	glPopMatrix();
}

void FotLBTransform() {
	glRotated(45, 1.0, 0.0, 0.0);
	glTranslated(0.0, -1.2, 1.0);
	glRotated(LB3, 1.0, 0.0, 0.0);
	glTranslated(0.0, 0.0, 0.4);
}

//LegRA

void LegRARender() {
	glPushMatrix();
		//Axes();
		//glRotated(45, 1.0, 0.0, 0.0);
		glScaled(0.7, 3.0, 1.0);
		glutSolidCube(1.0);
	glPopMatrix();
}

void LegRATransform() {
	//glTranslated(-2.0, 0.0, -1.5);
	glTranslated(-2.0, 0.0, -2.5);
	glRotated(45 + LA1, 1.0, 0.0, 0.0);
	glTranslated(0.0, -1.0, 0.0);
}

void CalfRARender() {
	glPushMatrix();
	//Axes();
		//glRotated(-45, 1.0, 0.0, 0.0);
		glScaled(0.7, 3.0, 1.0);
		glutSolidCube(1.0);
	glPopMatrix();
}

void CalfRATransform() {
	glTranslated(0.0, -1.5, 0.0);
	glRotatef(-90 + LA2, 1.0, 0.0, 0.0);
	glTranslated(0.0, -1.5, 0.0);
	//glTranslated(0.0, -2.0, 0.0);

}

void FotRARender() {
	glPushMatrix();
	Axes();
	glScaled(1.1, 0.3, 1.3);
	glutSolidCube(1.0);
	glPopMatrix();
}

void FotRATransform() {
	glRotated(45, 1.0, 0.0, 0.0);
	glTranslated(0.0, -1.2, 1.0);
	glRotated(LA3, 1.0, 0.0, 0.0);
	glTranslated(0.0, 0.0, 0.4);
}

//LegLA
void LegLATransform() {
	glTranslated(2.0, 0.0, 2.5);
	glRotated(45 + LA1, 1.0, 0.0, 0.0);
	glTranslated(0.0, -1.0, 0.0);
}

//LegRB
void LegRBTransform() {
	glTranslated(-2.0, 0.0, 2.5);
	glRotated(45 + LB1, 1.0, 0.0, 0.0);
	glTranslated(0.0, -1.0, 0.0);
}

//NECK
void NeckRender() {
	glPushMatrix();
		//Axes();
		glRotated(90, 1.0, 0.0, 0.0);
		drawCylinder(0.5, 0.5, 3.0, 60, 60);
	glPopMatrix();
}

void NeckTransform() {
	glTranslated(0.0, 0.0, 2.5);
	glRotated(15 + N, 1.0, 0.0, 0.0);
	glTranslated(0.0, 4.0, 0.0);
}

//Head

void HeadRender() {
	glRotated(H2, 0.0, 1.0, 0.0);
	glRotated(H1, 1.0, 0.0, 0.0);
	glPushMatrix();
		Axes();
		glScaled(1.5, 1.5, 1.5);
		glutSolidCube(1.0);
	glPopMatrix();
}

void HeadTransform() {
	glTranslated(0.0, 0.0, 0.0);
}

void MouthRender() {
	glPushMatrix();
		Axes();
		glScaled(1.0, 0.45, 1.0);
		glutSolidCube(1.0);
	glPopMatrix();
}

void MouthTranslate() {
	glTranslated(0.0, 0.0, 1.25);
}

void Mouth2Render() {
	glPushMatrix();
		glRotated(J, 1.0, 0.0, 0.0);
		glTranslated(0.0, 0.0, 1.25);
		glScaled(1.0, 0.25, 1.0);
		glutSolidCube(1.0);
	glPopMatrix();
}

void Mouth2Translate() {
	glTranslated(0.0, -0.25, 0.0);
}

// END define transforms and render functions
// -------------------------------------------

void Create()
{
	// Create tree structure here  
	root.draw = EmptyRender;
	root.transform = EmptyTransform;
	root.child = &torso;
	root.sibling = NULL;

	torso.draw = TorsoRender;
	torso.transform = TorsoTransform;
	torso.child = &neck;
	torso.sibling = NULL;
	
	//Neck
	neck.draw = NeckRender;
	neck.transform = NeckTransform;
	neck.child = &head;
	neck.sibling = &legLB;

	//Head
	head.draw = HeadRender;
	head.transform = HeadTransform;
	head.child = &mouth1;
	head.sibling = NULL;

	//Mouth
	mouth1.draw = MouthRender;
	mouth1.transform = MouthTranslate;
	mouth1.child = NULL;
	mouth1.sibling = &mouth2;

	mouth2.draw = Mouth2Render;
	mouth2.transform = Mouth2Translate;
	mouth2.child = NULL;
	mouth2.sibling = NULL;

	//Legs
		//LegLB

		legLB.draw = LegLBRender;
		legLB.transform = LegLBTransform;
		legLB.child = &calfLB;
		legLB.sibling = &legRA;

		calfLB.draw = CalfLBRender;
		calfLB.transform = CalfLBTransform;
		calfLB.child = &fotLB;
		calfLB.sibling = NULL;

		fotLB.draw = FotLBRender;
		fotLB.transform = FotLBTransform;
		fotLB.child = NULL;
		fotLB.sibling = NULL;

		//LegRA
		legRA.draw = LegRARender;
		legRA.transform = LegRATransform;
		legRA.child = &calfRA;
		legRA.sibling = &legLA;

		calfRA.draw = CalfRARender;
		calfRA.transform = CalfRATransform;
		calfRA.child = &fotRA;
		calfRA.sibling = NULL;

		fotRA.draw = FotRARender;
		fotRA.transform = FotRATransform;
		fotRA.child = NULL;
		fotRA.sibling = NULL;

		//LegLA
		legLA.draw = LegRARender;
		legLA.transform = LegLATransform;
		legLA.child = &calfRA;
		legLA.sibling = &legRB;

		//LegRB
		legRB.draw = LegLBRender;
		legRB.transform = LegRBTransform;
		legRB.child = &calfLB;
		legRB.sibling = NULL;

}

void init(void)
{
    // Set clear (background) color
	glClearColor(0.3, 0.32, 0.354, 0.0);

   // Set light properties...
   GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light_position0[] = { 1.0, 1.0, 1.0, 0.0 };
   GLfloat light_position1[] = { -1.0, 1.0, 0.5, 0.0 };

   // Finish setting up the two lights (position, and component values (specular and diffuse))
   glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
   glLightfv(GL_LIGHT0, GL_AMBIENT_AND_DIFFUSE, white_light);
   glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

   glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
   glLightfv(GL_LIGHT1, GL_AMBIENT_AND_DIFFUSE, white_light);
   glLightfv(GL_LIGHT1, GL_SPECULAR, white_light);

   // Define material properties
   GLfloat mat_specular[] = { 0.8, 0.9, 1.0, 1.0 };
   GLfloat mat_shininess[] = { 30.0 };
   GLfloat mat_surface[] = { 0.2, 0.2, 0.9, 1.0 };

   // Set material properties, as defined above
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
   glMaterialfv(GL_FRONT, GL_AMBIENT, mat_surface);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_surface);

   // Set shading model to use
   glShadeModel (GL_SMOOTH);

   // Enable lighting
   glEnable(GL_LIGHTING);
   // Activate (enable) lights
   glEnable(GL_LIGHT0);
   glEnable(GL_LIGHT1);

   // Enable depth testing (for hidden surface removal)
   glEnable(GL_DEPTH_TEST);

   // Create tree structure
   Create();
}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Initial Push-Pop, so that each time display is called, the same image is drawn
	Axes();

    glPushMatrix();
	traverse( &root );
    glPopMatrix();

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport( 0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 40.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(10.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
		case 'm':
			angleT -= angleInc;
			break;
		case 'M':
			angleT += angleInc;
			break;
		case 'a':
            H1 -= angleInc;
            break;
		case 'A':
			H1 += angleInc;
			break;
		case 's':
            H2 -= angleInc;
            break;
		case 'S':
			H2 += angleInc;
			break;
		case 'j':
			J -= angleInc;
			break;
		case 'J':
			J += angleInc;
			break;
		case 'n':
			N -= angleInc;
			break;
		case 'N':
			N += angleInc;
			break;
		case 'p':
			LA1 -= angleInc;
			break;
		case 'P':
			LA1 += angleInc;
			break;
		case 'o':
			LA2 -= angleInc;
			break;
		case 'O':
			LA2 += angleInc;
			break;
		case 'i':
			LA3 -= angleInc;
			break;
		case 'I':
			LA3 += angleInc;
			break;
		case 'b':
			LB1 -= angleInc;
			break;
		case 'B':
			LB1 += angleInc;
			break;
		case 'v':
			LB2 -= angleInc;
			break;
		case 'V':
			LB2 += angleInc;
			break;
		case 'c':
			LB3 -= angleInc;
			break;
		case 'C':
			LB3 += angleInc;
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

int main (int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Dogo");
	init();

	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);

	glutMainLoop();
	return 0;
}
