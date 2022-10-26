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

	bool IsDead() const { return isDead_; }	//���S��
	int GetId() { return bulletId_; }
	void SetID(int ID) { bulletId_ = ID; }
	void SetFieldLane(int lane) { fieldLane_ = lane; };
	int GetFieldLane() { return fieldLane_; }
	Lane GetLane() { return lane_; };
	int GetTexNum() { return texNum_; };
	//�e�̃C�[�W���O
	float easeIn(float x);

	////���[���h���W���擾
	XMFLOAT3 GetWorldPosition() { return translation_; };

	//�Փ˂����o������Ăяo�����R�[���o�b�N�֐�
	void OnCollision(bool isBreak);

public:
	Cube* cube_;
	Input* input_ = nullptr;
	Object3d object_;
	DirectXCommon* dxCommon_;

	XMFLOAT3 translation_;
	XMFLOAT3 scale_;
	XMFLOAT3 rotation_;

	//�ŗLID
	int bulletId_ = 0;

	//�f�X�t���O
	bool isDead_ = false;

	float depth = 40.0f;	//���s
	float xDifference = 10.0f;	//���E��

	//�m�[�c�̑��x
	float kBulletSpeedZ = 0.4;
	//�m�[�c�̉����x
	float kBulletSpeedAcc = 0.003;

	//���݂̃��[��
	Lane lane_;

	//�t�B�[���h�擾�p
	int fieldLane_ = 0;

	//�F�ύX�p
	int texNum_;
};

