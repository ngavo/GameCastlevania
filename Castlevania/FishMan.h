#pragma once
#include "Enemy.h"
class FishMan: public Enemy
{
public:
	FishMan();
	DWORD last_time;
	float a;
	void Init(float x, float y, int width, int height);
	void Render(float x, float y);
	void Update(int time);
	~FishMan();
};

