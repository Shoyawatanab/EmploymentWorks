#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"

class BossEnemy;

class BossEnemyRightArm : public BossEnemyParts
{
	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "RightArm";

public:
	//�R���X�g���N�^
	BossEnemyRightArm(Scene* scene, BossEnemy* boss);
	//�f�X�g���N�^
	~BossEnemyRightArm() override;


	//�ʂ̓����������̊֐�
	void OnCollisionEnterActor(ColliderComponent* collider);


};