#pragma once
#include "WinApp.h"
#include "DirectXCommon.h"
#include "input.h"
#include "Masage.h"
#include "Texture.h"
#include "Sphere.h"

#include "string"
#include "DirectXMath.h"
//#include "d3dcompiler.h"
#include "dinput.h"
#include "assert.h"
#include "DirectXTex.h"
#include "object3D.h"

using namespace DirectX;
using namespace Microsoft::WRL;

//#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dinput8.lib")

//DirectX初期化用の変数
HRESULT result;

//カメラの回転角
float angle = 0.0f;

//座標
XMFLOAT3 position = { 0.0f,0.0f,-40.0f };

float x = 0;