#include "whip.h"



whip::whip()
{
	this->texture = new GTexture("Resources/weapon/whip_right.bmp",3,6,18);
	this->sprite = new GSprite(texture, 0, 27, 2);
}

void whip:: SetIndex(int index)
{
	this->sprite->SelectIndex(index);
}
void whip::Draw(int x,int y)
{
	this->sprite->Draw(x, y);
}
void whip::DrawFlip(int x, int y)
{
	this->sprite->DrawFlipX(x, y);
}

int whip::GetIndex()
{
	return this->sprite->GetIndex();
}
whip::~whip()
{
}
