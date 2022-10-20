#include "main.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//�E�B���h�E����
	WinApp* win = nullptr;
	win = WinApp::GetInstance();
	win->CreateWindow_(L"DirectX");

	Masage* masage;	//���b�Z�[�W
	masage = Masage::GetInstance();

	//DirectX����������
	DirectXCommon* dx = nullptr;
	dx = DirectXCommon::GetInstance();
	dx->Initialize(win);

	//�L�[�{�[�h
	Input* input = nullptr;
	input = Input::GetInstance();
	input->Initialize(win);

#pragma region �`�揈��������
	XMFLOAT3 size1 = { 1.0f,1.0f,1.0f };
	Sphere sphere;
	sphere.Initialize(size1, dx, L"BasicVS.hlsl", L"BasicPS.hlsl");

	////���\�[�X�ݒ�
	//D3D12_RESOURCE_DESC depthResorceDesc{};
	//depthResorceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	//depthResorceDesc.Width = window_width;	//�����_�[�^�[�Q�b�g�ɍ��킹��
	//depthResorceDesc.Height = window_height;	//�����_�[�^�[�Q�b�g�ɍ��킹��
	//depthResorceDesc.DepthOrArraySize = 1;
	//depthResorceDesc.Format = DXGI_FORMAT_D32_FLOAT;	//�[�x�l�t�H�[�}�b�g
	//depthResorceDesc.SampleDesc.Count = 1;
	//depthResorceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;	//�f�v�X�X�e���V��

	////�k�x�l�p�q�[�v�v���p�e�B
	//D3D12_HEAP_PROPERTIES depthHeapProp{};
	//depthHeapProp.Type = D3D12_HEAP_TYPE_DEFAULT;
	////�[�x�l�̃N���A�ݒ�
	//D3D12_CLEAR_VALUE depthClearValue{};
	//depthClearValue.DepthStencil.Depth = 1.0f;	//�[�x�l1.0f(�ő�l)�ŃN���A
	//depthClearValue.Format = DXGI_FORMAT_D32_FLOAT;	//�[�x�l�t�H�[�}�b�g

	////���\�[�X����
	//ComPtr<ID3D12Resource> depthBuff;
	//result = dx->GetDevice()->CreateCommittedResource(
	//	&depthHeapProp,
	//	D3D12_HEAP_FLAG_NONE,
	//	&depthResorceDesc,
	//	D3D12_RESOURCE_STATE_DEPTH_WRITE,	//�[�x�l�������݂Ɏg�p
	//	&depthClearValue,
	//	IID_PPV_ARGS(&depthBuff)
	//);

	////�[�x�r���[�p�f�X�N���v�^�q�[�v�쐬
	//D3D12_DESCRIPTOR_HEAP_DESC dsvHeapDesc{};
	//dsvHeapDesc.NumDescriptors = 1;	//�[�x�r���[��1��
	//dsvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;	//�f�v�X�X�e���V���r���[
	//ComPtr<ID3D12DescriptorHeap> dsvHeap;
	//result = dx->GetDevice()->CreateDescriptorHeap(&dsvHeapDesc, IID_PPV_ARGS(&dsvHeap));

	////�[�x�X�e���V���r���[�̐���
	//D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc = {};
	//dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;	//�[�x�l�t�H�[�}�b�g
	//dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	//dx->GetDevice()->CreateDepthStencilView(
	//	depthBuff.Get(),
	//	&dsvDesc,
	//	dsvHeap->GetCPUDescriptorHandleForHeapStart()
	//);

	//�ǂݍ��މ摜�̐�
	const size_t metadataCount = 2;
	//�摜
	Texture texture[metadataCount];
	//������
	texture[0].Initialize(dx, 0);
	texture[1].Initialize(dx, 1);


	//3D�I�u�W�F�N�g�̐�
	const size_t kObjectCount = 2;
	//3D�I�u�W�F�N�g�̔z��
	Object3d object3ds[kObjectCount];
	object3ds[0].position = { 0.0f,0.0f,-60.0f };

	//�z������ׂẴI�u�W�F�N�g�ɑ΂���
	for (int i = 0; i < _countof(object3ds); i++)
	{
		//������
		InitializeObject3d(&object3ds[i], dx->GetDevice());
			object3ds[i].scale = { 10.0f,10.0f,10.0f };
			object3ds[i].rotation = { 0.0f,0.0f,0.0f };
	}

	//�ˉe�ϊ�
	XMMATRIX matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(45.0f),			//�㉺��p45�x
		(float)window_width / window_height,//�A�X�y�N�g��(��ʉ���/��ʗ���)
		0.1f, 1000.0f						//�O�[�A���[
	);

	//�r���[�ϊ��s��
	XMMATRIX matView;
	XMFLOAT3 eye(0, 0, -100);
	XMFLOAT3 target(0, 0, 0);
	XMFLOAT3 up(0, 1, 0);
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

