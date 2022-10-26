#include "DirectXCommon.h"
#include "input.h"
#include "DirectXTex.h"
#include "Sphere.h"
#include "Cube.h"
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


class GameScene
{
	//�����o�֐�
public:
	void Initialize(DirectXCommon* dxCommon, Input* input);
	void Update();
	void Draw();

	//�����o�ϐ�
private: 
	//�f�o�C�X��input
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;

	//���̂̃��f��
	XMFLOAT3 size1 = { 1.0f,1.0f,1.0f };
	std::unique_ptr<Sphere> sphere_;

	//�L���[�u�̃��f��
	XMFLOAT3 size2 = { 2.02f,2.02f,2.02f };
	std::unique_ptr<Cube> cube_;

	//�摜
	size_t laneTexCount_ = 3;	//�e�N�X�`���̐�
	std::vector<Texture> laneTex_;	//�e�N�X�`��
	size_t texImgCount_ = 1;	//�e�N�X�`���̐�
	std::vector<Texture> texImg_;	//�e�N�X�`��

	//3D�I�u�W�F�N�g
	size_t kObjectCount = 2;		//�I�u�W�F�N�g�̐�
	std::vector<Object3d> object3ds_;	//�I�u�W�F�N�g

	size_t backGroundCount = 1;		//�I�u�W�F�N�g�̐�
	std::vector<Object3d> objectBackGround_;	//�I�u�W�F�N�g


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

	//�r���[�ϊ��s��
	XMMATRIX matView;
	XMFLOAT3 eye = { 0,8,-50 };
	XMFLOAT3 target = { 0,0,-30 };
	XMFLOAT3 up = { 0, 1, 0 };
};
