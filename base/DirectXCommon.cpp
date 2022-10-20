#include "DirectXCommon.h"

DirectXCommon* DirectXCommon::GetInstance()
{
	static DirectXCommon instance;
	return &instance;
}

void DirectXCommon::Initialize(WinApp* winApp)
{
	winApp_ = winApp;
	HRESULT result;

	//�f�o�C�X������
	InitializeDevice();
	//�R�}���h���X�g������
	InitializeCommand();
	//�X���b�v�`�F�[��������
	InitializeSwapchain();
	//�����_�[�^�[�Q�b�g�r���[������
	InitializeRenderTargetView();
	//�t�F���X����
	InitializeFence();
}

#pragma region �f�o�C�X������
void DirectXCommon::InitializeDevice()
{
	HRESULT result;
	
	#ifdef _DEBUG
		//�f�o�b�O���C���[���I����
		if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
		{
			debugController->EnableDebugLayer();
		}
	
	#endif
	
		//DXGI�t�@�N�g���[�̐���
		result = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
		assert(SUCCEEDED(result));
	
		//�A�_�v�^�[
		//�p�t�H�[�}���X���������̂��珇�ɁA���ׂẴA�_�v�^�[��񋓂���
		for (UINT i = 0;
			dxgiFactory->EnumAdapterByGpuPreference(
				i,
				DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE,
				IID_PPV_ARGS(&tmpAdapter)) != DXGI_ERROR_NOT_FOUND;
			i++)
		{
			//���I�z��ɒǉ�����
			adapters.push_back(tmpAdapter);
		}
	
		//�Ó��ȃA�_�v�^�[��I�ʂ���
		for (size_t i = 0; i < adapters.size(); i++)
		{
			DXGI_ADAPTER_DESC3 adapterDesc;
			//�A�_�v�^�[�̏����擾����
			adapters[i]->GetDesc3(&adapterDesc);
	
			//�\�t�g�E�F�A�f�o�C�X�����
			if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE))
			{
				//�f�o�C�X���̗p���ă��[�v�𔲂���
				tmpAdapter = adapters[i];
				break;
			}
		}
	
		//�Ή����x���̐���
		D3D_FEATURE_LEVEL levels[] =
		{
			D3D_FEATURE_LEVEL_12_1,
			D3D_FEATURE_LEVEL_12_0,
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
		};
	
		D3D_FEATURE_LEVEL featureLevel;
	
		for (size_t i = 0; i < _countof(levels); i++)
		{
			//�̗p�����A�_�v�^�[���f�o�C�X�Ő���
			result = D3D12CreateDevice(tmpAdapter.Get(), levels[i],
				IID_PPV_ARGS(&device));
			if (result == S_OK)
			{
				//�f�o�C�X�����ł������_�Ń��[�v�𔲂���
				featureLevel = levels[i];
				break;
			}
		}
}
#pragma endregion
#pragma region �R�}���h���X�g������
void DirectXCommon::InitializeCommand()
{
	HRESULT result;
	//�R�}���h�A���P�[�^�𐶐�
	result = device->CreateCommandAllocator(
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		IID_PPV_ARGS(&commandAllocator));
	assert(SUCCEEDED(result));

	//�R�}���h���X�g�𐶐�
	result = device->CreateCommandList(
		0,
		D3D12_COMMAND_LIST_TYPE_DIRECT,
		commandAllocator.Get(),
		nullptr,
		IID_PPV_ARGS(&commandList));
	assert(SUCCEEDED(result));

	//�R�}���h�L���[�ɐݒ�
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
	//�R�}���h�L���[�𐶐�
	result = device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&commandQueue));
	assert(SUCCEEDED(result));
}
#pragma endregion
#pragma region �X���b�v�`�F�[��
void DirectXCommon::InitializeSwapchain()
{
	HRESULT result;
	//�X���b�v�`�F�[���̐ݒ�
	swapChainDesc.Width = window_width;
	swapChainDesc.Height = window_height;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	//�F���̏���
	swapChainDesc.SampleDesc.Count = 1;					//�}���`�T���v�����O���Ȃ�
	swapChainDesc.BufferUsage = DXGI_USAGE_BACK_BUFFER;	//�o�b�N�o�b�t�@�p
	swapChainDesc.BufferCount = 2;						//�o�b�t�@����2�ɐݒ�
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;	//�t���b�v��͔j��
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	ComPtr<IDXGISwapChain1>swapchain1;

	//�X���b�v�`�F�[���̐��� 
	result = dxgiFactory->CreateSwapChainForHwnd(
		commandQueue.Get(),
		winApp_->hwnd,
		&swapChainDesc,
		nullptr,
		nullptr,
		&swapchain1);

	swapchain1.As(&swapChain);
	assert(SUCCEEDED(result));
}
#pragma endregion
#pragma region �����_�[�^�[�Q�b�g�r���[ 
void DirectXCommon::InitializeRenderTargetView()
{
	// �f�X�N���v�^�q�[�v�̐ݒ� 
	rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV; // �����_�[�^�[�Q�b�g�r���[ 
	rtvHeapDesc.NumDescriptors = swapChainDesc.BufferCount; //���\�̓��

	// �f�X�N���v�^�q�[�v�̐��� 
	device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));

	//�o�b�N�o�b�t�@
	backBuffers.resize(swapChainDesc.BufferCount);

	//�X���b�v�`�F�[���̑S�Ẵo�b�t�@�ɂ��ď�������
	for (size_t i = 0; i < backBuffers.size(); i++)
	{
		//�X���b�v�`�F�[������o�b�t�@���擾
		swapChain->GetBuffer((UINT)i, IID_PPV_ARGS(&backBuffers[i]));
		//�f�X�N���v�^�q�[�v�̃n���h�����擾
		D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = rtvHeap->GetCPUDescriptorHandleForHeapStart();
		//�����\�ŃA�h���X�������
		rtvHandle.ptr += i * device->GetDescriptorHandleIncrementSize(rtvHeapDesc.Type);
		//�����_�[�^�[�Q�b�g�r���[�̐ݒ�
		D3D12_RENDER_TARGET_VIEW_DESC rtvDesc{};
		//�V�F�[�_�[�̌v�Z���ʂ�SRGB�ɕϊ����ď�������
		rtvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
		rtvDesc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
		//�����_�[�^�[�Q�b�g�r���̐���
		device->CreateRenderTargetView(backBuffers[i].Get(), &rtvDesc, rtvHandle);
	}
}
#pragma endregion
void DirectXCommon::InitializeDepthBuffer()
{
}
#pragma region �t�F���X
void DirectXCommon::InitializeFence()
{
	HRESULT result;
	//�t�F���X�̐���
	result = device->CreateFence(fenceVal, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
}
#pragma endregion

void DirectXCommon::PreDraw()
{
}

void DirectXCommon::PostDraw()
{
}