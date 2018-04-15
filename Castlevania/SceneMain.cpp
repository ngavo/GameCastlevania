#include "SceneMain.h"


SceneMain::SceneMain(int _nCmdShow): CGame(_nCmdShow)
{
	
}

void SceneMain::UpdateFrame(int Delta)
{
	
	
	this->_kitty->Update(Delta);
	map->Update(Delta, this->_kitty);
	
	
	map->LoadListObjectInWorld(this->_kitty->camera->GetRegion(this->_kitty->camera->viewport.x, 0, G_ScreenWidth, G_ScreenHeight));
	//d3ddv->ColorFill(G_BackBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
	
}
void SceneMain::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	
	this->background->DrawBackground(this->_kitty->camera->viewport.x);
	map->Draw(this->_kitty->camera->viewport.x, G_ScreenHeight);
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
		if (this->_kitty->IsActack == false)
		{
			this->_kitty->_vx = 0.2;
			this->_kitty->_posx = this->_kitty->_posx + this->_kitty->_vx*Delta;
			/*this->_kitty->_posx = this->_kitty->_posx + this->_v*/
			this->_kitty->flat = false;//dung de xem di chuyen trai hay phai
			this->_kitty->PosStart(0);
			this->_kitty->PosEnd(3);
			this->_kitty->Next();
		}
		
		
		
	}
	if (IsKeyDown(DIK_LEFT))
	{
		if (this->_kitty->IsActack == false)
		{
			this->_kitty->_vx = -0.2;
			this->_kitty->_posx = this->_kitty->_posx + this->_kitty->_vx*Delta;
			this->_kitty->flat = true;
			this->_kitty->PosStart(0);
			this->_kitty->PosEnd(3);
			this->_kitty->Next();
		}
		
			
		
	}
	if (IsKeyDown(DIK_DOWN))
	{
		this->_kitty->IsDown = true;
		this->_kitty->_vx = 0;
		this->_kitty->_vy = 0;
	}

	
}

void SceneMain::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	this->background = new Background();
	this->background->readfile("stage.txt");
	this->_kitty = new kitty();
	this->map = new Map();
	map->LoadMap("Resources/quadtree/stage10.o");
}

void SceneMain::OnKeyDown(int KeyCode)
{
	if (KeyCode == DIK_SPACE)
	{
		if (this->_kitty->CheckLoLung == false)
		{
			this->_kitty->nhay = true;
			this->_kitty->dungtrenMove = false;
			this->_kitty->_vy = 1;
			this->_kitty->nhaydendocao = this->_kitty->_posy + 100;
			this->_kitty->PosIndex(4);
		}
		
		
	}
	if (KeyCode== DIK_F)
	{
		if(this->_kitty->IsActack==false)
			this->_kitty->Actack();
	}
}
void SceneMain::OnKeyUp(int KeyCode)
{
	
	if (KeyCode == DIK_RIGHT)
	{
		this->_kitty->PosIndex(0);
		
	}
	if (KeyCode == DIK_LEFT)
	{
		this->_kitty->PosIndex(0);
	}
	if (KeyCode == DIK_DOWN)
	{
		this->_kitty->IsDown = false;
		
		this->_kitty->_vx = 0.3;
		this->_kitty->PosIndex(0);
	}
		
	
}
SceneMain::~SceneMain(void)
{
}
