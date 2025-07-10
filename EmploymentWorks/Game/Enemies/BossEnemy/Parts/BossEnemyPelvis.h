/*
	�N���X��     : BossEnemyPelvis
	����         : �{�X�G�̍����f��
	�⑫�E���ӓ_ :
*/
#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"

class BossEnemy;

class BossEnemyPelvis : public BossEnemyParts
{
	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "Pelvis";

public:
	//�R���X�g���N�^
	BossEnemyPelvis(Scene* scene, BossEnemy* boss);
	//�f�X�g���N�^
	~BossEnemyPelvis() override;

};