#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"


class BossEnemyLeftArmJoint : public BossEnemyParts
{
	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "LeftArmJoint";

public:
	//�R���X�g���N�^
	BossEnemyLeftArmJoint(Scene* scene);
	//�f�X�g���N�^
	~BossEnemyLeftArmJoint() override;

};