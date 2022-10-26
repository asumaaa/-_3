#pragma once
#include "Input.h"
#include "Cube.h"
#include "DirectXMath.h"
#include "DirectXCommon.h"
#include "list"
#include "cassert"
#include "Lane.h"

class Bullet
{
public:
	void Initialize(DirectXCommon* dxCommon, Cube* cube, XMFLOAT3 vector3, float kBulSpeed, int texNum);
	void Update(XMMATRIX& matView, XMMATRIX& matProjection, XMFLOAT3 vector3);
	void Draw(XMMATRIX matView);

	bool IsDead() const { return isDead_; }	//死亡時
	int GetId() { return bulletId_; }
	void SetID(int ID) { bulletId_ = ID; }
	void SetFieldLane(int lane) { fieldLane_ = lane; };
	int GetFieldLane() { return fieldLane_; }
	Lane GetLane() { return lane_; };
	int GetTexNum() { return texNum_; };
	//弾のイージング
	float easeIn(float x);

	////ワールド座標を取得
	XMFLOAT3 GetWorldPosition() { return translation_; };

	//衝突を検出したら呼び出されるコールバック関数
	void OnCollision(bool isBreak);

public:
	Cube* cube_;
	Input* input_ = nullptr;
	Object3d object_;
	DirectXCommon* dxCommon_;

	XMFLOAT3 translation_;
	XMFLOAT3 scale_;
	XMFLOAT3 rotation_;

	//固有ID
	int bulletId_ = 0;

	//デスフラグ
	bool isDead_ = false;

	float depth = 40.0f;	//奥行
	float xDifference = 10.0f;	//左右差

	//ノーツの速度
	float kBulletSpeedZ = 0.4;
	//ノーツの加速度
	float kBulletSpeedAcc = 0.003;

	//現在のレーン
	Lane lane_;

	//フィールド取得用
	int fieldLane_ = 0;

	//色変更用
	int texNum_;
};

