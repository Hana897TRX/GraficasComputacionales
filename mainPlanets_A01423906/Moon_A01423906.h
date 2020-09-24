#pragma once
#include "planet.h"
class Moon
{
	float moonSize, moonOffset[3], color[3], year, days, rotation[3];
public:
	Moon(float);
	~Moon();

	void SetColor(float, float, float);
	void setOffset(float, float, float);
	void moonRotation(float, float, float, float, float);
	void Draw();
};

