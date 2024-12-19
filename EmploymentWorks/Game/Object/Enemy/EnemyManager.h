/*
	@file	EnemyManager.h
	@brief	�V�[���}�l�[�W���N���X
*/
#pragma once
#include "Game/Object/BirdEnemy/BirdEnemyBase.h"

// �O���錾
class CommonResources;
class Fade;
class Player;

class EnemyManager
{

private:
	CommonResources* m_commonResources;

	std::vector<std::unique_ptr<BirdEnemyBase>> m_enemys;

public:
	EnemyManager();
	~EnemyManager();

	void Initialize();
	void Update(float elapsedTime);
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection);
	void Finalize();



	//�N���X�̃C���X�^���X
	void Instances(Player* player, CommonResources* resources);


};

//�{�X�͓��ꂸ�ɎG���G��������U�Ǘ�����