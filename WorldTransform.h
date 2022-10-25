#pragma once
#include "Windows.h"
#include "d3d12.h"
#include "dxgi1_6.h"
#include "cassert"
#include "vector"
#include "string"
#include "DirectXMath.h"
#include "assert.h"
#include "DirectXTex.h"
#include "wrl.h"

using namespace DirectX;
using namespace Microsoft::WRL;

class WorldTransform
{
public:
	WorldTransform(XMFLOAT3 translation, XMFLOAT3 scale, XMFLOAT3 rotation);
public:
	XMFLOAT3 translation_;
	XMFLOAT3 scale_;
	XMFLOAT3 rotation_;
};

