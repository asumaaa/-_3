#include "DirectXCommon.h"
#include "input.h"
#include "DirectXTex.h"
#include "Sphere.h"
#include "Cube.h"
#include "object3D.h"
#include "list"
#include "memory"
#include "Texture.h"

class GameScene
{
	//メンバ関数
public:
	GameScene();
	~GameScene();
	void Initialize(DirectXCommon* dxCommon, Input* input);
	void Update();
	void Draw();

	//メンバ変数
private: 
	//デバイスとinput
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;

	//球体のモデル
	XMFLOAT3 size1 = { 1.0f,1.0f,1.0f };
	std::unique_ptr<Sphere> sphere_;

	//キューブのモデル
	XMFLOAT3 size2 = { 1.0f,1.0f,1.0f };
	std::unique_ptr<Cube> cube_;

	//画像
	size_t textureCount_ = 3;	//テクスチャの数
	std::vector<Texture> texture_;	//テクスチャ
	size_t texImgCount_ = 1;	//テクスチャの数
	std::vector<Texture> texImg_;	//テクスチャ

	//3
	size_t backGroundCount = 2;		//オブジェクトの数
	std::vector<Object3d> objectBackGround_;	//オブジェクト

	//射影変換
	XMMATRIX matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(45.0f),			//上下画角45度
		(float)window_width / window_height,//アスペクト比(画面横幅/画面立幅)
		0.1f, 1000.0f						//前端、奥端
	);

	//ビュー変換行列
	XMMATRIX matView;
	XMFLOAT3 eye = { 0,7,-50 };
	XMFLOAT3 target = { 0,0,-32 };
	XMFLOAT3 up = { 0, 1, 0 };
};
