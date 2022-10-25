#pragma once
#include "DirectXCommon.h"

class SpriteCommon
{
public:
	void Initialize(DirectXCommon *dxCommon);
	//ÉQÉbÉ^Å[
	DirectXCommon GetDxCommon() { return *dxCommon_; }

private:
	DirectXCommon* dxCommon_;
};

