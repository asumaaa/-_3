#include "GameScene.h"
#include<fstream>

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
	this->dxCommon = dxCommon;
	this->input = input;

	//���̃��f��������
	Sphere* newSphere = new Sphere();
	newSphere->Initialize(size1,dxCommon);
	sphere_.reset(newSphere);

	//�L���[�u���f��������
	Cube* newCube = new Cube();
	newCube->Initialize(size2, dxCommon);
	cube_.reset(newCube);

	//�L���[�u���f��������
	Sprite* newSprite = new Sprite();
	newSprite->Initialize(size2, dxCommon);
	sprite_.reset(newSprite);

	//�o���b�g
	BulletReset();

	//�e�N�X�`��������
	laneTex_.resize(laneTexCount_);
	texImg_.resize(texImgCount_);
	//���[���摜
	for (int i = 0; i < laneTex_.size(); i++)
	{
		laneTex_[i].Initialize(dxCommon, i);
	}
	//�w�i�摜
	for (int i = 0; i < texImg_.size(); i++)
	{
		texImg_[0].Initialize(L"Resources/backGround.png", dxCommon, 0);
		texImg_[1].Initialize(L"Resources/title.png", dxCommon, 0);
		texImg_[2].Initialize(L"Resources/setumei.png", dxCommon, 0);
	}


	//���[��������
	lane_.resize(laneCount);
	lane_[0].Initialize(dxCommon, cube_.get(), Left,input);
	lane_[1].Initialize(dxCommon, cube_.get(), Center,input);
	lane_[2].Initialize(dxCommon, cube_.get(), Right,input);

	goal_.Initialize(dxCommon, cube_.get());

	//�I�u�W�F�N�g������
	object3ds_.resize(kObjectCount);
	objectBackGround_.resize(backGroundCount);
	objectBullet_.resize(bulletCount);
	spriteOrangeMater_.resize(spriteCount);
	spritePurpleMater_.resize(spriteCount);
	spriteYellowMater_.resize(spriteCount);
	spriteTitle.resize(spriteCount2);

	for (int i = 0; i < object3ds_.size(); i++)
	{
		//������
		InitializeObject3d(&object3ds_[i], dxCommon->GetDevice());
		object3ds_[i].scale = { 1,10.0f,1 };
		object3ds_[i].rotation = { 0.0f,0.0f,0.0f };
		object3ds_[0].position = { -10.0f,0.0f,-60.0f };
		object3ds_[1].position = { 10.0f,0.0f,-60.0f };
	}
	for (int i = 0; i < objectBackGround_.size(); i++)
	{
		InitializeObject3d(&objectBackGround_[i], dxCommon->GetDevice());
		objectBackGround_[i].scale = { window_width * 0.4f,window_height * 0.4f,1.0f };
		objectBackGround_[i].rotation = { 0.4f,0.0f,0.0f };
		objectBackGround_[i].position = { 0.0f,-250.0f,600.0f };
	}
	for (int i = 0; i < objectBullet_.size(); i++)
	{
		//������
		InitializeObject3d(&objectBullet_[i], dxCommon->GetDevice());
		objectBullet_[i].scale = { 1,10.0f,1 };
		objectBullet_[i].rotation = { 0.0f,0.0f,0.0f };
		objectBullet_[0].position = { -10.0f,0.0f,-60.0f };
		objectBullet_[1].position = { 10.0f,0.0f,-60.0f };
	}

	for (int i = 0; i < spriteCount; i++)
	{
		InitializeObject3d(&spriteOrangeMater_[i], dxCommon->GetDevice());
		InitializeObject3d(&spritePurpleMater_[i], dxCommon->GetDevice());
		InitializeObject3d(&spriteYellowMater_[i], dxCommon->GetDevice());
		float x1 = -9.2 + (i * 0.5);
		spriteOrangeMater_[i].position = { x1,0,-38};
		spriteOrangeMater_[i].rotation = { 0.24,0,0 };
		spriteOrangeMater_[i].scale = { 0.24,0.24,0.24 };
		float x2 = -8.6 + (i * 0.48);
		spritePurpleMater_[i].position = { x2,0,-39 };
		spritePurpleMater_[i].rotation = { 0.24,0,0 };
		spritePurpleMater_[i].scale = { 0.23,0.23,0.23 };
		float x3 = -8.0 + (i * 0.46);
		spriteYellowMater_[i].position = { x3,0,-40 };
		spriteYellowMater_[i].rotation = { 0.24,0,0 };
		spriteYellowMater_[i].scale = { 0.22,0.22,0.22 };
	}
	for (int i = 0; i < spriteCount2; i++)
	{
		InitializeObject3d(&spriteTitle[i], dxCommon->GetDevice());
		spriteTitle[i].scale = { window_width * 0.4f,window_height * 0.4f,1.0f };
		spriteTitle[i].rotation = { 0.4f,0.0f,0.0f };
		spriteTitle[i].position = { 0.0f,-250.0f,600.0f };
	}

	deathblowScale_ = { 2,0.5,2 };
	isDeathblow_ = false;

	//�J����������
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}

