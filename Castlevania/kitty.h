#pragma once
#include "GSprite.h"
#include "GTexture.h"
#include "GCamera.h"
#include "whip.h"


class kitty
{
public:
	
	bool nhay;
	bool befornhay;
	bool move;
	bool IsActack;
	bool IsDown;
	bool CheckLoLung;
	int postground=100;
	D3DXVECTOR3 velocity;
	float _vx;
	float _vy;
	float _vg;
	int nhaydendocao;
	DWORD last_time;
	float _posx;
	float _posy;
	GSprite *sprite;
	GTexture *texture;
	GCamera*camera;
	whip*_whip;
	bool flat = false;
	kitty();
	LPDIRECT3DSURFACE9 _Background;
	void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
	void Update(int time);
	void Next();
	void PosIndex(int index);
	void PosEnd(int end);
	void PosStart(int start);
	void Jumb();
	void Actack();
	void ThucHienActack(int start, int end);
	void CheckActack();
	int CountSpriteActtack = 0;
	~kitty();
};

