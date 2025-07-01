#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"
class BossEnemy;


class BossEnemyRightThigh : public BossEnemyParts
{
	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "RightThigh";

public:
	//�R���X�g���N�^
	BossEnemyRightThigh(Scene* scene, BossEnemy* boss);
	//�f�X�g���N�^
	~BossEnemyRightThigh() override;

};