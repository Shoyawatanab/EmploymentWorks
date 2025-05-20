/*
	@file	BirdEnemyFeather.h
	@brief�@���̓G�̉H
*/
#pragma once
#include "Game/Enemys/BirdEnemy/BirdEnemyPartsBase.h"

//�O���錾
namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BirdEnemyFeather : public BirdEnemyPartsBase
{
public:
	//�p�[�c��
	static constexpr const char PARTSNAME[] = "Body";

public:
	//�H�̏��
	enum class State
	{
		UP
		,DOWN
	};


public:
	//�R���X�g���N�^
	BirdEnemyFeather(CommonResources* resources, 
		CharacterEntity* parent, 		                         //�e�N���X
		DirectX::SimpleMath::Vector3 scale,                  //�����̑傫��
		DirectX::SimpleMath::Vector3 position,               //�e�̍��W����ǂꂾ������Ă��邩
		DirectX::SimpleMath::Quaternion rotation);           //+Z�Ɍ����Ă���Ƃ��̉�]���
	//�f�X�g���N�^
	~BirdEnemyFeather();
	//������
	void Initialize() override;
	//�X�V����
	void Update(const float& elapsedTime) override;


private:

	State m_state;

};
