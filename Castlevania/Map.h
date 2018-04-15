#pragma once
#include "QuadTreeObject.h"
#include "GameObject.h"
#include<fstream>
#include "SweptAABB.h"
#include "kitty.h"
#include "Bats.h"
#include "FishMan.h"
#include "Eagles.h"
#include "Fleaman.h"
#include "BoneDragons.h"
#include "Enemy.h"
using namespace std;
class Map
{
public:
	/*Bats*bat;
	FishMan*fishman;
	Eagles*eagles;
	Fleaman*fleaman;
	BoneDragons*bonedragones;*/

	vector<Bats*> ListBats;
	vector<FishMan*> ListFishMan;
	vector<Enemy*> ListEnemys;

	vector <GameObject*> ListObjects;//danh sach toan bo object trong Map 
	QuadTreeObject*quadtree;
	void LoadObjectFromFile(string filepath);
	void LoadMap(string filepath);
	void LoadObject(int IDObject, int Type, float x, float y, int width, int height);
	void LoadListObjectInWorld(RECT rect);
	void Draw(float x,float y);
	void Update(int time, kitty* simon);
	int CountRowObject(string filepath);
	int CountRowBetween(string filepath, int RowObject);
	Map();
	~Map();
};

