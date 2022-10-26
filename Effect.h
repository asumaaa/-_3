#pragma once
#include <list>
#include <cassert>
#include "DirectXMath.h"
#include "DirectXCommon.h"
#include "Cube.h"
#include "Input.h"
#include "Object3d.h"
#include "lane.h"

//エフェクトの数
const int EFFECT_NUM = 40;

class Effect
{
public:
	void Initialize(DirectXCommon* dxCommon, Cube* cube, XMFLOAT3 vector3, int texNum);
	void Update(XMMATRIX& matView, XMMATRIX& matProjection);
	void Draw(XMMATRIX matView);

	bool IsDead() const { return isDead_; }	//死亡時

	XMFLOAT3 vector3Normalize(XMFLOAT3 vector_);
	float vector3Length(XMFLOAT3 vector_);

	int GetTexNum() { return texNum_; };

private:
	DirectXCommon* dxCommon_;
	Cube* cube_;
	std::vector<Object3d> object_;

	std::vector<XMFLOAT3> translation_;
	std::vector<XMFLOAT3> scale_;
	std::vector<XMFLOAT3> rotation_;

	std::vector<XMFLOAT3> velocity_;
	std::vector<XMFLOAT3> rotVector_;

	//デスフラグ
	bool isDead_ = false;
	int daedFlame_ = 0;

	int texNum_;
};

