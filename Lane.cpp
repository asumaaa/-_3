#include "Lane.h"

void Field::Initialize(DirectXCommon* dxCommon,Cube* cube, Lane lane)
{
	this->dxCommon_ = dxCommon;
	this->cube_ = cube;

	//シングルトンインスタンスを取得
	input_ = Input::GetInstance();
	scale_ = { 0.3f,0.2f,length };
	rotation_ = { 0.0f,0.0f,0.0f };
	//x座標に応じて現在のレーンを判定
	lane_ = lane;

	if (lane == Left)
	{
		translation_ = { -laneWidth,0.0f,zLen_ };
	}
	else if (lane == Center)
	{
		translation_ = { 0.0f,0.0f,zLen_ };
	}
	else if (lane == Right)
	{
		translation_ = { laneWidth,0.0f,zLen_ };
	}

	//オブジェクト初期化
	InitializeObject3d(&object_, dxCommon->GetDevice());
}

void Field::Draw(XMMATRIX matView)
{
	DrawObject3d(&object_, dxCommon_->GetCommandList(), cube_->vbView, cube_->ibView, cube_->indices.size());
}

void Field::Update(XMMATRIX& matView, XMMATRIX& matProjection)
{
	object_.position = translation_;
	object_.rotation = rotation_;
	object_.scale = scale_;

	UpdateObject3d(&object_, matView, matProjection);
}
