#include "Effect.h"
#include "stdlib.h"

void Effect::Initialize(DirectXCommon* dxCommon, Cube* cube, XMFLOAT3 vector3)
{
	this->dxCommon_ = dxCommon;
	this->cube_ = cube;

	object_.resize(EFFECT_NUM);
	translation_.resize(EFFECT_NUM);
	scale_.resize(EFFECT_NUM);
	rotation_.resize(EFFECT_NUM);
	velocity_.resize(EFFECT_NUM);
	rotVector_.resize(EFFECT_NUM);

	float kMoveSpeed = 0.2f;	//スピード調整
	float kRotSpeed = 0.2f;

	//初期値をセット
	for (int i = 0; i < EFFECT_NUM; i++) {
		translation_[i] = vector3;
		scale_[i] = { 0.7,0.7,0.3 };
		rotation_[i] = { 0,0,0 };

		rotVector_[i] = { static_cast<float> (rand() % 20 - 10),
			static_cast<float> (rand() % 20 - 10) ,
			static_cast<float> (rand() % 20 - 10) };	//回転用
		rotVector_[i] = vector3Normalize(rotVector_[i]);

		velocity_[i] = { static_cast<float>(rand() % 20 - 10),
			static_cast<float>(rand() % 20 - 10) ,
			static_cast<float>(rand() % 20 - 10) };	//散布の方向
		velocity_[i] = vector3Normalize(velocity_[i]);

		rotVector_[i].x *= kRotSpeed;
		rotVector_[i].y *= kRotSpeed;
		rotVector_[i].z *= kRotSpeed;
		velocity_[i].x *= kMoveSpeed;
		velocity_[i].y *= kMoveSpeed;
		velocity_[i].z *= kMoveSpeed;

		InitializeObject3d(&object_[i], dxCommon->GetDevice());
	}
}

void Effect::Update(XMMATRIX& matView, XMMATRIX& matProjection)
{
	for (int i = 0; i < EFFECT_NUM; i++) {
		translation_[i].x += velocity_[i].x;
		translation_[i].y += velocity_[i].y;
		translation_[i].z += velocity_[i].z;
		rotation_[i].x += rotVector_[i].x;	//回転
		rotation_[i].y += rotVector_[i].y;	//回転
		rotation_[i].z += rotVector_[i].z;	//回転

		float kMinusScale = 0.04f;
		scale_[i].x += -kMinusScale;
		scale_[i].y += -kMinusScale;
		scale_[i].z += -kMinusScale;
		object_[i].position = translation_[i];
		object_[i].scale = scale_[i];
		object_[i].rotation = rotation_[i];

		float limitScale = 0.0f;
		if (scale_[i].x <= limitScale &&
			scale_[i].y <= limitScale &&
			scale_[i].z <= limitScale) {
			isDead_ = true;
		}

		UpdateObject3d(&object_[i], matView, matProjection);
	};	
}

void Effect::Draw(XMMATRIX matView)
{
	for (int i = 0; i < EFFECT_NUM; i++)
	{
		DrawObject3d(&object_[i], dxCommon_->GetCommandList(), cube_->vbView, cube_->ibView, cube_->indices.size());
	}
}

XMFLOAT3 Effect::vector3Normalize(XMFLOAT3 vector_)
{
	XMFLOAT3 v;
	v.x = vector_.x / vector3Length(vector_);
	v.y = vector_.y / vector3Length(vector_);
	v.z = vector_.z / vector3Length(vector_);

	return v;
}

float Effect::vector3Length(XMFLOAT3 vector_)
{
	float x2 = vector_.x * vector_.x;
	float y2 = vector_.y * vector_.y;
	float z2 = vector_.z * vector_.z;
	return sqrt(x2 + y2 + z2);
}