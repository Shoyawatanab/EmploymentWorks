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
class BossEnemyHead : public BossEnemyPartsBase
{

private:

	//�p�[�c��
	static constexpr const char PARTSNAME[] = "Head";


public:
	//�R���X�g���N�^
	BossEnemyHead(CommonResources* resources,
		BossEnemy* root,                         //�v���C���̌����N���X�iPlayer.cpp�j
		CharacterEntity* parent, 		                         //�e�N���X
		DirectX::SimpleMath::Vector3 scale,                  //�����̑傫��
		DirectX::SimpleMath::Vector3 position,               //�e�̍��W����ǂꂾ������Ă��邩
		DirectX::SimpleMath::Quaternion rotation);           //+Z�Ɍ����Ă���Ƃ��̉�]���
	//�f�X�g���N�^
	~BossEnemyHead() override;


	//������
	void Initialize() override;


};

