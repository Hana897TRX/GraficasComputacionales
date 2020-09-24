#include "Disk.h"
#include <windows.h>
#include <GL/gl.h>
#include <glut.h>

Disk::Disk(float _tx, float _ty, float _tz)
{
	translate[0] = _tx;
	translate[1] = _ty;
	translate[2] = _tz;
}

Disk::~Disk()
{
}

void Disk::SetRadius(float _innerRadius,float _outherRadius) {
	innerRadius = _innerRadius;
	outherRadius = _outherRadius;
}

void Disk::SetDime(float _dx, float _dy, float _dz)
{
	dimensions[0] = _dx;
	dimensions[1] = _dy;
	dimensions[2] = _dz;
}

void Disk::SetRotations(float _degres, float _rx, float _ry, float _rz)
{
	rotation[0] = _degres;
	rotation[1] = _rx;
	rotation[2] = _ry;
	rotation[3] = _rz;
}

void Disk::SetColor(float _r, float _g, float _b)
{
	color[0] = _r;
	color[1] = _g;
	color[2] = _b;
}

void Disk::Draw()
{
	glPushMatrix();
		glColor3fv(color);
		glTranslatef(translate[0], translate[1], translate[2]);
		glScalef(dimensions[0], dimensions[1], dimensions[2]);
		glRotatef(rotation[0], rotation[1], rotation[2], rotation[3]);
		glutSolidTorus(innerRadius, outherRadius, slides, rings);
	glPopMatrix();
}
