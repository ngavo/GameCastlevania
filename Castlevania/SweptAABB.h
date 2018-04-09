#pragma once
#include <algorithm>
#include <limits>
#include <d3d9.h>

struct Box
{
	float l, t;
	float r, b;
	float vx, vy;

	Box(float _l, float _t, float _r, float _b, float _vx, float _vy)
	{
		l = _l;
		t = _t;
		r = _r;
		b = _b;
		vx = _vx;
		vy = _vy;
	}


};

static bool AABB(Box b1, Box b2)
{
	if (b1.l > b2.r)//canh trai box > canh phai vat qua cham
		return false;
	if (b1.r < b2.l)
		return false;
	if (b1.t > b2.b)
		return false;
	if (b1.b < b2.t)
		return false;
	return true;
}

// trả về box bao lấy phần giao thoa của box hiện tại và box đích
static Box GetSweptBroadphaseBox(Box b, int dt)
{
	Box broadphasebox(0.0f, 0.0f, 0.0f, 0.0f, 0.0f,0.0f);

	if (b.vx > 0)
	{
		broadphasebox.l = b.l;
		broadphasebox.r = b.r + b.vx*dt;
	}
	else
	{
		broadphasebox.l = b.l + b.vx*dt;
		broadphasebox.r = b.r;
	}

	if (b.vy > 0)
	{
		broadphasebox.t = b.t;
		broadphasebox.b = b.b + b.vy*dt;
	}
	else
	{
		broadphasebox.t = b.t + b.vy*dt;
		broadphasebox.b = b.b;
	}

	return broadphasebox;
}

//static float SweptAABB(Box b1, Box b2, float& normalx, float& normaly, int dt)
//{
//	float xInvEntry, yInvEntry;
//	float xInvExit, yInvExit;
//
//	// find the distance between the objects on the near and far sides for both x and y
//	if (b1.vx > 0.0f)
//	{
//		xInvEntry = b2.x - (b1.x + b1.w);
//		xInvExit = (b2.x + b2.w) - b1.x;
//	}
//	else
//	{
//		xInvEntry = (b2.x + b2.w) - b1.x;
//		xInvExit = b2.x - (b1.x + b1.w);
//	}
//
//	if (b1.vy < 0.0f)
//	{
//		yInvEntry = b2.y - (b1.y - b1.h);
//		yInvExit = (b2.y - b2.h) - b1.y;
//	}
//	else
//	{
//		yInvEntry = (b2.y - b2.h) - b1.y;
//		yInvExit = b2.y - (b1.y - b1.h);
//	}
//
//	// find time of collision and time of leaving for each axis (if statement is to prevent divide by zero)
//	float xEntry, yEntry;
//	float xExit, yExit;
//
//	if (b1.vx == 0.0f)
//	{
//		xEntry = -std::numeric_limits<float>::infinity();
//		xExit = std::numeric_limits<float>::infinity();
//	}
//	else
//	{
//		xEntry = xInvEntry / (b1.vx * dt);
//		xExit = xInvExit / (b1.vx * dt);
//	}
//
//	if (b1.vy == 0.0f)
//	{
//		yEntry = -std::numeric_limits<float>::infinity();
//		yExit = std::numeric_limits<float>::infinity();
//	}
//	else
//	{
//		yEntry = yInvEntry / (b1.vy * dt);
//		yExit = yInvExit / (b1.vy * dt);
//	}
//
//	// find the earliest/latest times of collision
//	float entryTime = max(xEntry, yEntry);
//	float exitTime = min(xExit, yExit);
//
//	// if there was no collision
//	if (entryTime > exitTime || xEntry < 0.0f && yEntry < 0.0f || xEntry > 1.0f || yEntry > 1.0f)
//	{
//		normalx = 0.0f;
//		normaly = 0.0f;
//		return 1.0f;
//	}
//	else // if there was a collision
//	{
//		// calculate normal of collided surface
//		if (xEntry > yEntry)
//		{
//			if (xInvEntry < 0.0f)
//			{
//				normalx = 1.0f;
//				normaly = 0.0f;
//			}
//			else
//			{
//				normalx = -1.0f;
//				normaly = 0.0f;
//			}
//		}
//		else
//		{
//			if (yInvEntry < 0.0f)
//			{
//				normalx = 0.0f;
//				normaly = 1.0f;
//			}
//			else
//			{
//				normalx = 0.0f;
//				normaly = -1.0f;
//			}
//		}
//
//		// return the time of collision
//		return entryTime;
//	}
//}
//
