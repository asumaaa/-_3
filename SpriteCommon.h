#pragma once
#include "DirectXCommon.h"

class SpriteCommon
{
public:
	void Initialize(DirectXCommon *dxCommon);
	//�Q�b�^�[
	DirectXCommon GetDxCommon() { return *dxCommon_; }

private:
	DirectXCommon* dxCommon_;
};