#pragma endregion

	//�Q�[�����[�v
	while (true)
	{
		//���b�Z�[�W������H
		masage->Update();

#pragma region DirectX���t���[������

		//�L�[�{�[�h�X�V
		input->Update();

		for (int i = 0; i < _countof(object3ds); i++)
		{
			UpdateObject3d(&object3ds[i], matView, matProjection);
		}


		//���W���ړ����鏈��
		if (input->key[DIK_1])
		{
			sphere.pipe.pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;	//�J�����O���Ȃ�
		}
		if (input->key[DIK_2])
		{
			sphere.pipe.pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;	//�J�����O���Ȃ�
		}
		if (input->key[DIK_3])
		{
			sphere.pipe.pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;	//�|���S���h��Ԃ�
		}
		if (input->key[DIK_4])
		{
			sphere.pipe.pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;	//�|���S���h��Ԃ�
		}

		////�o�b�N�o�b�t�@�̔ԍ����擾(2�Ȃ̂�0�Ԃ�1��)
		//UINT bbIndex = dx->GetSwapChain()->GetCurrentBackBufferIndex();

		//// 1. ���\�[�X�o���A�ɏ������݉\�ɕύX
		//D3D12_RESOURCE_BARRIER barrierDesc{};
		//barrierDesc.Transition.pResource = dx->backBuffers[bbIndex].Get();	//�o�b�N�o�b�t�@���w��
		//barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;	//�\����Ԃ���
		//barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;	//�`���Ԃ�
		//dx->GetCommandList()->ResourceBarrier(1, &barrierDesc);

		//// 2. �`���̕ύX
		//// �����_�[�^�[�Q�b�g�r���[�̃n���h�����擾
		//D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = dx->GetRtvHeap()->GetCPUDescriptorHandleForHeapStart();
		//rtvHandle.ptr += bbIndex * dx->GetDevice()->GetDescriptorHandleIncrementSize(dx->rtvHeapDesc.Type);
		//D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = dsvHeap->GetCPUDescriptorHandleForHeapStart();
		//dx->GetCommandList()->OMSetRenderTargets(1, &rtvHandle, false, &dsvHandle);

		//// 3. ��ʃN���A�R�}���h   R     G    B    A
		//FLOAT clearColor[] = { 0.1f,0.25f,0.5f,0.0f };
		//dx->GetCommandList()->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);
		//dx->GetCommandList()->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);

		dx->PreDraw();

		// 4. �`��R�}���h
		sphere.Update(size1, L"BasicVS.hlsl", L"BasicPS.hlsl");

		//�~��`��
		texture[0].SetImageData(XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f));
		texture[0].Draw();
		DrawObject3d(&object3ds[0], dx->GetCommandList(), sphere.vertBuff.vbView, sphere.indexBuff.ibView, _countof(sphere.vertex->indices));
		DrawObject3d(&object3ds[1], dx->GetCommandList(), sphere.vertBuff.vbView, sphere.indexBuff.ibView, _countof(sphere.vertex->indices));


		dx->PostDraw();
		//// 5. ���\�[�X�o���A���������݋֎~��
		//barrierDesc.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;	//�`���Ԃ���
		//barrierDesc.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;			//�\����Ԃ�
		//dx->GetCommandList()->ResourceBarrier(1, &barrierDesc);

		////���߂̃N���[�Y
		//result = dx->GetCommandList()->Close();
		//assert(SUCCEEDED(result));
		////�R�}���h���X�g�̎��s
		//ID3D12CommandList* commandLists[] = { dx->GetCommandList() };
		//dx->GetCommandQueue()->ExecuteCommandLists(1, commandLists);

		////��ʂɕ\������o�b�t�@���N���b�v
		//result = dx->GetSwapChain()->Present(1, 0);
		//assert(SUCCEEDED(result));


		////�R�}���h�̎��s������҂�
		//dx->GetCommandQueue()->Signal(dx->GetFence(), ++dx->fenceVal);
		//if (dx->GetFence()->GetCompletedValue() != dx->fenceVal)
		//{
		//	HANDLE event = CreateEvent(nullptr, false, false, nullptr);
		//	dx->GetFence()->SetEventOnCompletion(dx->fenceVal, event);
		//	if (event != NULL) {
		//		WaitForSingleObject(event, INFINITE);
		//	}
		//	if (event != NULL) {
		//		CloseHandle(event);
		//	}
		//}

		////�L���[���N���A
		//result = dx->GetCommandAllocator()->Reset();
		//assert(SUCCEEDED(result));
		////�ĂуR�}���h���X�g�𒙂߂鏀��
		//result = dx->GetCommandList()->Reset(dx->GetCommandAllocator(), nullptr);
		//assert(SUCCEEDED(result));

#pragma endregion


		//X�{�^���ŏI�����b�Z����������Q�[�����[�v�𔲂��� 
		if (masage->ExitGameloop() == 1)
		{
			break;
		}

		//�E�B���h�E�N���X��o�^����
		win->deleteWindow();
	}

	return 0;
}