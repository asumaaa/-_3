
#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

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
	texture_.resize(textureCount_);	
	for (int i = 0; i < texture_.size(); i++)
	{
		texture_[i].Initialize(dxCommon, i);
	}
	texImg_.resize(texImgCount_);
	for (int i = 0; i < texImgCount_; i++)
	{
		texImg_[0].Initialize(L"Resource/backGround.png", dxCommon, i);
	}

	//オブジェクト初期化
	objectBackGround_.resize(backGroundCount);
	InitializeObject3d(&objectBackGround_[0], dxCommon->GetDevice());
	InitializeObject3d(&objectBackGround_[1], dxCommon->GetDevice());
	objectBackGround_[0].scale = { 10.0f,10.0f,10.0f };
	objectBackGround_[0].rotation = { 0.0f,0.0f,0.0f };
	objectBackGround_[0].position = { -10.0f,0.0f,-60.0f };
	objectBackGround_[1].scale = { 10.0f,10.0f,10.0f };
	objectBackGround_[1].rotation = { 0.0f,0.0f,0.0f };
	objectBackGround_[1].position = { -10.0f,0.0f,-60.0f };

	//カメラ初期化
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}

void GameScene::Update()
{
	//オブジェクトの更新
	UpdateObject3d(&objectBackGround_[0], matView, matProjection);
	UpdateObject3d(&objectBackGround_[1], matView, matProjection);
}

void GameScene::Draw()
{
	sphere_->Update();
	cube_->Update();

	/*texture_[0].SetImageData(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	texture_[0].Draw();
	DrawObject3d(&object3ds_[0], dxCommon->GetCommandList(), sphere_->vbView, sphere_->ibView, sphere_->indices.size());

	texture_[1].SetImageData(XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f));
	texture_[1].Draw();
	texture_[2].Draw();*/

	texture_[1].SetImageData(XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f));
	texImg_[0].Draw();
	DrawObject3d(&objectBackGround_[0], dxCommon->GetCommandList(), cube_->vbView, cube_->ibView, cube_->indices.size());
	DrawObject3d(&objectBackGround_[1], dxCommon->GetCommandList(), sphere_->vbView, sphere_->ibView, sphere_->indices.size());
}