void GameScene::Update()
{
	if (scene == 0)
	{
		if (input->TriggerKey(DIK_SPACE) && sceneChange == 1)
		{
			scene = 1;
		}
		if (input->TriggerKey(DIK_SPACE) && sceneChange == 0)
		{
			sceneChange = 1;
		}
	}

	if (scene == 1)
	{
		//�^�C�}�[�X�V
		gameTimer_++;
		if (gameTimer_ > 200) {
			if (gameLevel_ < levelMax_) {
				gameTimer_ = 0;
				gameLevel_++;
			}
			else {
				gameTimer_ = 0;
			}
		}

		//�e
		//�f���[�g
		bullets_.remove_if([](std::unique_ptr<Bullet>& bullet_) { return bullet_->IsDead(); });
		UpdateBulletPopCommands();

		//�G�t�F�N�g
		//�f���[�g
		effects_.remove_if([](std::unique_ptr<Effect>& effect_) { return effect_->IsDead(); });;

		//���[���X�V
		for (int i = 0; i < lane_.size(); i++)
		{
			lane_[i].Update(matView, matProjection);
		}

		//�e�X�V
		for (std::unique_ptr<Bullet>& bullet_ : bullets_) {
			bullet_->Update(matView, matProjection, lane_[bullet_->GetFieldLane()].GetTransration());
		}

		//�G�t�F�N�g�X�V
		for (std::unique_ptr<Effect>& effect_ : effects_) {
			effect_->Update(matView, matProjection);
		}

		//�S�[���X�V
		goal_.Update(matView, matProjection);

#pragma region �K�E�Z
		if (goal_.bulletHit_[0] >= 2 &&
			goal_.bulletHit_[1] >= 2 &&
			goal_.bulletHit_[2] >= 2) {
			isDeathblow_ = true;
		}
		else if (goal_.bulletHit_[0] <= 0 &&
			goal_.bulletHit_[1] <= 0 &&
			goal_.bulletHit_[2] <= 0) {
			isDeathblow_ = false;
		}
		goal_.MaterDown(isDeathblow_);

		if (isDeathblow_ == true) {
			float powerRadius = 9.5f;
			deathblowRadius += powerRadius;
		}
		else if (isDeathblow_ == false) {
			deathblowRadius = 0;
		}
#pragma endregion �K�E�Z

		CheckAllCollisions();
	}

		//�I�u�W�F�N�g�X�V
		for (int i = 0; i < object3ds_.size(); i++)
		{
			UpdateObject3d(&object3ds_[i], matView, matProjection);
		}
		for (int i = 0; i < objectBackGround_.size(); i++)
		{
			UpdateObject3d(&objectBackGround_[i], matView, matProjection);
		}
		for (int i = 0; i < objectBullet_.size(); i++)
		{
			//������
			UpdateObject3d(&objectBullet_[0], matView, matProjection);
		}

		for (int i = 0; i < spriteCount; i++)
		{
			//������

			UpdateObject3d(&spriteOrangeMater_[i], matView, matProjection);
			UpdateObject3d(&spritePurpleMater_[i], matView, matProjection);
			UpdateObject3d(&spriteYellowMater_[i], matView, matProjection);
		}
}

