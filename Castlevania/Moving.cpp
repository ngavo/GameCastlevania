#include "Moving.h"



Moving::Moving(int id, int type, float x, float y, int width, int height)
{
	_Id = id;
	_Type = type;
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	this->texture = new GTexture("Resources/other/9.png", 1, 1, 1);
	sprite = new GSprite(this->texture, 0, 1, 2);
	this->camera = new  GCamera();
	this->left = x - 128;
	this->right = x + 80;
	this->_vx = -0.3;
}

void Moving::Render(float x, float y)
{
	if (this->hienthi)
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


void Moving::Update(int time)
{
	float k = this->_x;
	DWORD now = GetTickCount();
	if ((now - last_time) > (1000 / 10))
	{
		//this->_detalx = this->_vx*time;
		
		this->_x = this->_x + this->_vx*time;
		if (this->_x < this->left)
		{
			this->_vx = 0.3;
		}
		if (this->_x > this->right)
		{
			this->_vx = -0.3;
		}
		last_time = now;
	}

	

	this->_detalx = this->_x - k;
}
Moving::~Moving()
{
}
