#pragma once
#include "Enemy.h"
#include "Dragon.h"
class BoneDragons: public Enemy
{
public:
	BoneDragons();
	bool len = false;
	bool xuong = false;
	int this_xuong = 0;
	int this_len = 0;
	Dragon* dragon[6];
	DWORD last_time;
	void Init(float x, float y, int width, int height);
	void Render(float x, float y);
	void Update(int time);
	~BoneDragons();
};

