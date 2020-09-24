#pragma once
class Disk
{
private:
	float translate[3], dimensions[3] = { 1.0, 1.0, 1.0 }, rotation[4], innerRadius, outherRadius, slides = 50, rings = 45;
	float color[3];
public:
	Disk(float, float, float);
	~Disk();
	void SetRadius(float, float);
	void SetDime(float, float, float);
	void SetRotations(float, float, float, float);
	void SetColor(float, float, float);
	void Draw();
};

