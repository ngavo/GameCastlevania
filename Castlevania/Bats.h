#pragma once
#include "Enemy.h"
class Bats:public Enemy
{
public:
	DWORD last_time;
	float a;
	void Init(float x, float y, int width, int height);
	void Render(float x, float y);
	void Update(int time);
	Bats();
	~Bats();
};

