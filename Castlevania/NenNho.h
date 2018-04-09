#pragma once
#include"GameObject.h"
#include "GCamera.h"
class NenNho: public GameObject
{
public:
	NenNho(int id, int type, float x, float y, int width, int height);
	DWORD last_time;
	GTexture*texture;
	GSprite*sprite;
	GCamera*camera;
	/*Ground(int id, int type, float x, float y, int width, int height);*/
	void Render(int x,int y);
	void Update(int time);
	~NenNho();
};

