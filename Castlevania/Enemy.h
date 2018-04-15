#pragma once
#include "GCamera.h"
#include "GSprite.h"
#include "GTexture.h"
class Enemy
{
public:
	GSprite*sprite;
	GTexture*texture;
	GCamera*camera;
	int _id;
	float _x;
	float _y;
	bool hienthi;
	bool die;
	int _width;
	int _height;
	virtual void Init(float x, float y,int width,int height );
	virtual void  Update(int time);
	virtual void Render(float x, float y);
	
	Enemy();
	~Enemy();
};

