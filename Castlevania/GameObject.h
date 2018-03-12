#pragma once
#include "GSprite.h"
#include "GTexture.h"
class GameObject
{
public:

	GameObject();

	GSprite*sprite;
	GTexture*texture;

	// ====== các phương thức ảo =====
	virtual void Init(int _X, int _Y);		// reset object
	virtual void Update(const float &_DeltaTime);	// update per frame
	virtual void Render();							// render per frame
	virtual void Destroy();					// clear sub object, without delete this
	~GameObject();
};

