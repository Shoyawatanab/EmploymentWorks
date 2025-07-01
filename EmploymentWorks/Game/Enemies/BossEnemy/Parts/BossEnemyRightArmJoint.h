#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"

class BossEnemy;

class BossEnemyRightArmJoint : public BossEnemyParts
{
	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "RightArmJoint";

public:
	//�R���X�g���N�^
	BossEnemyRightArmJoint(Scene* scene, BossEnemy* boss);
	//�f�X�g���N�^
	~BossEnemyRightArmJoint() override;

};