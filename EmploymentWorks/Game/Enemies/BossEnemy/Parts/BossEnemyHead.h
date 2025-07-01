#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"

class BossEnemy;

class BossEnemyHead : public BossEnemyParts
{
	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "Head";

public:
	//�R���X�g���N�^
	BossEnemyHead(Scene* scene, BossEnemy* boss);
	//�f�X�g���N�^
	~BossEnemyHead() override;

};