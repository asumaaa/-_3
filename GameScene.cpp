#include "GameScene.h"

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
	this->dxCommon = dxCommon;
	this->input = input;

	//球体モデル初期化
	Sphere* newSphere = new Sphere();
	newSphere->Initialize(size1,dxCommon);
	sphere_.reset(newSphere);

	//キューブモデル初期化
	Cube* newCube = new Cube();
	newCube->Initialize(size2, dxCommon);
	cube_.reset(newCube);



	//テクスチャ初期化
	laneTex_.resize(laneTexCount_);
	texImg_.resize(texImgCount_);
	//レーン画像
	for (int i = 0; i < laneTex_.size(); i++)
	{
		laneTex_[i].Initialize(dxCommon, i);
	}
	//背景画像
	for (int i = 0; i < texImg_.size(); i++)
	{
		texImg_[i].Initialize(L"Resources/backGround.png", dxCommon, 0);
	}


	//レーン初期化
	lane_.resize(laneCount);
	lane_[0].Initialize(dxCommon, cube_.get(), Left);
	lane_[1].Initialize(dxCommon, cube_.get(), Center);
	lane_[2].Initialize(dxCommon, cube_.get(), Right);

	goal_.Initialize(dxCommon, cube_.get());

	//オブジェクト初期化
	object3ds_.resize(kObjectCount);
	objectBackGround_.resize(backGroundCount);
	for (int i = 0; i < object3ds_.size(); i++)
	{
		//初期化
		InitializeObject3d(&object3ds_[i], dxCommon->GetDevice());
		object3ds_[i].scale = { 1,10.0f,1 };
		object3ds_[i].rotation = { 0.0f,0.0f,0.0f };
		object3ds_[0].position = { -10.0f,0.0f,-60.0f };
		object3ds_[1].position = { 10.0f,0.0f,-60.0f };
	}
	InitializeObject3d(&objectBackGround_[0], dxCommon->GetDevice());
	objectBackGround_[0].scale = { window_width  * 0.4f,window_height  * 0.4f,1.0f };
	objectBackGround_[0].rotation = { 0.4f,0.0f,0.0f };
	objectBackGround_[0].position = { 0.0f,-250.0f,600.0f };

	//カメラ初期化
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}

void GameScene::Update()
{
	//レーン更新
	for (int i = 0; i < lane_.size() ;i++)
	{
		lane_[i].Update(matView, matProjection);
	}

	//ゴール更新
	goal_.Update(matView, matProjection);

	//オブジェクト更新
	for (int i = 0; i < object3ds_.size(); i++)
	{
		UpdateObject3d(&object3ds_[i], matView, matProjection);
	}
	UpdateObject3d(&objectBackGround_[0], matView, matProjection);
}

void GameScene::Draw()
{
	sphere_->Update();
	cube_->Update();

	for (int i = 0; i < laneTex_.size(); i++)
	{
		laneTex_[0].SetImageData(XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f));
		laneTex_[1].SetImageData(XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f));
		laneTex_[2].SetImageData(XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f));
	}

	texImg_[0].Draw();
	DrawObject3d(&objectBackGround_[0], dxCommon->GetCommandList(), cube_->vbView, cube_->ibView, cube_->indices.size());

	//レーン描画
	for (int i = 0; i < lane_.size(); i++)
	{
		laneTex_[i].Draw();
		lane_[i].Draw(matView);
	}

	//ゴール描画
	laneTex_[0].Draw();
	goal_.Draw(matView);
}
