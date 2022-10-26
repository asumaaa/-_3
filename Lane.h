#pragma once
#include "memory"
#include "Input.h"
#include "WorldTransform.h"
#include "Object3d.h"
#include "Cube.h"
#include "Texture.h"
#include "DirectXCommon.h"
#include "Ease.h"

//レーンの列挙型
enum Lane
{
	Left,
	Center,
	Right
};

class Field
{
public:
	void Initialize(DirectXCommon* dxCommon,Cube* cube, Lane lane, Input* input);	//レーンのX座標を決めて初期化
	void Draw(XMMATRIX matView);
	void Update(XMMATRIX& matView, XMMATRIX& matProjection);
	//ゲッター
	XMFLOAT3 GetTransration() { return translation_; };
	Lane GetLane() { return lane_; };
private:

	DirectXCommon* dxCommon_;
	Input* input_ = nullptr;
	XMFLOAT3 translation_;
	XMFLOAT3 scale_;
	XMFLOAT3 rotation_;
	Cube* cube_;
	Object3d object_;

	float length = 200.0f;	//レーンの長さ
	float zLen_ = 165.0f;	//okuyuki
	//現在のレーン
	Lane lane_;

	//レーンの幅
	float laneWidth = 10.0f;
	//イージング用
	Ease* ease_ = nullptr;
	bool isChangeRight_ = false;		//レーンチェンジ
	bool isChangeLeft_ = false;
	const int maxTime_ = 10;
	int time_ = 0;


};