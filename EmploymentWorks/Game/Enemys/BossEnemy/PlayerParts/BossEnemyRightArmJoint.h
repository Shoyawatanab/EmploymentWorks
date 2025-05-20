/*
* �v���C���̑̃N���X
*/

#pragma once
#include "Game/Enemys/BossEnemy/BossEnemyPartsBase.h"


//�O���錾
class Enemy;

namespace WataLib
{
	class Animation;
	class Bounding;

}

// �u�C���v�N���X���`����
class BossEnemyRightArmJoint : public BossEnemyPartsBase
{

private:
	//�p�[�e�B�N���̐����̃��b�Z�[�W�𑗂�
	static constexpr const char PARTSNAME[] = "RightArmJoint";

public:
	//�R���X�g���N�^
	BossEnemyRightArmJoint(CommonResources* resources,
		BossEnemy* root,                         //�v���C���̌����N���X�iPlayer.cpp�j
		CharacterEntity* parent, 		                         //�e�N���X
		DirectX::SimpleMath::Vector3 scale,                  //�����̑傫��
		DirectX::SimpleMath::Vector3 position,               //�e�̍��W����ǂꂾ������Ă��邩
		DirectX::SimpleMath::Quaternion rotation);           //+Z�Ɍ����Ă���Ƃ��̉�]���
	//�f�X�g���N�^
	~BossEnemyRightArmJoint() override;

	//������
	void Initialize() override;

};

