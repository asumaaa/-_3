#include "Goal.h"
#include "Math.h"

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

	s += 0.02;
	translation_[0].y += cos(s) / 70;
	translation_[1].x += cos(s) / 70;
	translation_[2].y += cos(s + PI) / 70;
	translation_[3].x += cos(s + PI) / 70;

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

void Goal::MaterDown(bool isMaterDown)
{
	if (isMaterDown == true) {
		materDownTime_++;

		if (materDownTime_ >= 5) {
			materDownTime_ = 0;
			for (int i = 0; i < 3; i++) {
				if (bulletHit_[i] > 0) {
					bulletHit_[i]--;
				}
			}

		}

	}
}
XMFLOAT3 Goal::GetWorldPosition()
{
	XMFLOAT3 a = { 0,0,0 };
	
	for (int i = 0; i < 4; i++)
	{
		a.x += translation_[i].x;
		a.y += translation_[i].y;
		a.z += translation_[i].z;
	}
	a.x /= 4;
	a.y /= 4;
	a.z /= 4;


	return a;
}
