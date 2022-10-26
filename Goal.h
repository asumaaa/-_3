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
	void MaterDown(bool isMaterDown);
	//ゲッター
	XMFLOAT3 GetWorldPosition();

	int bulletHit_[3] = {};
public:

	DirectXCommon* dxCommon_;
	Input* input_ = nullptr;
	Cube* cube_;
	Object3d object_[4];

	float modelVelocityAngle_ = 0; //digrees
	XMFLOAT3 translation_[4];
	XMFLOAT3 scale_[4];
	XMFLOAT3 rotation_[4];

	float s = 0;

	int materDownTime_ = 0;//メーターダウンのディレイカウント
};

