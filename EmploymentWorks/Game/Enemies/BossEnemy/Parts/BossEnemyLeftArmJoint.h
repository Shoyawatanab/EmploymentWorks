/*
	�N���X��     : BossEnemyLeftArmJoint
	����         : �{�X�G�̍��r�֐߃��f��
	�⑫�E���ӓ_ :
*/
#pragma once
#include "Game/Enemies/BossEnemy/BossEnemyParts.h"

class BossEnemy;

class BossEnemyLeftArmJoint : public BossEnemyParts
{
	//�p�[�c��
	static constexpr const char PARTS_NAME[] = "LeftArmJoint";

public:
	//�R���X�g���N�^
	BossEnemyLeftArmJoint(Scene* scene, BossEnemy* boss);
	//�f�X�g���N�^
	~BossEnemyLeftArmJoint() override;

};