void GameScene::Draw()
{
	sphere_->Update();
	cube_->Update();
	sprite_->Update();


	if (scene == 0)
	{
		if (sceneChange == 0)
		{
			texImg_[1].Draw();
		}
		else if(sceneChange == 1)
		{
			texImg_[2].Draw();
		}
		DrawObject3d(&objectBackGround_[1], dxCommon->GetCommandList(), sprite_->vbView, sprite_->ibView, sprite_->indices.size());
	}

	if (scene == 1)
	{
		for (int i = 0; i < laneTex_.size(); i++)
		{
			laneTex_[0].SetImageData(XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f));
			laneTex_[1].SetImageData(XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f));
			laneTex_[2].SetImageData(XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f));
		}

		texImg_[0].Draw();
		DrawObject3d(&objectBackGround_[0], dxCommon->GetCommandList(), sprite_->vbView, sprite_->ibView, sprite_->indices.size());

		//���[���`��
		for (int i = 0; i < lane_.size(); i++)
		{
			laneTex_[i].Draw();
			lane_[i].Draw(matView);
		}

		//�S�[���`��
		laneTex_[0].Draw();
		goal_.Draw(matView);

		for (std::unique_ptr<Bullet>& bullet_ : bullets_) {
			if (bullet_->GetTexNum() == 0)
			{
				laneTex_[0].Draw();
			}
			if (bullet_->GetTexNum() == 1)
			{
				laneTex_[1].Draw();
			}
			if (bullet_->GetTexNum() == 2)
			{
				laneTex_[2].Draw();
			}
			bullet_->Draw(matView);
		}

		//�G�t�F�N�g�`��
		for (std::unique_ptr<Effect>& effect_ : effects_) {
			if (effect_->GetTexNum() == 0)
			{
				laneTex_[0].Draw();
			}
			if (effect_->GetTexNum() == 1)
			{
				laneTex_[1].Draw();
			}
			if (effect_->GetTexNum() == 2)
			{
				laneTex_[2].Draw();
			}
			effect_->Draw(matView);
		}

		for (int i = 0; i < spriteCount; i++)
		{
			if (i + 1 <= goal_.bulletHit_[0]) {
				laneTex_[0].Draw();
				DrawObject3d(&spriteOrangeMater_[i], dxCommon->GetCommandList(), sprite_->vbView, sprite_->ibView, sprite_->indices.size());
			}
			if (i + 1 <= goal_.bulletHit_[1]) {
				laneTex_[1].Draw();
				DrawObject3d(&spritePurpleMater_[i], dxCommon->GetCommandList(), sprite_->vbView, sprite_->ibView, sprite_->indices.size());
			}
			if (i + 1 <= goal_.bulletHit_[2]) {
				laneTex_[2].Draw();
				DrawObject3d(&spriteYellowMater_[i], dxCommon->GetCommandList(), sprite_->vbView, sprite_->ibView, sprite_->indices.size());
			}
		}
	}
}

void GameScene::Title()
{
}

void GameScene::Select()
{
}

void GameScene::Game()
{
}

void GameScene::TitleDraw()
{
}

void GameScene::SelectDraw()
{
}

void GameScene::GameDraw()
{
}

void GameScene::AddBullet(std::unique_ptr<Bullet>& Bullet)
{
}

void GameScene::GenerBullet(XMFLOAT3 BulletPos, int ID, int lane)
{
	//����
	std::unique_ptr<Bullet> newBullet = std::make_unique<Bullet>();
	//�G�L�����̏�����
	float kBulSpeed = 0.4f;
	if (gameLevel_ > 0) {
		kBulSpeed += gameLevel_ * 0.1f + 1.0f;	//���x�����オ��ƒe������
	}

	if (lane == 0) {
		newBullet->Initialize(dxCommon,cube_.get(), BulletPos, kBulSpeed,0);
	}
	else if (lane == 1) {
		newBullet->Initialize(dxCommon, cube_.get(), BulletPos, kBulSpeed,1);
	}
	else if (lane == 2) {
		newBullet->Initialize(dxCommon, cube_.get(), BulletPos, kBulSpeed,2);
	}

	newBullet->SetID(ID);
	newBullet->SetFieldLane(lane);

	//���X�g�ɓo�^����
	bullets_.push_back(std::move(newBullet));

}

void GameScene::LoadBulletPopData()
{
	//�t�@�C�����J��
	std::ifstream file;
	file.open("Resources/enemyPop2.csv");

	assert(file.is_open());

	//�t�@�C���̓��e�𕶎���X�g���[���ɃR�s�[
	bulletPopCommands_ << file.rdbuf();

	//�t�@�C�������
	file.close();
}

