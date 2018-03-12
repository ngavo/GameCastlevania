#include "kitty.h"
#define VX  0.5f

kitty::kitty()
{
	texture = new GTexture("simon_right.bmp", 6, 5, 29);
	sprite = new GSprite(texture, 0, 28, 2);
	this->_vx = VX;
	this->_posx = 100;
	this->_posy = 100;
	camera = new GCamera();
	
}

void kitty::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	/*if(_posx > G_ScreenWidth/2)*/

	/*camera->UpdateCamera(_posx);*/
	D3DXVECTOR2 _pos = camera->Transform(_posx, _posy);
	G_SpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);
	if (this->flat == false)
	{
		
			sprite->Draw(_pos.x, _pos.y);
	}
	else
	{
		sprite->DrawFlipX(_pos.x, _pos.y);
	}
	G_SpriteHandler->End();
	
}

void kitty::Next()
{
	sprite->Next();
}

void kitty::PosEnd(int end)
{
	sprite->GetEnd(end);
}

void kitty::PosStart(int start)
{
	sprite->GetStart(start);
}
kitty::~kitty()
{
}
