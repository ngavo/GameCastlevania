#include "BoneDragons.h"



BoneDragons::BoneDragons()
{
}
void BoneDragons::Init(float x, float y, int width, int height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
	texture = new GTexture("Resources/enemy/BoneDragons.bmp", 3, 1, 3);
	sprite = new GSprite(texture, 0, 2, 2);
	camera = new GCamera();
	dragon[0] = new Dragon();
	dragon[1] = new Dragon();
	dragon[2] = new Dragon();
	dragon[3] = new Dragon();
	dragon[4] = new Dragon();
	dragon[5] = new Dragon();
	dragon[0]->Init(_x, _y, 32, 32);
	dragon[1]->Init(_x, _y, 32, 32);
	dragon[2]->Init(_x, _y, 32, 32);
	dragon[3]->Init(_x, _y, 32, 32);
	dragon[4]->Init(_x, _y, 32, 32);
	dragon[5]->Init(_x, _y, 32, 32);
}
void BoneDragons::Render(float x, float y)
{
	
	D3DXVECTOR2 view;
	view.x = x;
	view.y = y;
	camera->setViewPort(view);
	D3DXVECTOR2 _pos = camera->Transform(this->_x, this->_y);
	G_SpriteHandler->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK | D3DXSPRITE_ALPHABLEND);

	sprite->Draw(_pos.x, _pos.y);
	G_SpriteHandler->End();

	this->dragon[0]->Render(x, y);
	this->dragon[1]->Render(x, y);
	this->dragon[2]->Render(x, y);
	this->dragon[3]->Render(x, y);
	this->dragon[4]->Render(x, y);
	this->dragon[5]->Render(x, y);

}
void BoneDragons::Update(int time)
{
	DWORD now = GetTickCount();
	if ((now - last_time) > (1000 / 3))
	{
		
		if (this->_x < 480)//dang set co dinh sau sẽ dựa vào vị trị trong quadtree - (6*wight+ 21 với wight là chiều dài của moi đốt  21 là một nữa của cái đầu)
		{
			if (this->_y >= 400  && this_xuong==0)//xuong lan dau
			{
				this->xuong = true;
				this->len = false;

			}
			//if (this->_y <= 250 && this_len==0)//len lan dau
			//{
			//	this->len = true;
			//	this->xuong = false;
			//}

			if (this->_y >= 550 && this_len == 1)//len toi dinh lan dau va sau do xuong
			{
				this->xuong = true;
				this->len = false;
			}

			



		}
		else
		{
			this->_x = this->_x - 0.1*time;
			this->dragon[0]->_x = this->_x + 21;
			this->dragon[1]->_x = this->dragon[0]->_x + 21;
			this->dragon[2]->_x = this->dragon[1]->_x + 21;
			this->dragon[3]->_x = this->dragon[2]->_x + 21;
			this->dragon[4]->_x = this->dragon[3]->_x + 21;
			this->dragon[5]->_x = 600;

		}

		if (this->xuong == true)
		{
			if (this_xuong == 0)//xuong lan dau tien
			{
				this->_y = this->_y - 0.2*time;
				if (this->_y <= 400 && this->_y>370)
				{
					this->dragon[0]->_y = this->_y + 20;
				}
				if (this->_y <= 370 && this->_y < 340)
				{
					this->dragon[0]->_y = this->_y + 20;
					this->dragon[1]->_y = this->_y + 40;
				}
				if (this->_y <= 340 && this->_y > 310)
				{
					this->dragon[0]->_y = this->_y + 20;
					this->dragon[1]->_y = this->_y + 40;
					this->dragon[2]->_y = this->_y + 60;
				}
				if (this->_y <= 310 && this->_y > 280)
				{
					this->dragon[0]->_y = this->_y + 20;
					this->dragon[1]->_y = this->_y + 40;
					this->dragon[2]->_y = this->_y + 60;
					this->dragon[3]->_y = this->_y + 80;
				}
				if (this->_y <= 280 && this->_y > 250)
				{
					this->dragon[0]->_y = this->_y + 20;
					this->dragon[1]->_y = this->_y + 40;
					this->dragon[2]->_y = this->_y + 60;
					this->dragon[3]->_y = this->_y + 80;
					this->dragon[4]->_y = this->_y + 100;
				}
				if (this->_y <= 250)
				{
					this->xuong = false;
					this->len = true;
					this_len = 1;
				}
				
				this->dragon[5]->_y = 400;
			}
			
			if (this_xuong != 0)
			{
				this->_y = this->_y - 0.2*time;
				if (this->_y < 550 && this->_y <= 520)
				{
					this->dragon[0]->_y = this->_y + 20;
				}
				if (this->_y <= 520 && this->_y > 490)
				{
					this->dragon[0]->_y = this->_y + 20;
					this->dragon[1]->_y = this->_y + 40;
				}
				if (this->_y <= 460 && this->_y > 430)
				{
					this->dragon[0]->_y = this->_y + 20;
					this->dragon[1]->_y = this->_y + 40;
					this->dragon[2]->_y = this->_y + 60;
				}
				if (this->_y <= 430 && this->_y > 400)
				{
					this->dragon[0]->_y = this->_y + 20;
					this->dragon[1]->_y = this->_y + 40;
					this->dragon[2]->_y = this->_y + 90;
				}
				if (this->_y <= 400)
				{
					this->len = true;
					this_len = 2;
				}

			}
			

		}

		if (this->len == true)
		{
			/*this->_y = this->_y + 0.2*time;
			this->dragon[0]->_y = this->_y - 10;
			this->dragon[1]->_y = this->dragon[0]->_y - 10;
			this->dragon[2]->_y = this->dragon[1]->_y - 10;
			this->dragon[3]->_y = this->dragon[4]->_y + 10;
			this->dragon[4]->_y = this->dragon[5]->_y + 10;
			this->dragon[5]->_y = 250;*/
			if (this_len == 1)
			{
				this->_y = this->_y + 0.2*time;
				if (this->_y > 280 && this->_y <= 310)
				{
					this->dragon[0]->_y = this->_y - 20;
				}
				if (this->_y > 310 && this->_y <= 340)
				{
					this->dragon[0]->_y = this->_y - 20;
					this->dragon[1]->_y = this->_y - 40;
				}
				if (this->_y > 340 && this->_y <= 370)
				{
					this->dragon[0]->_y = this->_y - 20;
					this->dragon[1]->_y = this->_y - 40;
					this->dragon[2]->_y = this->_y - 60;
				}
				if (this->_y > 370 && this->_y <= 400)
				{
					this->dragon[0]->_y = this->_y - 20;
					this->dragon[1]->_y = this->_y - 40;
					this->dragon[2]->_y = this->_y - 60;
					this->dragon[3]->_y = this->_y - 80;
				}
				if (this->_y >400 && this->_y <= 550)
				{
					this->dragon[0]->_y = this->_y - 20;
					this->dragon[1]->_y = this->_y - 40;
					this->dragon[2]->_y = this->_y - 60;
					this->dragon[3]->_y = this->_y - 80;
					this->dragon[4]->_y = this->_y - 100;
				}
				if (this->_y > 550)
				{
					this->xuong = true;
					this->len = false;
					this_xuong = 1;
				}

				this->dragon[5]->_y = 400;
			}

			if (this_len > 1)
			{
				this->_y = this->_y + 0.2*time;
				if (this->_y <= 430 && this->_y > 400)
				{
					this->dragon[0]->_y = this->_y - 100;
					/*this->dragon[2]->_y = this->_y-30;*/
				}
				if (this->_y <= 460 && this->_y > 430)
				{
					this->dragon[0]->_y = this->_y - 30;
					this->dragon[1]->_y = this->_y - 10;
					this->dragon[2]->_y = 400;
				}
				if (this->_y <= 490 && this->_y > 460)
				{
					this->dragon[0]->_y = this->_y - 20;
					this->dragon[1]->_y = this->_y - 40;
					this->dragon[3]->_y = 400 - 40;
				}
				if (this->_y <= 520 && this->_y > 490)
				{
					this->dragon[0]->_y = this->_y - 20;
					this->dragon[1]->_y = this->_y - 40;
					this->dragon[3]->_y = 400 - 40;
					this->dragon[4]->_y = 400 - 80;
				}

				if (this->_y <= 550 && this->_y < 520)
				{
					this->dragon[0]->_y = this->_y - 20;
					this->dragon[1]->_y = this->_y - 40;
					this->dragon[3]->_y = 400 + 40;
					this->dragon[4]->_y = 400 + 80;
				}
				if (this->_y > 550)
				{
					this->xuong = true;
				}

				this->dragon[5]->_y = 400;
			}
	
		}
	}

	
}

BoneDragons::~BoneDragons()
{
	delete[] dragon;
}
