#include "DirectXCommon.h"
#include "input.h"
#include "DirectXTex.h"
#include "Sphere.h"
#include "Cube.h"
#include "Sprite.h"
#include "object3D.h"
#include "list"
#include "memory"
#include "Texture.h"
#include "WinApp.h"
#include "Lane.h"
#include "Goal.h"
#include "Bullet.h"
#include "string"
#include "sstream"
#include "Effect.h"
#include "FPS.h"
#include "wrl.h"

using namespace Microsoft::WRL;


class GameScene
{
	//�����o�֐�
public:
	void Initialize(DirectXCommon* dxCommon, Input* input);
	void Update();
	void Draw();

	void Title();
	void Select();
	void Game();

	void TitleDraw();
	void SelectDraw();
	void GameDraw();

	//�����o�ϐ�
private: 
	//�f�o�C�X��input
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;

	////���̂̃��f��
	//XMFLOAT3 size1 = { 1.0f,1.0f,1.0f };
	//std::unique_ptr<ComPtr<Sphere>> sphere_;

	//�L���[�u�̃��f��
	XMFLOAT3 size2 = { 2.02f,2.02f,2.02f };
	std::unique_ptr<Cube> cube_;

	//�X�v���C�g�̃��f��
	XMFLOAT3 size3 = { 2.02f,2.02f,2.02f };
	std::unique_ptr<Sprite> sprite_;

	//�摜
	size_t laneTexCount_ = 3;	//�e�N�X�`���̐�
	std::vector<Texture> laneTex_;	//�e�N�X�`��
	size_t texImgCount_ = 4;	//�e�N�X�`���̐�
	std::vector<Texture> texImg_;	//�e�N�X�`��
	size_t numImgCount_ = 10;	//�e�N�X�`���̐�
	std::vector<Texture> numImg_;	//�e�N�X�`��

	//3D�I�u�W�F�N�g
	size_t kObjectCount = 2;		//�I�u�W�F�N�g�̐�
	std::vector<Object3d> object3ds_;	//�I�u�W�F�N�g

	size_t backGroundCount = 3;		//�I�u�W�F�N�g�̐�
	std::vector<Object3d> objectBackGround_;	//�I�u�W�F�N�g

	size_t bulletCount = 30;		//�I�u�W�F�N�g�̐�
	std::vector<Object3d> objectBullet_;	//�I�u�W�F�N�g

	size_t numCount = 3;		//�I�u�W�F�N�g�̐�
	std::vector<Object3d> objectnum_;	//�I�u�W�F�N�g


	//���[��
	size_t laneCount = 3;	//���[���̐�
	std::vector<Field> lane_;	//���[��
	int popLane_ = 0;

	//�S�[��
	Goal goal_;

	//�e
	//�e���X�g���擾
	std::list<std::unique_ptr<Bullet>> bullets_;
	const std::list<std::unique_ptr<Bullet>>& GetBullets() { return bullets_; }
	//�e�𑫂�
	void AddBullet(std::unique_ptr<Bullet>& Bullet);
	void GenerBullet(XMFLOAT3 BulletPos, int ID, int lane);
	//�G�����f�[�^�ǂݍ���
	void LoadBulletPopData();
	void BulletReset();
	void UpdateBulletPopCommands();
	//csv
	std::stringstream bulletPopCommands_;

	//�G�t�F�N�g
	std::list<std::unique_ptr<Effect>> effects_;
	void GenerEffect(XMFLOAT3 pos, int lane, int texNum);
	Effect* effect_ = nullptr;

	//�����蔻��
	void CheckAllCollisions();

	int gameLevel_ = 0;
	int levelMax_ = 8;
	//�ҋ@���t���O
	bool isStand_ = false;
	//�ҋ@�^�C�}�[
	int standTime_ = 0;
	int gameTimer_ = 0;

	//�ˉe�ϊ�
	XMMATRIX matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(45.0f),			//�㉺��p45�x
		(float)window_width / window_height,//�A�X�y�N�g��(��ʉ���/��ʗ���)
		0.1f, 1000.0f						//�O�[�A���[
	);

	//�V�[��
	enum class Scene
	{
		Title,	//�^�C�g��
		Select,	//�X�e�[�W�I��
		Game	//����
	};
	//�V�[��	�ŏ����^�C�g��
	size_t scene_ = static_cast<size_t>(Scene::Title);
	//�����o�֐��̃|�C���^�e�[�u��
	static void (GameScene::* Scene_[])();

	//�r���[�ϊ��s��
	XMMATRIX matView;
	XMFLOAT3 eye = { 0,8,-50 };
	XMFLOAT3 target = { 0,0,-30 };
	XMFLOAT3 up = { 0, 1, 0 };

	//�K�E�Z���f���p<-�K�E�Z�S�ʂ̓Q�[���V�[�������ł��B���߂�Ȃ����B
	XMFLOAT3 deathblowTranslation_;
	XMFLOAT3 deathblowScale_;
	XMFLOAT3 deathblowRotation_;
	bool isDeathblow_ = false;
	float deathblowRadius = 0.0f;

	int spriteCount = 10;
	std::vector<Object3d> spriteOrangeMater_;//
	std::vector<Object3d> spritePurpleMater_;//
	std::vector<Object3d> spriteYellowMater_;//

	int spriteCount2 = 2;
	std::vector<Object3d> spriteTitle;//

	int scene = 0;
	int sceneChange = 0;

	//�X�R�A
	int hit_ = 0;
};
