#include "Bullet.h"
#include <cmath>
#include "math.h"
#define PI 3.141592653589

void Bullet::Initialize(DirectXCommon* dxCommon, Cube* cube, XMFLOAT3 vector3, float kBulSpeed,  int texNum)
{
	this->dxCommon_ = dxCommon;
	this->cube_ = cube;

	texNum_ = texNum;
	//シングルインスタンスを取得する
	input_ = Input::GetInstance();

	translation_ = vector3;
	scale_ = { 1,1,1 };
	rotation_ = { 0,0,0 };

	//現在のXによってレーンを変更
	if (translation_.x < 0)
	{
		lane_ = Left;
	}
	else if (translation_.x == 0)
	{
		lane_ = Center;
	}
	else if (translation_.x > 0)
	{
		lane_ = Right;
	}

	InitializeObject3d(&object_, dxCommon->GetDevice());
}

void Bullet::Update(XMMATRIX& matView, XMMATRIX& matProjection, XMFLOAT3 vector3)
{
	translation_.x = vector3.x;
	translation_.y = vector3.y;

	//ノーツの速度の処理
	kBulletSpeedZ += kBulletSpeedAcc;
	XMFLOAT3 kBulletSpeed = { 0.0f,0.0f,-easeIn(kBulletSpeedZ) };
	translation_.x += kBulletSpeed.x;
	translation_.y += kBulletSpeed.y;
	translation_.z += kBulletSpeed.z;
	
	object_.position = translation_;
	object_.rotation = rotation_;
	object_.scale = scale_;

		UpdateObject3d(&object_, matView, matProjection);
}

void Bullet::Draw(XMMATRIX matView)
{
	DrawObject3d(&object_, dxCommon_->GetCommandList(), cube_->vbView, cube_->ibView, cube_->indices.size());
}

float Bullet::easeIn(float x)
{
	return 1 - cos((x * PI) / 2);
}

void Bullet::OnCollision(bool isBreak)
{
	isDead_ = true;
}
