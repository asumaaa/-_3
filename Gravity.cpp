#include "Gravity.h"

void Gravity::Initialize(float x_, float y_, float z_, float weight_)
{
	this->x = x_;
	this->y = y_;
	this->z = z_;
	this->weight = weight_;
}

void Gravity::Updadte(Gravity g)
{
	if (abs(x - g.x) >= 32 || abs(y - g.y) >= 32 || abs(z - g.z) >= 32)
	{
		if (x - g.x < 0)
		{
			x += ((weight * g.weight) / (length(g) * length(g))) * G * VecGetX(g);
		}
		else
		{
			x -= ((weight * g.weight) / (length(g) * length(g))) * G * VecGetX(g);
		}
	}
	if (abs(x - g.x) >= 32 || abs(y - g.y) >= 32 || abs(z - g.z) >= 32)
	{
		if (y - g.y < 0)
		{
			y += ((weight * g.weight) / (length(g) * length(g))) * G * VecGetY(g);
		}
		else
		{
			y -= ((weight * g.weight) / (length(g) * length(g))) * G * VecGetY(g);
		}
	}
	if (abs(x - g.x) >= 32 || abs(y - g.y) >= 32 || abs(z - g.z) >= 32)
	{
		if (z - g.z < 0)
		{
			z += ((weight * g.weight) / (length(g) * length(g))) * G * VecGetY(g);
		}
		else
		{
			z-= ((weight * g.weight) / (length(g) * length(g))) * G * VecGetY(g);
		}
	}
}

float Gravity::length(Gravity g)
{
	float x2 = abs(x - g.x) * abs(x - g.x);
	float y2 = abs(y - g.y) * abs(y - g.y);
	float z2 = abs(z - g.z) * abs(z - g.z);
	return sqrt(x2 + y2 + z2);
}

float Gravity::VecGetX(Gravity g)
{
	return abs(g.x - x) / length(g);
}

float Gravity::VecGetY(Gravity g)
{
	return abs(g.y - y) / length(g);
}

float Gravity::VecGetZ(Gravity g)
{
	return abs(g.z - z) / length(g);
}
