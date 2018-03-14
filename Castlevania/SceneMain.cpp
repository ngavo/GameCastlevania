#include "SceneMain.h"

SceneMain::SceneMain(int _nCmdShow): CGame(_nCmdShow)
{
	
}

void SceneMain::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	d3ddv->ColorFill(G_BackBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
	this->background->DrawBackground(this->_kitty->camera->viewport.x);
	this->_kitty->RenderFrame(d3ddv,t);
}

void SceneMain::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
	if (this->_kitty->_posx > G_ScreenWidth / 2)
	{
		this->_kitty->camera->UpdateCamera(this->_kitty->_posx);
	}
	if (IsKeyDown(DIK_RIGHT))
	{
		this->_kitty->flat = false;
		this->_kitty->_posx = this->_kitty->_posx + this->_kitty->_vx*Delta;
		this->_kitty->PosStart(0);
		this->_kitty->PosEnd(3);
		this->_kitty->Next();
	}
	if (IsKeyDown(DIK_LEFT))
	{
		this->_kitty->flat = true;
		this->_kitty->_posx = this->_kitty->_posx - this->_kitty->_vx*Delta;
		this->_kitty->PosEnd(3);
		this->_kitty->Next();
	}
}

void SceneMain::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	this->_kitty = new kitty();
	this->background = new Background();
	this->background->readfile2("8473_true-no-brick.txt");
}

void SceneMain::OnKeyDown(int KeyCode)
{

}

SceneMain::~SceneMain(void)
{
}
