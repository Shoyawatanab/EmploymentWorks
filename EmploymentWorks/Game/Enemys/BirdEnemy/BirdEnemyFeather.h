/*
	@file	BirdEnemyFeather.h
	@brief�@���̓G�̉H
*/
#pragma once
#include "Game/Enemys/BirdEnemy/BirdEnemyPartsBase.h"


namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class BirdEnemyFeather : public BirdEnemyPartsBase
{
public:
	static constexpr const char PARTSNAME[] = "Body";

public:
	enum class State
	{
		Up
		,Down
	};

	State m_state;

public:
	BirdEnemyFeather(CommonResources* resources, 
		CharacterEntity* parent, 		                         //�e�N���X
		DirectX::SimpleMath::Vector3 scale,                  //�����̑傫��
		DirectX::SimpleMath::Vector3 position,               //�e�̍��W����ǂꂾ������Ă��邩
		DirectX::SimpleMath::Quaternion rotation);           //+Z�Ɍ����Ă���Ƃ��̉�]���
	
	~BirdEnemyFeather();
	//������
	void Initialize() override;

	void Update(const float& elapsedTime) override;

};
