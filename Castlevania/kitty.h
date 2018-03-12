#pragma once
#include "GSprite.h"
#include "GTexture.h"
#include "GCamera.h"
class kitty
{
public:
	float _vx;
	float _vy;
	float _posx;
	float _posy;
	GSprite *sprite;
	GTexture *texture;
	GCamera*camera;
	bool flat = false;
	kitty();
	LPDIRECT3DSURFACE9 _Background;
	void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);

	void Next();
	void PosEnd(int end);
	void PosStart(int start);
	~kitty();
};

