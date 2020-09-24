#pragma once
#include "Moon.h"
#include <windows.h>
#include <GL/gl.h>
#include <glut.h>

Moon::Moon(float _moonSize)
{
	moonSize = _moonSize;
}

Moon::~Moon()
{
}

void Moon::SetColor(float _r, float _g, float _b) {
	color[0] = _r;
	color[1] = _g;
	color[2] = _b;
}

void Moon::setOffset(float _x, float _y, float _z)
{
	moonOffset[0] = _x;
	moonOffset[1] = _y;
	moonOffset[2] = _z;
}

void Moon::moonRotation(float _days, float _years, float _x, float _y, float _z)
{
	days = _days;
	year = _years;
	rotation[0] = _x;
	rotation[1] = _y;
	rotation[2] = _z;
}

void Moon::Draw()
{
	glColor3fv(color);
	glPushMatrix();
		glRotatef(year, rotation[0], rotation[1], rotation[2]);
		glTranslated(moonOffset[0], moonOffset[1], moonOffset[2]);
		glRotatef(days, rotation[0], rotation[1], rotation[2]);
		glScaled(moonSize, moonSize, moonSize);
		glutSolidSphere(1.0, 20, 15);
	glPopMatrix();
}
