#pragma once
#include "memory"
#include "Input.h"
#include "WorldTransform.h"
#include "Object3d.h"
#include "Cube.h"
#include "Texture.h"
#include "DirectXCommon.h"

//���[���̗񋓌^
enum Lane
{
	Left,
	Center,
	Right
};

class Field
{
public:
	void Initialize(DirectXCommon* dxCommon,Cube* cube, Lane lane);	//���[����X���W�����߂ď�����
	void Draw(XMMATRIX matView, Texture* texture);
	void Update();
	//�Q�b�^�[
	XMFLOAT3 GetTransration() { return worldTransform_.translation_; };
	/*int GetLane() { return lane_; };

	void LaneChange();*/
private:

	DirectXCommon* dxCommon_;
	Input* input_ = nullptr;
	WorldTransform worldTransform_;
	Cube* cube_;
	Object3d* object_;

	float length = 200.0f;	//���[���̒���
	float zLen_ = 165.0f;	//okuyuki
	//���݂̃��[��
	Lane lane_;

	//���[���̕�
	float laneWidth = 10.0f;
	////�C�[�W���O�p
	//Ease* ease_ = nullptr;
	//bool isChangeRight_ = false;		//���[���`�F���W
	//bool isChangeLeft_ = false;
	//const int maxTime_ = 10;
	//int time_ = 0;


};