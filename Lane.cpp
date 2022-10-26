#include "Lane.h"

void Field::Initialize(DirectXCommon* dxCommon,Cube* cube, Lane lane,Input *input)
{
	this->dxCommon_ = dxCommon;
	this->cube_ = cube;
	this->input_ = input;

	////�V���O���g���C���X�^���X���擾
	//input_ = Input::GetInstance();
	
	//�傫���p�x������
	scale_ = { 0.3f,0.2f,length };
	rotation_ = { 0.0f,0.0f,0.0f };
	//x���W�ɉ����Č��݂̃��[���𔻒�
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

	//�C�[�W���O
	ease_ = new Ease;

	//�I�u�W�F�N�g������
	InitializeObject3d(&object_, dxCommon->GetDevice());
}

void Field::Draw(XMMATRIX matView)
{
	DrawObject3d(&object_, dxCommon_->GetCommandList(), cube_->vbView, cube_->ibView, cube_->indices.size());
}

void Field::Update(XMMATRIX& matView, XMMATRIX& matProjection)
{
	//�L�[���͂ɉ�����Lane��ύX
	if (input_->key(DIK_LEFT) && input_->key(DIK_SPACE)
		&& isChangeLeft_ == false && isChangeRight_ == false)
	{
		/*if (lane_ == Left)lane_ = Center;
		else if (lane_ == Center)lane_ = Left;*/
		isChangeLeft_ = true;

	}
	else if (input_->PushKey(DIK_RIGHT) && input_->TriggerKey(DIK_SPACE)
		&& isChangeLeft_ == false && isChangeRight_ == false)
	{
		/*if (lane_ == Right)lane_ = Center;
		else if (lane_ == Center)lane_ = Right;*/
		isChangeRight_ = true;
	}

	if (time_ >= maxTime_) {	//�^�C�����Z�b�g
		time_ = 0;
		if (isChangeLeft_ == true) {
			isChangeLeft_ = false;
			if (lane_ == Left) {
				lane_ = Center;
			}
			else if (lane_ == Center) {
				lane_ = Left;
			}
		}
		if (isChangeRight_ == true) {
			isChangeRight_ = false;
			if (lane_ == Right) {
				lane_ = Center;
			}
			else if (lane_ == Center) {
				lane_ = Right;
			}
		}

		if (lane_ == Left)
		{
			worldTransform_.translation_ = { -laneWidth,0.0f,zLen_ };
		}
		else if (lane_ == Center)
		{
			worldTransform_.translation_ = { 0.0f,0.0f,zLen_ };
		}
		else if (lane_ == Right)
		{
			worldTransform_.translation_ = { laneWidth,0.0f,zLen_ };
		}
	}


	if (isChangeLeft_ == true) {
		time_++;
		if (lane_ == Left) {
			worldTransform_.translation_.x = ease_->InOutQuad(laneWidth, -laneWidth, maxTime_, time_);
		}
		if (lane_ == Center) {
			worldTransform_.translation_.x = ease_->InOutQuad(-laneWidth, 0.0f, maxTime_, time_);
		}

	}
	else if (isChangeRight_ == true) {
		time_++;
		if (lane_ == Right) {
			worldTransform_.translation_.x = ease_->InOutQuad(-laneWidth, laneWidth, maxTime_, time_);
		}
		if (lane_ == Center) {
			worldTransform_.translation_.x = ease_->InOutQuad(laneWidth, 0.0f, maxTime_, time_);
		}
	}


	object_.position = translation_;
	object_.rotation = rotation_;
	object_.scale = scale_;

	UpdateObject3d(&object_, matView, matProjection);
}
