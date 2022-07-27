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
#include "math.h"

#define PI 3.141592653589793238462643

using namespace DirectX;
using namespace Microsoft::WRL;

//頂点データ構造体
struct Vertex
{
	XMFLOAT3 pos;	//座標
	XMFLOAT3 normalize;	//法線ベクトル
	XMFLOAT2 uv;	//uv座標
	Vertex* parent = nullptr;
};

struct Indices
{
	int num;
};

class Ver
{
public:
	static Ver* GetInstance();
	void Initialize(XMFLOAT3 size);
public:
	Vertex vertices[24];
	unsigned short indices[36];
	UINT sizeVB;
	UINT sizeIB;
	D3D12_INPUT_ELEMENT_DESC inputLayout[3];//頂点レイアウト	xyz座標、法線ベクトル、uv座標の順番
};

class Ver2
{
public:
	static Ver2* GetInstance();
	void Initialize(XMFLOAT3 size);
public:
	Vertex vertices[12];
	unsigned short indices[12];
	UINT sizeVB;
	UINT sizeIB;
	D3D12_INPUT_ELEMENT_DESC inputLayout[3];//頂点レイアウト	xyz座標、法線ベクトル、uv座標の順番
};

const int fine = 64;	//球体の細かさ	変数宣言用
const int fine2 = fine * fine * 2;	//描画に使う頂点の数
const int fine3 = fine * fine * 3;	//インデックスの数
const int fine4 = fine * fine + fine;	//頂点の数

class Ver3
{
public:
	static Ver3* GetInstance();
	void Initialize(XMFLOAT3 size);
	void Update();
public:
	const float fineSize = fine;	//球体の細かさ
	Vertex vertices[fine2];	//外部に渡す用の頂点データ
	Vertex v[fine2], v2[fine4];	//計算用頂点データ
	unsigned short indices[fine3];
	UINT sizeVB;
	UINT sizeIB;
	D3D12_INPUT_ELEMENT_DESC inputLayout[3];//頂点レイアウト	xyz座標、法線ベクトル、uv座標の順番
};