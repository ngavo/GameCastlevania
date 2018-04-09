#include "Ground.h"



Ground::Ground(int id, int type, float x, float y, int width, int height)
{
	_Id = id;
	_Type = type;
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	this->texture = new GTexture("Resources/other/ground.png", 1, 1, 1);
	sprite = new GSprite(this->texture, 0, 0, 2);
	this->camera = new  GCamera();
}

void Ground::Render(int x, int y)
{
	/*D3DXVECTOR2 view;
	view.x = x;
	view.y = y;
	camera->setViewPort(view);
	
	G_SpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);
	D3DXVECTOR2 _pos = camera->Transform(this->_x, this->_y);
		sprite->Draw(_pos.x,_pos.y);
	G_SpriteHandler->End();*/
	D3DXVECTOR2 view;
	view.x = x;
	view.y = y;
	camera->setViewPort(view);
	for (int r = 0; r < CountRow; r++)
	{
		for (int c = 0; c < CountColumn; c++)
		{
			G_SpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);
			D3DXVECTOR2 _pos = camera->Transform(HeadBrick + c * 32, HeadBrickY + r * 32);
			sprite->Draw(_pos.x, _pos.y);
			G_SpriteHandler->End();
		}
	}
}

void Ground::Update(int time)
{
	/*sprite->Next(0, 0);*/
	CountRow = _height / 32;
	CountColumn = _width / 32;
	//if (countcolumn % 2 != 0)
//	{
	HeadBrick = _x - ((float)CountColumn / 2) * 32;
	HeadBrickY = _y - ((float)(CountRow / 2)) * 32;
//	}
//	else
//	{
//	HeadBrick = m_Position.x - (CountColumn / 2) * 32 + 16;
//	}
}
Ground::~Ground()
{
}
