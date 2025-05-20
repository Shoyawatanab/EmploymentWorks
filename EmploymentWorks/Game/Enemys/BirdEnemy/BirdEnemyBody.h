/*
	@file	BirdEnemyBody.h
	@brief	���̓G�̑�
*/
#pragma once
#include "Game/Enemys/BirdEnemy/BirdEnemyPartsBase.h"

// �O���錾
namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BirdEnemyBody : public BirdEnemyPartsBase
{

public:
	//�p�[�c��
	static constexpr const char PARTSNAME[] = "Body";


public:
	//�R���X�g���N�^
	BirdEnemyBody(CommonResources* resources,
		CharacterEntity* parent, 		                         //�e�N���X
		DirectX::SimpleMath::Vector3 scale,                  //�����̑傫��
		DirectX::SimpleMath::Vector3 position,               //�e�̍��W����ǂꂾ������Ă��邩
		DirectX::SimpleMath::Quaternion rotation);           //+Z�Ɍ����Ă���Ƃ��̉�]���

	//�f�X�g���N�^
	~BirdEnemyBody() override ;

	//������
	void Initialize() override;
	//�X�V����
	void Update(const float& elapsedTime) override;


};
