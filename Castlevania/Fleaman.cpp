#include "Fleaman.h"



Fleaman::Fleaman()
{
}

void Fleaman::Init(float x, float y, int width, int height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	texture = new GTexture("Resources/enemy/Fleaman.bmp", 2, 1, 2);
	sprite = new GSprite(texture, 0, 1, 2);
	camera = new GCamera();
	sprite->SelectIndex(0);
}
void Fleaman::Render(float x, float y)
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
void Fleaman::Update(Eagles*eagles,int time)
{
	if (camera->viewport.x + G_ScreenWidth / 2 > eagles->_x)
	{
		if (this->_y > 150 && this->flat==false)
		{
			this->_y = this->_y - 0.3*time;
		}
			
		else
		{
			this->flat = true;
			this->_x = this->_x + 0.6*cos(0.7)*time;
			if (this->_y < 170)
			{
				this->_y = this->_y + 0.6*sin(0.7)*time;
				this->sprite->SelectIndex(0);
			}
			else
			{
				this->sprite->SelectIndex(0);
				this->flat = false;
			}

		}
		
		
	}
	else
	{
		this->_x = eagles->_x;
	}

	
}

Fleaman::~Fleaman()
{
}
