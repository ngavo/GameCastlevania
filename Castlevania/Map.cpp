#include "Map.h"
#include "Ground.h"
#include "NenNho.h"
#include "Bats.h"
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
	switch (type)
	{
	case 12:
		object = new Ground(id, type, x, y, width, height);
		break;
	case 11:
		object = new NenNho(id, type, x, y, width, height);
		break;
	default:
		break;
	}
	if (object != NULL)
	{
		ListObjects.push_back(object);
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
}

void Map::Draw(int x, int y)
{
	if (quadtree->ListObjectInRect.size() != NULL)
	{
		for (int i = 0; i < quadtree->ListObjectInRect.size(); i++)
		{
			quadtree->ListObjectInRect[i]->Render(x,y);
		}
	}
	/*bat->Render(x, y);
	fishman->Render(x, y);
	eagles->Render(x, y);
	fleaman->Render(x, y);
	bonedragones->Render(x, y);*/
}


void Map::Update(int time, kitty*simon)
{
	if (quadtree->ListObjectInRect.size() != NULL)
	{
		for (int i = 0; i < quadtree->ListObjectInRect.size(); i++)
		{
			quadtree->ListObjectInRect[i]->Update(time);
			Box box(quadtree->ListObjectInRect[i]->_x - quadtree->ListObjectInRect[i]->_width / 2, quadtree->ListObjectInRect[i]->_y - quadtree->ListObjectInRect[i]->_height / 2, quadtree->ListObjectInRect[i]->_x + quadtree->ListObjectInRect[i]->_width / 2, quadtree->ListObjectInRect[i]->_y + quadtree->ListObjectInRect[i]->_height / 2, 0, 0);
			if (quadtree->ListObjectInRect[i]->GetType() == 12)
			{
				Box simonBox(simon->_posx - 16, simon->_posy - 32, simon->_posx+16, simon->_posy+32, simon->_vx, simon->_vy+simon->_vg);
				Box broadphasebox = GetSweptBroadphaseBox(simonBox, time);
				

				/*if (simon->_posy-32 < quadtree->ListObjectInRect[i]->_y+quadtree->ListObjectInRect[i]->_height/2 && simon->_posx +32 > quadtree->ListObjectInRect[i]->_x - quadtree->ListObjectInRect[i]->_width / 2 && simon->_posx <quadtree->ListObjectInRect[i]->_x + quadtree->ListObjectInRect[i]->_width / 2)
				{
					simon->_posy = quadtree->ListObjectInRect[i]->_y + 50;
					simon->nhay = false;
					simon->nhaydendocao = 0;
					simon->postground = quadtree->ListObjectInRect[i]->_y + 50;
					simon->CheckLoLung = false;
				}*/

					if (AABB(broadphasebox, box))
					{
						if (simon->_posy -32 <= quadtree->ListObjectInRect[i]->_y + quadtree->ListObjectInRect[i]->_height / 2)
						{
							simon->_posy = quadtree->ListObjectInRect[i]->_y + 50;
							simon->nhay = false;
							simon->nhaydendocao = 0;
							simon->postground = quadtree->ListObjectInRect[i]->_y + 55;
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
						whip = Box(simon->_posx + 16, simon->_posy, simon->_posx + 16 + 72, simon->_posy + 24, 0, 0);
						
					}
					else//ngoi danh voi hinh ben trai
					{
						 whip = Box(simon->_posx-16-72, simon->_posy, simon->_posx -16, simon->_posy + 24, 0, 0);
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
						whip = Box(simon->_posx + 16, simon->_posy, simon->_posx + 16 + 72, simon->_posy + 24, 0, 0);

					}
					else//ngoi danh voi hinh ben trai
					{
						whip = Box(simon->_posx - 16 - 72, simon->_posy, simon->_posx - 16, simon->_posy + 24, 0, 0);
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
		}
	}
	/*bat->Update(time);
	fishman->Update(time);
	eagles->Update(time);
	fleaman->Update(eagles, time);
	bonedragones->Update(time);*/
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
	/*delete eagles;
	delete bat;
	delete fishman;
	delete fleaman;*/
}
