#include <windows.h>
#include <GL/gl.h>
#include <glut.h>
#include <GL/glu.h>

// Global variables for each of the your angles
 float angleT = 0.0;
 float angleH = 0.0;
 //Left
 float angleLS = 0.0;
 float angleLARM = 0.0;
 //Right
 float angleRS = 0.0;
 float angleRARM = 0.0;

 //Fingers
 float angleLFF = 0.0;
 float angleLSF = 0.0;
 float angleLTF = 0.0;
 float angleLHR = 0.0;
 float angleRHR = 0.0;

// Set the increment
static float angleInc = 3.0;

float baseHeight = 5.0;
float linkLength = 3.0;
float shoulderLength = 3.0;

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

void Axis() {
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
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
	glPopMatrix();
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
treenode torso2;
treenode torso3;
treenode torso4;
treenode head;
treenode LShoulder;
treenode LARM;
treenode LFFinger;
treenode LSFinger;
treenode LTFinger;
treenode RFFinger;
treenode RSFinger;
treenode RTFinger;
treenode RShoulder;
treenode RARM;

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
	glTranslated(0.0, baseHeight/2.0, 0.0);
	glScalef(baseHeight, baseHeight, linkLength/2.0);
	glutSolidCube(1.0);
	glPopMatrix();

	// baseHeight
	// linkLength 
}

void TorsoTransform()
{
	glTranslated(baseHeight,0.0,baseHeight);
	glRotated(angleT, 0.0, 1.0, 0.0);
}

void TorsoTransform2()
{
	glTranslated(-baseHeight,0.0,baseHeight);
	glRotated(angleT, 0.0, 1.0, 0.0);
}

void TorsoTransform3()
{
	glTranslated(GLfloat(baseHeight * -2), 0.0, GLfloat(baseHeight * -2));
	glRotated(angleT, 0.0, 1.0, 0.0);
}

void TorsoTransform4()
{
	glTranslated(0.0, 0.0, GLfloat(baseHeight * -2));
	glRotated(angleT, 0.0, 1.0, 0.0);
}

void HeadRender()
{
	Axis();
	glutSolidSphere(1.0, 8, 8);
}

void HeadTransform()
{
	glTranslated(0.0, baseHeight + 1.0, 0.0);
	glRotated(angleH, 0.0, 1.0, 0.0);
}

//LEFT ARM AND HAND

void LSRender() {
	glScaled(2.0, 0.5, 1.0);
	glutSolidCube(1.0);
}

void LSTransform() {
	glTranslated(linkLength, baseHeight - 1.5, 0.0);
	glRotated(angleLS, 0.0, 1.0, 0.0);
	glTranslated(0.5, 0.0, 0.0);
}

void LARMRender() {
	Axis();
	glScaled(0.3, 5.0, 1.0);
	glutSolidCube(1.0);
}

void LARMTransform() {
	glRotated(angleLARM, 1.0, 0.0, 0.0);
	glTranslated(0.5,-2.0, 0.0);
}

void LFFingerRender() {
	Axis();
	glScaled(0.2, 0.4, 0.2);
	glutSolidCube(1.0);
}

void LFFingerTransform() {
	glRotated(angleLFF, 1.0, 0.0, 0.0);
	glRotated(angleLHR, 1.0, 0.0, 0.0);
	glTranslated(0.0, 0.0, -0.2);
	glTranslated(0.0, -0.7, 0.0);
}

void LSFingerRender() {
	Axis();
	glScaled(0.2, 0.4, 0.2);
	glutSolidCube(1.0);
}

void LSFingerTransform() {
	glRotated(angleLFF, 1.0, 0.0, 0.0);
	glTranslated(0.0, 0.0, 0.3);
	glRotated(-angleLSF, 1.0, 0.0, 0.0);
	glTranslated(0.0, -0.6, 0.0);
}

void LTFingerRender() {
	Axis();
	glScaled(0.2, 0.4, 0.2);
	glutSolidCube(1.0);
}

void LTFingerTransform() {
	glRotated(angleLFF, 1.0, 0.0, 0.0);
	glTranslated(0.3, 0.0, 0.0);
	glRotated(angleLTF, 0.0, 0.0, 1.0);
	glTranslated(0.0, -0.6, 0.1);
}

//RIGHT ARM - HAND

void RSRender() {
	Axis();
	glScaled(2.0, 0.5, 1.0);
	glutSolidCube(1.0);
}

void RSTransform() {
	glTranslated(-linkLength, baseHeight - 1.5, 0.0);
	glRotated(angleRS, 0.0, 1.0, 0.0);
	glTranslated(-0.5, 0.0, 0.0);
}

void RARMRender() {
	Axis();
	glScaled(0.3, 5.0, 1.0);
	glutSolidCube(1.0);
}

