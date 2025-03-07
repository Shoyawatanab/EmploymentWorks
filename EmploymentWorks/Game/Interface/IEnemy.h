/*
* �R���|�W�b�g�p�^�[���̍��̃C���^�[�t�F�[�X
*/
#pragma once
#include "Game/Interface/ICompositeRoot.h"

class EnemyManager;

class IEnemy : public ICompositeRoot
{
public:
	//�f�X�g���N�^
	virtual ~IEnemy() = default;

	virtual void SetManager(EnemyManager* enemyManager) = 0;

	virtual bool GetIsActives() = 0;

};
