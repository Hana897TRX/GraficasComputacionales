#pragma once
class planet
{
private:
	//Planet
	float scale[3], color[3], translate[3], size, moonRotation[5], day, year;
	int lunas = 0, numPlaneta = 0, moonIndice = 0;
	//Moon
	float moonSize, moonOffset[3], moonColor[3], moonRotationX[3];
	//Disk
	float diskTrans[3], diskDimension[3] = {1.0, 1.0, 1.0}, diskRotation[4], diskColor[3], innerRadius, outherRadius;
	bool diskEnable = false;

public:
	planet(int, float, int);
	~planet();
	//Planet
	void SetColor(float, float, float);
	void SetTranslate(float, float, float);
	void SetRotations(float, float);
	//Disk
	void SetDisk(float, float, float);
	void SetDime(float, float, float);
	void SetRadius(float, float);
	void SetDiskColor(float, float, float);
	void SetDiskRotation(float, float, float, float);
	//Moon
	void SetMoonSpecs(float, float, float, float, int);
	void SetMoonColor(float, float, float);
	void SetMoonRotation(float, float, float);
	void Draw(float[], float[]);
	void Draw();
};

