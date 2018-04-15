#include "Map.h"
#include "Ground.h"
#include "NenNho.h"
#include "Bats.h"
#include "Moving.h"
Map::Map()
{
	quadtree = new QuadTreeObject();
	/*bat = new Bats();
	fishman = new FishMan();
	eagles = new Eagles();
	fleaman = new Fleaman();
	bonedragones = new BoneDragons();
	bat->Init(600, 100, 32, 32);
	fishman->Init(600, 150, 32, 32);
	eagles->Init(600, 300, 32, 32);
	fleaman->Init(600, 262, 32, 32);
	bonedragones->Init(600, 400, 32, 32);*/
}

void Map::LoadObjectFromFile(string filepath)
{
	int id, type, width, height;
	float x, y; 
	ifstream fi;
	fi.open(filepath);

	while (!fi.eof())
	{
		fi >> id >> type >> x >> y >> width >> height;
		LoadObject( id, type, x, y, width, height);
	}

	fi.close();
}

void Map::LoadObject(int id, int type, float x, float y, int width, int height)
{
	GameObject*object = NULL;
	/*Bats*bat = NULL;
	FishMan*fishman = NULL;*/
	Enemy*enemy = NULL;
	switch (type)
	{
	case 12:
		object = new Ground(id, type, x, y, width, height);
		break;
	case 11:
		object = new NenNho(id, type, x, y, width, height);
		break;
	case 19:
		object = new Moving(id, type, x, y, width, height);
		break;
	case 0:
		enemy = new Bats();
		enemy->Init(x, y, width, height);
		break;
	case 3:
		enemy = new FishMan();
		enemy->Init(x, y, width, height);
		break;
	default:
		break;
	}
	if (object != NULL)
	{
		ListObjects.push_back(object);
	}
	if (enemy != NULL)
	{
		ListEnemys.push_back(enemy);
	}
	
	
}
void Map::LoadMap(string filepath)
{
	//quadtree->LoadNodeInFile(filepath, ListObjects);
	int  RowObject = 0;
	RowObject = CountRowObject(filepath);
	fstream file;
	file.open(filepath, ios::in);
	//dau danh sach object tu file vo ListObject
	for (int i = 0; i < RowObject; i++)
	{

		int IDObject; file >> IDObject;
		int Type; file >> Type;
		int flip; file >> flip;
		int x; file >> x;
		int y; file >> y;
		int width; file >> width;
		int height; file >> height;
		LoadObject(IDObject, Type,  x, y, width, height);
	}

	file.close();

	file.open(filepath, ios::in);


	int RowBetWeen = CountRowBetween(filepath, RowObject);

	quadtree->LoadNodeInFile(filepath, RowObject, RowBetWeen, ListObjects);
}

void Map::LoadListObjectInWorld(RECT rect)
{
	RECT rec;
	rec = rect;
	quadtree->GetListObjectInRect(rec);
	for (int i = 0; i < quadtree->ListObjectInRect.size() - 1; i++)
	{
		for (int j = i + 1; j<quadtree->ListObjectInRect.size(); j++)
			// Các object cùng địa chỉ
			if (quadtree->ListObjectInRect[i] == quadtree->ListObjectInRect[j])
			{
				quadtree->ListObjectInRect.erase(quadtree->ListObjectInRect.begin() + j);
				j--;
			}

	}

	if (ListEnemys.size() != 0)
	{
		for (int i = 0; i < ListEnemys.size(); i++)
		{
			if (ListEnemys[i]->_x<rec.right && ListEnemys[i]->_x > rec.left)
			{
				ListEnemys[i]->hienthi = true;
			}
		}
	}

}

void Map::Draw(float x, float y)
{
	if (quadtree->ListObjectInRect.size() != NULL)
	{
		for (int i = 0; i < quadtree->ListObjectInRect.size(); i++)
		{
			quadtree->ListObjectInRect[i]->Render(x,y);
		}
	}

	for(int k=0 ; k< ListEnemys.size();k++)
	{
		if(ListEnemys[k]->hienthi)
			ListEnemys[k]->Render(x,y);
	}

	
}


