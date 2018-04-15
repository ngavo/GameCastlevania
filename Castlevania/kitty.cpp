#include "kitty.h"
#define VX  0.2f
#define G -0.2f

kitty::kitty()
{
	texture = new GTexture("simon_right.bmp", 6, 5, 29);
	sprite = new GSprite(texture, 0, 28, 2);
	this->_vx = VX;
	this->_vg = G;
	this->_vy = 0;
	this->_posx = 110;
	this->_posy = 150;
	camera = new GCamera();
	_whip = new whip();
	nhay = false;
	move = false;
	IsActack = false;
	IsDown = false;
	befornhay = false;
	CheckLoLung = false;
	dungtrenMove = false;
	//chamdat = false;
}

void kitty::Update(int time)
{
	
	
	/*this->_posy = this->_posy - this->_vg*time;*/
	if (this->dungtrenMove == true)
	{
		this->_posx = this->_posx + this->_xtrenmove;
	}
	 
	this->_posy = this->_posy + this->_vy*time + this->_vg*time;

	if (this->_posy > this->nhaydendocao )
	{
		this->_vy = 0;
	}
	if (this->_posy <= this->postground && this->nhay==true)//nhay cham mat dat
	{
		this->PosIndex(0);
	}

	if (this->_posy > this->postground && this->nhay == true)//nhay chua cham mat dat
	{
		this->CheckLoLung = true;
		if (IsActack == true)//nhay danh
		{
			ThucHienActack(11, 13);
		}
		else//khong danh chi nhay
		{
			
			this->PosIndex(4);
		}
		
	}

	if (this->nhay == false)//dung 
	{
		if (this->IsDown == true)
		{
			if (IsActack == true)
			{
				
					ThucHienActack(14, 16);
				
			}
			else
			{
				this->PosIndex(4);
			}
		}
		else
		{
			if (IsActack == true)
			{
				
				ThucHienActack(11, 13);
				
			}
		}
		
	}


	
	
}
void kitty::ThucHienActack(int start, int end)
{
	DWORD now = GetTickCount();
	sprite->GetStart(start);
	sprite->GetEnd(end);
	
		if (now - last_time > 1000 / 8)
		{
			
			last_time = now;
			
			if (this->IsDown == true)
			{
				/*if (sprite->GetIndex() == 14)
				{
					_whip->SetIndex(0);
				}
				if (sprite->GetIndex() == 15)
				{
					_whip->SetIndex(1);
				}
				if (sprite->GetIndex() == 16)
				{
					_whip->SetIndex(2);
				}*/

				if (CountSpriteActtack == 0)
				{
					sprite->SelectIndex(14);
					_whip->SetIndex(0);
				}
				if (CountSpriteActtack == 1)
				{
					sprite->SelectIndex(15);
					_whip->SetIndex(1);
				}

				if (CountSpriteActtack == 2)
				{
					sprite->SelectIndex(16);
					_whip->SetIndex(2);
				}

			}
			else
			{
				if (CountSpriteActtack == 0)
				{
					sprite->SelectIndex(11);
					_whip->SetIndex(0);
				}
				if (CountSpriteActtack == 1)
				{
					sprite->SelectIndex(12);
					_whip->SetIndex(1);
				}
				
				if (CountSpriteActtack == 2)
				{
					sprite->SelectIndex(13);
					_whip->SetIndex(2);
				}
				/*if (sprite->GetIndex() == 11)
				{
					
				}
				if (sprite->GetIndex() == 12)
				{
					_whip->SetIndex(1);
				}
				if (sprite->GetIndex() == 13)
				{
					_whip->SetIndex(2);
				}*/
			}

			
			
		//	sprite->SelectIndex(sprite->GetIndex()-1);
			CheckActack();
			
			
		}

	//	sprite->Next();
	
	
}

void kitty::CheckActack()
{
	if (CountSpriteActtack == 3)
	{
		IsActack = false;
		//this->_vy = VY;
		CountSpriteActtack = 0;
		if (this->IsDown == true)
		{
			this->PosIndex(4);
		}
		if (this->IsDown == false)
		{
			this->PosIndex(0);
		}
		this->_vx = VX;
	}
	else
	{
		CountSpriteActtack = CountSpriteActtack+1;
	}
}
void kitty::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	
	D3DXVECTOR2 _pos = camera->Transform(_posx, _posy);
	G_SpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);
	if (this->flat == false)
	{
			
			sprite->Draw(_pos.x, _pos.y);
			if (IsActack == true)
			{
				
				_whip->Draw(_pos.x, _pos.y);
			
			}
			
	}
	else
	{
		
		sprite->DrawFlipX(_pos.x, _pos.y);
		if (IsActack == true)
		{
			
			_whip->DrawFlip(_pos.x, _pos.y);
			
		}
		
	}
	G_SpriteHandler->End();
	
}

void kitty::Next()
{
	sprite->Next();
}

void kitty::PosIndex(int index)
{
	sprite->_index = index;
}

void kitty::PosEnd(int end)
{
	sprite->GetEnd(end);
}


void kitty::Jumb()
{
	
	
}

void kitty::Actack()
{
	if (this->IsDown == true)
		this->PosIndex(14);
	if(this->IsDown==false)
		this->PosIndex(11);
	this->IsActack = true;
	this->_vx = 0;
}

void kitty::PosStart(int start)
{
	sprite->GetStart(start);
}
kitty::~kitty()
{
}
