#pragma once
#include"Enemy.h"
#include "Eagles.h"
#include <cstdlib>
#include <ctime>
class Fleaman:public Enemy
{
public:
	Fleaman();
	float a;
	DWORD last_time;
	bool flat=false;
	void Init(float x, float y, int width, int height);
	void Render(float x, float y);
	void Update(Eagles*eagles,int time);
	~Fleaman();
};