void Map::Update(int time, kitty*simon)
{
	if (quadtree->ListObjectInRect.size() != NULL)
	{
		for (int i = 0; i < quadtree->ListObjectInRect.size(); i++)
		{
			
			Box box(quadtree->ListObjectInRect[i]->_x - quadtree->ListObjectInRect[i]->_width / 2, quadtree->ListObjectInRect[i]->_y - quadtree->ListObjectInRect[i]->_height / 2, quadtree->ListObjectInRect[i]->_x + quadtree->ListObjectInRect[i]->_width / 2, quadtree->ListObjectInRect[i]->_y + quadtree->ListObjectInRect[i]->_height / 2, 0, 0);
			if (quadtree->ListObjectInRect[i]->GetType() == 12 || quadtree->ListObjectInRect[i]->GetType() == 19)
			{
				Box simonBox(simon->_posx - 16, simon->_posy - 32, simon->_posx+16, simon->_posy+32, simon->_vx, simon->_vy+simon->_vg);
				Box broadphasebox = GetSweptBroadphaseBox(simonBox, time);

					if (AABB(broadphasebox, box))
					{
						if (simon->_posy -32 <= quadtree->ListObjectInRect[i]->_y + quadtree->ListObjectInRect[i]->_height / 2)
						{
							if (quadtree->ListObjectInRect[i]->GetType() == 12)
							{
								simon->_posy = quadtree->ListObjectInRect[i]->_y + 50;
								simon->postground = quadtree->ListObjectInRect[i]->_y + 55;
								simon->dungtrenMove = false;
							}
							if (quadtree->ListObjectInRect[i]->GetType() == 19)
							{
								simon->_posy = quadtree->ListObjectInRect[i]->_y + 42;
								simon->postground = quadtree->ListObjectInRect[i]->_y + 42;
								simon->dungtrenMove = true;
								simon->_xtrenmove = quadtree->ListObjectInRect[i]->_detalx;
							}
							
							simon->nhay = false;
							simon->nhaydendocao = 0;
							
							simon->CheckLoLung = false;
						}
						
					}
					
			}

			if (simon->IsActack == true )
			{
				
			//	Box box(quadtree->ListObjectInRect[i]->_x - quadtree->ListObjectInRect[i]->_width / 2, quadtree->ListObjectInRect[i]->_y - quadtree->ListObjectInRect[i]->_height / 2, quadtree->ListObjectInRect[i]->_x + quadtree->ListObjectInRect[i]->_width / 2, quadtree->ListObjectInRect[i]->_y + quadtree->ListObjectInRect[i]->_height / 2, 0, 0);

				if (simon->sprite->GetIndex() == 16)//ngoi danh
				{
					Box whip(0,0,0,0,0,0);
					if (simon->flat==false)//ngoi danh voi hinh ben phai
					{
						whip = Box(simon->_posx + 16, simon->_posy, simon->_posx + 16 + 50, simon->_posy + 10, 0, 0);
						
					}
					else//ngoi danh voi hinh ben trai
					{
						 whip = Box(simon->_posx-16-50, simon->_posy, simon->_posx -16, simon->_posy + 10, 0, 0);
					}

					if (quadtree->ListObjectInRect[i]->GetType() == 11)
					{
						if (AABB(whip, box))
						{
							quadtree->ListObjectInRect[i]->hienthi = false;
						}
					}

				}
				if(simon->sprite->GetIndex() == 13)
				{
					Box whip(0, 0, 0, 0, 0, 0);
					if (simon->flat == false)//ngoi danh voi hinh ben phai
					{
						whip = Box(simon->_posx + 16, simon->_posy, simon->_posx + 16 + 50, simon->_posy + 10, 0, 0);

					}
					else//ngoi danh voi hinh ben trai
					{
						whip = Box(simon->_posx - 16 - 50, simon->_posy, simon->_posx - 16, simon->_posy + 10, 0, 0);
					}

					if (quadtree->ListObjectInRect[i]->GetType() == 11)
					{
						if (AABB(whip, box))
						{
							quadtree->ListObjectInRect[i]->hienthi = false;
						}
					}
				}

				
				

			}

			quadtree->ListObjectInRect[i]->Update(time);
		}
	}

	for (int k = 0; k < ListEnemys.size(); k++)
	{
		if (ListEnemys[k]->hienthi == true)
		{
			Box box(ListEnemys[k]->_x - 32, ListEnemys[k]->_y - 32, ListEnemys[k]->_x + 32, ListEnemys[k]->_y + 32,0,0);
			if (simon->IsActack == true)
			{

				//	Box box(quadtree->ListObjectInRect[i]->_x - quadtree->ListObjectInRect[i]->_width / 2, quadtree->ListObjectInRect[i]->_y - quadtree->ListObjectInRect[i]->_height / 2, quadtree->ListObjectInRect[i]->_x + quadtree->ListObjectInRect[i]->_width / 2, quadtree->ListObjectInRect[i]->_y + quadtree->ListObjectInRect[i]->_height / 2, 0, 0);

				if (simon->sprite->GetIndex() == 16)//ngoi danh
				{
					Box whip(0, 0, 0, 0, 0, 0);
					if (simon->flat == false)//ngoi danh voi hinh ben phai
					{
						whip = Box(simon->_posx + 16, simon->_posy, simon->_posx + 16 + 50, simon->_posy + 10, 0, 0);

					}
					else//ngoi danh voi hinh ben trai
					{
						whip = Box(simon->_posx - 16 - 50, simon->_posy, simon->_posx - 16, simon->_posy + 10, 0, 0);
					}

					
						if (AABB(whip, box))
						{
							ListEnemys[k]->die = true;
						}
					

				}
				if (simon->sprite->GetIndex() == 13)
				{
					Box whip(0, 0, 0, 0, 0, 0);
					if (simon->flat == false)//ngoi danh voi hinh ben phai
					{
						whip = Box(simon->_posx + 16, simon->_posy, simon->_posx + 16 + 50, simon->_posy + 10, 0, 0);

					}
					else//ngoi danh voi hinh ben trai
					{
						whip = Box(simon->_posx - 16 - 50, simon->_posy, simon->_posx - 16, simon->_posy + 10, 0, 0);
					}

					
						if (AABB(whip, box))
						{
							ListEnemys[k]->die = true;
						}
					
				}




			}
			ListEnemys[k]->Update(time);
		}
		
	}
}


int Map::CountRowObject(string filepath)
{
	fstream file;
	file.open(filepath, ios::in);

	int dem = 0;
	while (!file.eof())
	{
		string line;
		getline(file, line);
		if (line != "END")
		{
			dem = dem + 1;;
			//cout << line << "\n";
		}
		else
		{
			file.close();
			return dem;
		}
	}
}
int Map::CountRowBetween(string filepath, int RowObject)
{
	string line;
	fstream file;
	file.open(filepath, ios::in);
	for (int i = 0; i < RowObject; i++)
	{
		getline(file, line);
	}
	int dem = 0;
	getline(file, line);//lay end
	while (!file.eof())
	{
		getline(file, line);
		if (line != "END")
		{
			dem++;
		}
		else
		{
			file.close();
			return dem;
		}
	}

}
Map::~Map()
{
	for (int i = 0; i<ListObjects.size(); i++)
		if (ListObjects[i]) {
			delete ListObjects[i];
			ListObjects[i] = NULL;
		}
	ListObjects.clear();
	for (int  i = 0; i < ListEnemys.size(); i++)
	{
		if (ListEnemys[i])
		{
			delete ListEnemys[i];
			ListEnemys[i] = NULL;
		}
	}

	ListEnemys.clear();
}
