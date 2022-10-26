#pragma once
#include "memory"
#include "Input.h"
#include "WorldTransform.h"
#include "Object3d.h"
#include "Cube.h"
#include "Texture.h"
#include "DirectXCommon.h"

class Goal
{
public:
	void Initialize(DirectXCommon* dxCommon, Cube* cube);
	void Update(XMMATRIX& matView, XMMATRIX& matProjection);
	void Draw(XMMATRIX matView);
public:

	DirectXCommon* dxCommon_;
	Input* input_ = nullptr;
	Cube* cube_;
	Object3d object_[4];

	float modelVelocityAngle_ = 0; //digrees
	XMFLOAT3 translation_[4];
	XMFLOAT3 scale_[4];
	XMFLOAT3 rotation_[4];
};

