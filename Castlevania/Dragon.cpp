#include "Dragon.h"



Dragon::Dragon()
{
}

void Dragon::Init(float x, float y, int width, int height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	texture = new GTexture("Resources/enemy/BoneDragons.bmp", 3, 1, 3);
	sprite = new GSprite(texture, 0, 2, 2);
	camera = new GCamera();
	sprite->SelectIndex(2);
}
void Dragon::Render(float x, float y)
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
void Dragon::Update(int time)
{

}

Dragon::~Dragon()
{
}
