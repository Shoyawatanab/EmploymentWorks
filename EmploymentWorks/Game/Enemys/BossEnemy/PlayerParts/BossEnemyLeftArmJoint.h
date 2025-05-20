/*
* �v���C���̑̃N���X
*/

#pragma once
#include "Game/Enemys/BossEnemy/BossEnemyPartsBase.h"


//�O���錾
class BossEnemy;

namespace WataLib
{
	class Animation;
	class Bounding;

}

// �u�C���v�N���X���`����
class BossEnemyLeftArmJoint : public BossEnemyPartsBase
{

private:
	//�p�[�c��
	static constexpr const char PARTSNAME[] = "LeftArmJoint";


public:
	//�R���X�g���N�^
	BossEnemyLeftArmJoint(CommonResources* resources,
		BossEnemy* root,                         //�v���C���̌����N���X�iPlayer.cpp�j
		CharacterEntity* parent, 		                         //�e�N���X
		DirectX::SimpleMath::Vector3 scale,                  //�����̑傫��
		DirectX::SimpleMath::Vector3 position,               //�e�̍��W����ǂꂾ������Ă��邩
		DirectX::SimpleMath::Quaternion rotation);           //+Z�Ɍ����Ă���Ƃ��̉�]���
	//�f�X�g���N�^
	~BossEnemyLeftArmJoint() override;

	//������
	void Initialize() override;


};

