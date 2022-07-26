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

	const int fine = 48;	//球体の細かさ	変数宣言用
class Ver3
{
public:
	static Ver3* GetInstance();
	void Initialize(XMFLOAT3 size);
	void Update();
public:
	const float fineSize = 48;	//球体の細かさ
	Vertex vertices[4 * 48 * 48];
	Vertex vertices2[48 * 48];
	unsigned short indices[6 * 48 * 48];
	UINT sizeVB;
	UINT sizeIB;
	D3D12_INPUT_ELEMENT_DESC inputLayout[3];//頂点レイアウト	xyz座標、法線ベクトル、uv座標の順番
};