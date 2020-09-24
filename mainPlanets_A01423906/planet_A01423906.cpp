#pragma once
#include <windows.h>
#include "planet.h"
#include "Moon.h"
#include "Disk.h"
#include <GL/gl.h>
#include <glut.h>

planet::planet(int planeta, float _size, int _lunas) {
	size = _size;
	lunas = _lunas;
	numPlaneta = planeta;
}

planet::~planet() {}

void planet::SetColor(float _r, float _g, float _b) {
	color[0] = _r;
	color[1] = _g;
	color[2] = _b;
}

void planet::SetTranslate(float _x, float _y, float _z) {
	translate[0] = _x;
	translate[1] = _y;
	translate[2] = _z;
}

void planet::SetRotations(float _day, float _year) {
	day = _day;
	year = _year;
}

void planet::SetDisk(float _tx, float _ty, float _tz)
{
	diskEnable = true;
	diskTrans[0] = _tx;
	diskTrans[1] = _ty;
	diskTrans[2] = _tz;
}

void planet::SetDime(float _dx, float _dy, float _dz)
{
	diskDimension[0] = _dx;
	diskDimension[1] = _dy;
	diskDimension[2] = _dz;
}

void planet::SetRadius(float _inner, float _outher)
{
	innerRadius = _inner;
	outherRadius = _outher;
}

void planet::SetDiskColor(float _r, float _g, float _b)
{
	diskColor[0] = _r;
	diskColor[1] = _g;
	diskColor[2] = _b;
}

void planet::SetDiskRotation(float _degres, float _rx, float _ry, float _rz)
{
	diskRotation[0] = _degres;
	diskRotation[1] = _rx;
	diskRotation[2] = _ry;
	diskRotation[3] = _rz;
}

void planet::SetMoonSpecs(float _size, float _tx, float _ty, float _tz,int _moonIndice)
{
	moonSize = _size;
	moonOffset[0] = _tx;
	moonOffset[1] = _ty;
	moonOffset[2] = _tz;
	moonIndice = _moonIndice;
}

void planet::SetMoonColor(float _r, float _g, float _b)
{
	moonColor[0] = _r;
	moonColor[1] = _g;
	moonColor[2] = _b;
}

void planet::SetMoonRotation(float _rx, float _ry, float _rz)
{
	moonRotationX[0] = _rx;
	moonRotationX[1] = _ry;
	moonRotationX[2] = _rz;
}

void planet::Draw(float _moonYears[], float _moonDays[]) {
	glPushMatrix();
		glRotated(year, 0.0, 1.0, 0.0);
		glTranslated(translate[0], translate[1], translate[2]);

		glPushMatrix();
			if (lunas != 0) {
				for (int i = 0; i < lunas; i++) {
					Moon moon(moonSize);
					moon.SetColor(moonColor[0], moonColor[1], moonColor[2]);
					moon.setOffset(moonOffset[0] , moonOffset[1], moonOffset[2]);
					moon.moonRotation(_moonDays[i + moonIndice], _moonYears[i + moonIndice], moonRotationX[0], moonRotationX[1], moonRotationX[2]);
					moon.Draw();
				}
			}
		glPopMatrix();

		glPushMatrix();
			if (diskEnable) {
				Disk disk(diskTrans[0], diskTrans[1], diskTrans[2]);
				disk.SetColor(diskColor[0], diskColor[1], diskColor[2]);
				disk.SetRotations(diskRotation[0], diskRotation[1], diskRotation[2], diskRotation[3]);
				disk.SetDime(diskDimension[0], diskDimension[1], diskDimension[2]);
				disk.SetRadius(innerRadius, outherRadius);
				disk.Draw();
			}
		glPopMatrix();

		glColor3fv(color);
		glRotated(day, 0.5, 0.5, 0.0);
		glScaled(size, size, size);
		glutSolidSphere(1.0, 20, 15);
	glPopMatrix();
}

void planet::Draw() {
	glPushMatrix();
		glRotated(year, 0.0, 1.0, 0.0);
		glTranslated(translate[0], translate[1], translate[2]);
		glColor3fv(color);
		glRotated(day, 0.5, 0.5, 0.0);
		glScaled(size, size, size);
		glutSolidSphere(1.0, 20, 15);
	glPopMatrix();
}