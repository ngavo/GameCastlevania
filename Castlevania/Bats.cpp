#include "Bats.h"

Bats::Bats()
{
	
	

}

void Bats::Update(int time)
{
	
	DWORD now = GetTickCount();
	if ((now - last_time) > (1000 / 10))
	{
		a += 0.3;
		this->_x = this->_x - 0.9*time;
		this->_y =  5 * sin(a) + this->_y;
		sprite->Next();
		last_time = now;
	}
}

void Bats::Init(float x, float y, int width, int height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	a = 0;
	texture = new GTexture("Resources/enemy/creep_right.bmp", 6, 5, 29);
	sprite = new GSprite(texture, 7, 10, 2);
	camera = new GCamera();
	sprite->SelectIndex(7);
}

void Bats::Render(float x, float y)
{
	if (this->die==false)
	{
		D3DXVECTOR2 view;
		view.x = x;
		view.y = y;
		camera->setViewPort(view);
		D3DXVECTOR2 _pos = camera->Transform(this->_x, this->_y);
		G_SpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);

		sprite->Draw(_pos.x, _pos.y);
		G_SpriteHandler->End();
	}
	

}


Bats::~Bats()
{
}
