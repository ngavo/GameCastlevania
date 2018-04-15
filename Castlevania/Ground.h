#pragma once
#include "GameObject.h"
#include "GSprite.h"
#include "GTexture.h"
#include "GCamera.h"
class Ground: public GameObject
{
public:
	/*int _id; int _type; float _x; float _y; int _width; int _height;*/
	int HeadBrick;
	int HeadBrickY;
	int CountRow;
	int CountColumn;
	GTexture*texture;
	GSprite*sprite;
	GCamera*camera;
	Ground(int id, int type, float x, float y, int width, int height);
	void Update(int time);
	void Render(float x, float y);
	~Ground();
};

