#include "main.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//ウィンドウ生成
	WinApp* win = nullptr;
	win = WinApp::GetInstance();
	win->CreateWindow_(L"DirectX");

	Masage* masage;	//メッセージ
	masage = Masage::GetInstance();

	//DirectX初期化処理
	DirectXCommon* dx = nullptr;
	dx = DirectXCommon::GetInstance();
	dx->Initialize(win);

	//キーボード
	Input* input = nullptr;
	input = Input::GetInstance();
	input->Initialize(win);

#pragma region 描画処理初期化
	XMFLOAT3 size1 = { 1.0f,1.0f,1.0f };
	Sphere sphere;
	sphere.Initialize(size1, dx);

	//読み込む画像の数
	const size_t metadataCount = 2;
	//画像
	Texture texture[metadataCount];
	//初期化
	texture[0].Initialize(dx, 0);
	texture[1].Initialize(dx, 1);


	//3Dオブジェクトの数
	const size_t kObjectCount = 1;
	//3Dオブジェクトの配列
	Object3d object3ds[kObjectCount];

	//配列内すべてのオブジェクトに対して
	for (int i = 0; i < _countof(object3ds); i++)
	{
		//初期化
		InitializeObject3d(&object3ds[i], dx->GetDevice());
			object3ds[i].scale = { 10.0f,10.0f,10.0f };
			object3ds[i].rotation = { 0.0f,0.0f,0.0f };
			object3ds[0].position = { -10.0f,0.0f,-60.0f };
			/*object3ds[1].position = { 10.0f,0.0f,-60.0f };*/
	}

	//射影変換
	XMMATRIX matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(45.0f),			//上下画角45度
		(float)window_width / window_height,//アスペクト比(画面横幅/画面立幅)
		0.1f, 1000.0f						//前端、奥端
	);

	//ビュー変換行列
	XMMATRIX matView;
	XMFLOAT3 eye(0, 0, -100);
	XMFLOAT3 target(0, 0, 0);
	XMFLOAT3 up(0, 1, 0);
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));

#pragma endregion

	//ゲームループ
	while (true)
	{
		//メッセージがある？
		masage->Update();

#pragma region DirectX毎フレーム処理

		//キーボード更新
		input->Update();

		for (int i = 0; i < _countof(object3ds); i++)
		{
			UpdateObject3d(&object3ds[i], matView, matProjection);
		}


		//座標を移動する処理
		//if (input->key[DIK_1])
		//{
		//	sphere.pipe.pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;	//カリングしない
		//}
		//if (input->key[DIK_2])
		//{
		//	sphere.pipe.pipelineDesc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;	//カリングしない
		//}
		//if (input->key[DIK_3])
		//{
		//	sphere.pipe.pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;	//ポリゴン塗りつぶし
		//}
		//if (input->key[DIK_4])
		//{
		//	sphere.pipe.pipelineDesc.RasterizerState.FillMode = D3D12_FILL_MODE_WIREFRAME;	//ポリゴン塗りつぶし
		//}

		dx->PreDraw();

		// 4. 描画コマンド
		sphere.Update();

		//円を描画
		texture[0].SetImageData(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
		texture[0].Draw();
		DrawObject3d(&object3ds[0], dx->GetCommandList(), sphere.vbView, sphere.ibView, sphere.indices.size());
		/*DrawObject3d(&object3ds[1], dx->GetCommandList(), sphere.vbView, sphere.ibView, _countof(sphere.indices));*/


		dx->PostDraw();

#pragma endregion


		//Xボタンで終了メッセ時が来たらゲームループを抜ける 
		if (masage->ExitGameloop() == 1)
		{
			break;
		}

		//ウィンドウクラスを登録解除
		win->deleteWindow();
	}

	return 0;
}