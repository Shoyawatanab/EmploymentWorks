#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"

class BossEnemy;

class BossEnemyLeftArm : public BossEnemyParts
{
	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "LeftArm";

public:
	//�R���X�g���N�^
	BossEnemyLeftArm(Scene* scene, BossEnemy* boss);
	//�f�X�g���N�^
	~BossEnemyLeftArm() override;

	//�ʂ̓����������̊֐�
	void OnCollisionEnterActor(ColliderComponent* collider);



};