void RARMTransform() {
	glRotated(angleRARM, 1.0, 0.0, 0.0);
	glTranslated(-0.5, -2.0, 0.0);
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
	torso.child = &head;
	torso.sibling = &torso2;

	head.draw = HeadRender;
	head.transform = HeadTransform;
	head.child = NULL;
	head.sibling = &LShoulder;

	//LEFT ARM

	LShoulder.draw = LSRender;
	LShoulder.transform = LSTransform;
	LShoulder.child = &LARM;
	LShoulder.sibling = &RShoulder;

	LARM.draw = LARMRender;
	LARM.transform = LARMTransform;
	LARM.child = &LFFinger;
	LARM.sibling = NULL;

	LFFinger.draw = LFFingerRender;
	LFFinger.transform = LFFingerTransform;
	LFFinger.child = NULL;
	LFFinger.sibling = &LSFinger;

	LSFinger.draw = LSFingerRender;
	LSFinger.transform = LSFingerTransform;
	LSFinger.child = NULL;
	LSFinger.sibling = &LTFinger;

	LTFinger.draw = LTFingerRender;
	LTFinger.transform = LTFingerTransform;
	LTFinger.child = NULL;
	LTFinger.sibling = NULL;

	//RIGHT Shoulder
	RShoulder.draw = RSRender;
	RShoulder.transform = RSTransform;
	RShoulder.child = &RARM;
	RShoulder.sibling = NULL;

	//RIGHT ARM
	RARM.draw = RARMRender;
	RARM.transform = RARMTransform;
	RARM.child = &RFFinger;
	RARM.sibling = NULL;

	RFFinger.draw = LFFingerRender;
	RFFinger.transform = LFFingerTransform;
	RFFinger.child = &RSFinger;
	RFFinger.sibling = NULL;

	RSFinger.draw = LSFingerRender;
	RSFinger.transform = LSFingerTransform;
	RSFinger.child = &RTFinger;
	RSFinger.sibling = NULL;

	RTFinger.draw = LTFingerRender;
	RTFinger.transform = LTFingerTransform;
	RTFinger.child = NULL;
	RTFinger.sibling = NULL;

	//Robot 2

	torso2.draw = TorsoRender;
	torso2.transform = TorsoTransform2;
	torso2.child = &head;
	torso2.sibling = &torso3;

	torso3.draw = TorsoRender;
	torso3.transform = TorsoTransform3;
	torso3.child = &head;
	torso3.sibling = &torso4;

	torso4.draw = TorsoRender;
	torso4.transform = TorsoTransform4;
	torso4.child = &head;
	torso4.sibling = NULL;
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

void Axes(void)
{
	glDisable(GL_LIGHTING);
   glLineWidth(2.0);
   glColor3f(1.0, 0.0, 0.0);
   glBegin(GL_LINES);
   glVertex3f(0.0,0.0,0.0);
   glVertex3f(2.0,0.0,0.0);
   glEnd();

   glColor3f(0.0, 1.0, 0.0);
   glBegin(GL_LINES);
   glVertex3f(0.0,0.0,0.0);
   glVertex3f(0.0,2.0,0.0);
   glEnd();

   glColor3f(0.0, 0.0, 1.0);
   glBegin(GL_LINES);
   glVertex3f(0.0,0.0,0.0);
   glVertex3f(0.0,0.0,2.0);
   glEnd();

   glEnable(GL_LIGHTING);
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
		case 'a':
            angleT-=angleInc;
            break;
		case 'A':
			angleT+=angleInc;
			break;
		case 's':
            angleH-=angleInc;
            break;
		case 'S':
			angleH+=angleInc;
			break;
		case 'e':
			angleLS -= angleInc;
			break;
		case 'E':
			angleLS += angleInc;
			break;
		case 'r':
			angleLARM -= angleInc;
			break;
		case 'R':
			angleLARM += angleInc;
			break;
		case 'p':
			angleRS -= angleInc;
			break;
		case 'P':
			angleRS += angleInc;
			break;
		case 'o':
			angleRARM -= angleInc;
			break;
		case 'O':
			angleRARM += angleInc;
			break;
		case 'i':
			if(angleLFF > 0)
				angleLFF -= angleInc;
			break;
		case 'I':
			if(angleLFF < 45)
				angleLFF += angleInc;
			break;
		case 'u':
			if (angleLSF > 0)
				angleLSF -= angleInc;
			break;
		case 'U':
			if (angleLSF < 45)
				angleLSF += angleInc;
			break;
		case 'y':
			if (angleLTF > 0)
				angleLTF -= angleInc;
			break;
		case 'Y':
			if (angleLTF < 45)
				angleLTF += angleInc;
			break;
		case 'k':
			if (angleLHR > 0)
				angleLHR -= angleInc;
			break;
		case 'K':
			if (angleLHR < 45)
				angleLHR += angleInc;
			break;
		case 'l':
			if (angleRHR > 0)
				angleRHR -= angleInc;
			break;
		case 'L':
			if (angleRHR < 45)
				angleRHR += angleInc;
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
	glutCreateWindow("Empty Hierarchical Model using Nodes");
	init();

	glutKeyboardFunc(keyboard);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);

	glutMainLoop();
	return 0;
}
