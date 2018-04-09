#pragma once
#include "GSprite.h"
class whip
{
public:
	GSprite *sprite;
	GTexture *texture;
	whip();
	void SetIndex(int index);
	void Draw(int x,int y);
	void DrawFlip(int x, int y);
	int GetIndex();
	~whip();
};

