#ifndef _SCENEMAIN_H_
#define _SCENEMAIN_H_

#include "Game.h"
#include "kitty.h"
#include "Map.h"
#include "BackgroundQuadtree.h"
class SceneMain: public CGame
{
public: 	
	SceneMain(int _nCmdShow);
	~SceneMain();	
	kitty * _kitty;
	Background* background;
	Map*map;
	BackgroundQuadtree*bgq;

protected:	
	
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void UpdateFrame(int Delta);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

#endif