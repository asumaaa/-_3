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
	void InitializeVertex(XMFLOAT3 size);	//���_������
	void InitializeIndexBuff();				//�C���f�b�N�X�o�b�t�@������	
	void InitializeVertBuff();				//���_�o�b�t�@������
	void CompileShader(const wchar_t* file, const wchar_t* file2);	//�V�F�[�_�ǂݍ���
	void InitializeRootSignature();			//���[�g�V�O�l�`��
	void InitializePipeline();				//�p�C�v���C��
	void InitializePipelineState();			//�p�C�v���C���X�e�[�g
	void Update();

public:
	//���_�f�[�^�\����
	struct Vertex
	{
		XMFLOAT3 pos;	//���W
		XMFLOAT2 uv;	//uv
		Vertex* parent = nullptr;
	};
	struct Indices
	{
		int num;
	};

	//�f�o�C�X
	DirectXCommon* dxCommon_;
	//���_�֘A
	size_t verticesCount = 4;
	std::vector<Vertex> vertices;
	UINT sizeVB;	//���_�f�[�^�T�C�Y
	//�C���f�b�N�X�֘A
	size_t indicesCount = 6;
	std::vector<unsigned short> indices;
	UINT sizeIB;	//�C���f�b�N�X�f�[�^�T�C�Y
	//���_���C�A�E�g
	D3D12_INPUT_ELEMENT_DESC inputLayout[2];	//xyz���W�A�@���x�N�g���Auv���W�̏���
	//�C���f�b�N�X�o�b�t�@�֘A
	ComPtr<ID3D12Resource> indexBuff;
	D3D12_INDEX_BUFFER_VIEW ibView{};
	//���_�o�b�t�@������
	ComPtr<ID3D12Resource> vertBuff;
	D3D12_VERTEX_BUFFER_VIEW vbView{};		//���_�o�b�t�@�r���[
	//�V�F�[�_�֘A
	ID3DBlob* vsBlob;	//���_�V�F�[�_�[�I�u�W�F�N�g
	ID3DBlob* psBlob;	//�s�N�Z���V�F�[�_�[�I�u�W�F�N�g
	ID3DBlob* errorBlob;	//�G���[�I�u�W�F�N�g
	//���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootSignature;
	//�p�C�v���C��
	D3D12_GRAPHICS_PIPELINE_STATE_DESC pipelineDesc{};	//�O���t�B�b�N�X�p�C�v���C��
	D3D12_STATIC_SAMPLER_DESC samplerDesc{};


	ComPtr<ID3D12PipelineState> pipelineState;
	ComPtr<ID3D12Resource> constBuffMaterial;
	D3D12_RECT scissorRect{};
	D3D12_VIEWPORT viewport{};
};

