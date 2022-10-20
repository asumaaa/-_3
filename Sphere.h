#pragma once
#include "DirectXCommon.h"
#include "Vertex.h"
#include "IndexBuff.h"
#include "VertBuff.h"
#include "Shader.h"
#include "RootSig.h"
#include "Pipe.h"
#include "d3d12.h"
#include "Gravity.h"

class Sphere
{
public:
	static Sphere* GetInstance();
	void Initialize(XMFLOAT3 size, DirectXCommon* dx_, const wchar_t* file,const wchar_t* file2);
	void Update(XMFLOAT3 size,const wchar_t* file, const wchar_t* file2);
public:
	Ver3* vertex = nullptr;
	IndexBuff indexBuff;
	VertBuff vertBuff;
	Shader shader;
	RootSig rootSig;
	Pipe pipe;
	DirectXCommon* dx;
	ComPtr<ID3D12PipelineState> pipelineState;
	ComPtr<ID3D12Resource> constBuffMaterial;
public:
	D3D12_RECT scissorRect{};
	D3D12_VIEWPORT viewport{};
};

