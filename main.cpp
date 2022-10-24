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
	sphere.Initialize(size1, dx);

	//�ǂݍ��މ摜�̐�
	const size_t metadataCount = 2;
	//�摜
	Texture texture[metadataCount];
	//������
	texture[0].Initialize(dx, 0);
	texture[1].Initialize(dx, 1);


	//3D�I�u�W�F�N�g�̐�
	const size_t kObjectCount = 1;
	//3D�I�u�W�F�N�g�̔z��
	Object3d object3ds[kObjectCount];

	//�z������ׂẴI�u�W�F�N�g�ɑ΂���
	for (int i = 0; i < _countof(object3ds); i++)
	{
		//������
		InitializeObject3d(&object3ds[i], dx->GetDevice());
			object3ds[i].scale = { 10.0f,10.0f,10.0f };
			object3ds[i].rotation = { 0.0f,0.0f,0.0f };
			object3ds[0].position = { -10.0f,0.0f,-60.0f };
			/*object3ds[1].position = { 10.0f,0.0f,-60.0f };*/
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
		//if (input->key[DIK_1])
		//{
		//	sphere.pipe.pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;	//�J�����O���Ȃ�
		//}
		//if (input->key[DIK_2])
		//{
		//	sphere.pipe.pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;	//�J�����O���Ȃ�
		//}
		//if (input->key[DIK_3])
		//{
		//	sphere.pipe.pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;	//�|���S���h��Ԃ�
		//}
		//if (input->key[DIK_4])
		//{
		//	sphere.pipe.pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;	//�|���S���h��Ԃ�
		//}

		dx->PreDraw();

		// 4. �`��R�}���h
		sphere.Update();

		//�~��`��
		texture[0].SetImageData(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		texture[0].Draw();
		DrawObject3d(&object3ds[0], dx->GetCommandList(), sphere.vbView, sphere.ibView, sphere.indices.size());
		/*DrawObject3d(&object3ds[1], dx->GetCommandList(), sphere.vbView, sphere.ibView, _countof(sphere.indices));*/


		dx->PostDraw();

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