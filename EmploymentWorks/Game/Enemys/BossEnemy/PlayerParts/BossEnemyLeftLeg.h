/*
* �v���C���̑̃N���X
*/

#pragma once
#include "Game/Enemys/BossEnemy/BossEnemyPartsBase.h"


//�O���錾

namespace WataLib
{
	class Animation;
	class Bounding;

}

// �u�C���v�N���X���`����
class BossEnemyLeftLeg : public BossEnemyPartsBase
{

private:
	//static constexpr �R���p�C�����Ɍ��肷��@�N���X�O�ł̕ύX������K�v���Ȃ�����
	//static cons      �N���X�O�ŕύX����\��������ꍇ

	static constexpr const char PARTSNAME[] = "LeftLeg";


public:
	//�R���X�g���N�^
	BossEnemyLeftLeg(CommonResources* resources,
		BossEnemy* root,                         //�v���C���̌����N���X�iPlayer.cpp�j
		CharacterEntity* parent, 		                         //�e�N���X
		DirectX::SimpleMath::Vector3 scale,                  //�����̑傫��
		DirectX::SimpleMath::Vector3 position,               //�e�̍��W����ǂꂾ������Ă��邩
		DirectX::SimpleMath::Quaternion rotation);           //+Z�Ɍ����Ă���Ƃ��̉�]���
	//�f�X�g���N�^
	~BossEnemyLeftLeg() override;


	//������
	void Initialize() override;


};

