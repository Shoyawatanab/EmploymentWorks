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
class BossEnemyRightArm : public BossEnemyPartsBase
{

private:
	//�p�[�c��
	static constexpr const char PARTSNAME[] = "RightArm";


public:
	//�R���X�g���N�^
	BossEnemyRightArm(CommonResources* resources,
		BossEnemy* root,                         //�v���C���̌����N���X�iPlayer.cpp�j
		CharacterEntity* parent, 		                         //�e�N���X
		DirectX::SimpleMath::Vector3 scale,                  //�����̑傫��
		DirectX::SimpleMath::Vector3 position,               //�e�̍��W����ǂꂾ������Ă��邩
		DirectX::SimpleMath::Quaternion rotation);           //+Z�Ɍ����Ă���Ƃ��̉�]���
	//�f�X�g���N�^
	~BossEnemyRightArm() override;


	//������
	void Initialize() override;
	//�����������ɌĂяo�����
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;

};