void GameScene::UpdateBulletPopCommands()
{
	//�ҋ@����
	if (isStand_) {
		standTime_--;
		if (standTime_ <= 0) {
			//�ҋ@����
			isStand_ = false;
		}
		return;
	}
	// 1�s���̕����������ϐ�
	std::string line;

	//�R�}���h���s���[�v
	while (getline(bulletPopCommands_, line)) {
		// 1�s���̕��������X�g���[���ɕϊ����ĉ�܂��₷���Ȃ�
		std::istringstream line_stream(line);

		std::string word;
		//,��؂�ōs�̐擪�������擾
		getline(line_stream, word, ',');

		//"//"����n�܂�s�̓R�����g
		if (word.find("//") == 0) {
			//�R�����g�s���΂�
			continue;
		}
		// POP�R�}���h
		if (word.find("POP") == 0) {

			//���[��
			std::getline(line_stream, word, ',');
			int lane = static_cast<int>(std::atof(word.c_str()));
			// ID
			std::getline(line_stream, word, ',');
			int ID = static_cast<int>(std::atof(word.c_str()));

			float depth = 200.0f;	//���s
			float xDifference = 10.0f;	//���E��



			if (lane == 1) {
				for (int i = 0; i < 3; i++) {
					if (lane_[i].GetLane() == 0) {
						popLane_ = i;
						break;
					}
				}
				GenerBullet(XMFLOAT3(-xDifference, 0, depth), ID, popLane_);

			}
			else if (lane == 2) {
				for (int i = 0; i < 3; i++) {
					if (lane_[i].GetLane() == 1) {
						popLane_ = i;
						break;
					}
				}
				GenerBullet(XMFLOAT3(0, 0, depth), ID, popLane_);
			}
			else if (lane == 3) {
				for (int i = 0; i < 3; i++) {
					if (lane_[i].GetLane() == 2) {
						popLane_ = i;
						break;
					}
				}
				GenerBullet(XMFLOAT3(xDifference, 0, depth), ID, popLane_);
			}
			else {


			}
		}
		// WAIT�R�}���h
		else if (word.find("WAIT") == 0) {
			std::getline(line_stream, word, ',');

			//�҂�����
			int32_t waitTime = std::atoi(word.c_str());

			//�ҋ@�J�n
			isStand_ = true;
			int maxTimeDiv = 10;
			if (gameLevel_ <= 0) {
				standTime_ = waitTime * (maxTimeDiv - gameLevel_) / maxTimeDiv;
			}
			else {

				standTime_ = waitTime * (maxTimeDiv - gameLevel_) / maxTimeDiv;
			}

			//������
			break;
		}
	}

}
void GameScene::BulletReset()
{
	bulletPopCommands_.str("");
	bulletPopCommands_.clear(std::stringstream::goodbit);
	LoadBulletPopData();
}

void GameScene::CheckAllCollisions() {

	//����Ώ�A��B�̍��W
	XMFLOAT3 posA, posB;



#pragma region ���e�ƓG�L�����̓����蔻��
	//�G�L�����̍��W
	for (std::unique_ptr<Bullet>& bullet_ : bullets_) {
		posA = bullet_->GetWorldPosition();


		//���e�̍��W
		posB = goal_.GetWorldPosition();

		float x = posB.x - posA.x;
		float y = posB.y - posA.y;
		float z = posB.z - posA.z;

		float cd = sqrt(x * x + y * y + z * z);

		if (cd <= 4.0f) {
			//�G�L�����̏Փˎ��R�[���o�b�N���Ăяo��
			bullet_->OnCollision(true);
			GenerEffect(goal_.GetWorldPosition(), bullet_->GetFieldLane(),bullet_->GetTexNum());

			//�Փˎ��R�[���o�b�N���Ăяo��
			//goal_->OnCollision();
		}

		if (cd <= deathblowRadius) {
			//�G�L�����̏Փˎ��R�[���o�b�N���Ăяo��
			bullet_->OnCollision(true);
			GenerEffect(bullet_->GetWorldPosition(), bullet_->GetFieldLane(), bullet_->GetTexNum());

			//�Փˎ��R�[���o�b�N���Ăяo��
			//goal_->OnCollision();
		}

		if (posA.z < -50/*��ʊO*/) {
			bullet_->OnCollision(false);
			if (goal_.bulletHit_[bullet_->GetFieldLane()] >= 5) {
				goal_.bulletHit_[bullet_->GetFieldLane()]--;
			}
		}
	}
}

void GameScene::GenerEffect(XMFLOAT3 pos, int lane,int texNum)
{
	//����
	std::unique_ptr<Effect> newEffect = std::make_unique<Effect>();
	///�G�L�����̏�����
	int maxHitCount = 14;
	if (lane == Left) {
		newEffect->Initialize(dxCommon,cube_.get(),pos,texNum);
		if (goal_.bulletHit_[Left] <= maxHitCount) {
			goal_.bulletHit_[Left]++;	//�O���[�o���ϐ��ł��B���߂�Ȃ����Bby�׈�
		}
	}
	else if (lane == Center) {
		newEffect->Initialize(dxCommon, cube_.get(), pos,texNum);
		if (goal_.bulletHit_[Center] <= maxHitCount) {
			goal_.bulletHit_[Center]++;
		}
	}
	else if (lane == Right) {
		newEffect->Initialize(dxCommon, cube_.get(), pos,texNum);
		if (goal_.bulletHit_[Right] <= maxHitCount) {
			goal_.bulletHit_[Right]++;
		}
	}

	//���X�g�ɓo�^����
	effects_.push_back(std::move(newEffect));

}

//�����o�֐��̃|�C���^�e�[�u��
void (GameScene::* GameScene::Scene_[])() =
{
	&GameScene::Title,
	&GameScene::Select,
	&GameScene::Game,
};