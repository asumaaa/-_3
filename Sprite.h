#pragma once
#include "SpriteCommon.h"
#include "DirectXCommon.h"
#include "Object3D.h"
#include "d3d12.h"
#include "list"
#include "vector"
#include "d3dcompiler.h"

using namespace DirectX;
using namespace Microsoft::WRL;

#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"dinput8.lib")

#define PI 3.14159265359

class Sprite
{
public:
	void Initialize(XMFLOAT3 size, DirectXCommon* dxCommon);
	void InitializeVertex(XMFLOAT3 size);	//頂点初期化
	void InitializeIndexBuff();				//インデックスバッファ初期化	
	void InitializeVertBuff();				//頂点バッファ初期化
	void CompileShader(const wchar_t* file, const wchar_t* file2);	//シェーダ読み込み
	void InitializeRootSignature();			//ルートシグネチャ
	void InitializePipeline();				//パイプライン
	void InitializePipelineState();			//パイプラインステート
	void Update();

public:
	//頂点データ構造体
	struct Vertex
	{
		XMFLOAT3 pos;	//座標
		XMFLOAT2 uv;	//uv
		Vertex* parent = nullptr;
	};
	struct Indices
	{
		int num;
	};

	//デバイス
	DirectXCommon* dxCommon_;
	//頂点関連
	size_t verticesCount = 4;
	std::vector<Vertex> vertices;
	UINT sizeVB;	//頂点データサイズ
	//インデックス関連
	size_t indicesCount = 6;
	std::vector<unsigned short> indices;
	UINT sizeIB;	//インデックスデータサイズ
	//頂点レイアウト
	D3D12_INPUT_ELEMENT_DESC inputLayout[2];	//xyz座標、法線ベクトル、uv座標の順番
	//インデックスバッファ関連
	ComPtr<ID3D12Resource> indexBuff;
	D3D12_INDEX_BUFFER_VIEW ibView{};
	//頂点バッファ初期化
	ComPtr<ID3D12Resource> vertBuff;
	D3D12_VERTEX_BUFFER_VIEW vbView{};		//頂点バッファビュー
	//シェーダ関連
	ID3DBlob* vsBlob;	//頂点シェーダーオブジェクト
	ID3DBlob* psBlob;	//ピクセルシェーダーオブジェクト
	ID3DBlob* errorBlob;	//エラーオブジェクト
	//ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootSignature;
	//パイプライン
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};	//グラフィックスパイプライン
	D3D12_STATIC_SAMPLER_DESC samplerDesc{};


	ComPtr<ID3D12PipelineState> pipelineState;
	ComPtr<ID3D12Resource> constBuffMaterial;
	D3D12_RECT scissorRect{};
	D3D12_VIEWPORT viewport{};
};

