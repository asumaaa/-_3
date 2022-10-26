#include "Goal.h"

#define PI 3.141592653589

void Goal::Initialize(DirectXCommon* dxCommon, Cube* cube)
{
	this->dxCommon_ = dxCommon;
	this->cube_ = cube;
	//シングルトンインスタンスを取得
	input_ = Input::GetInstance();

	for (int i = 0; i < 4; i++) {
		translation_[i] = { 0,0,-38 };
		scale_[i] = { 0.5,0.2,0.2  };
	}
	rotation_[0] = {0,0,0};
	rotation_[1] = {0,0,PI * 3 / 2};
	rotation_[2] = {0,0,PI};
	rotation_[3] = {0,0,PI / 2};

	//オブジェクト初期化
	for (int i = 0; i < 4; i++)
	{
		InitializeObject3d(&object_[i], dxCommon->GetDevice());
	}
}


void Goal::Update(XMMATRIX& matView, XMMATRIX& matProjection)
{
	modelVelocityAngle_++;
	if (modelVelocityAngle_ > 360) {
		modelVelocityAngle_ = 0;
	}

	//for (int i = 0; i < 4; i++) {

	//	XMFLOAT3 kVec = { 0,sinf(modelVelocityAngle_ * PI / 180.0f) + 2.4f,0 };

	//	XMFLOAT3 result = { 0, 0, 0 };


	//	result.x = kVec.x * worldTransform.matWorld_.m[0][0] +
	//		kVec.y * worldTransform.matWorld_.m[1][0] +
	//		kVec.z * worldTransform.matWorld_.m[2][0];

	//	result.y = kVec.x * worldTransform.matWorld_.m[0][1] +
	//		kVec.y * worldTransform.matWorld_.m[1][1] +
	//		kVec.z * worldTransform.matWorld_.m[2][1];

	//	result.z = kVec.x * worldTransform.matWorld_.m[0][2] +
	//		kVec.y * worldTransform.matWorld_.m[1][2] +
	//		kVec.z * worldTransform.matWorld_.m[2][2];

	//	translation_[i] = {kVec.x,kVec.y,-38};
	//}

	for (int i = 0; i < 4; i++)
	{
		object_[i].position = translation_[i];
		object_[i].rotation = rotation_[i];
		object_[i].scale = scale_[i];

		UpdateObject3d(&object_[i], matView, matProjection);
	}
}

void Goal::Draw(XMMATRIX matView)
{
	for (int i = 0; i < 4; i++)
	{
		DrawObject3d(&object_[i], dxCommon_->GetCommandList(), cube_->vbView, cube_->ibView, cube_->indices.size());
	}
}
