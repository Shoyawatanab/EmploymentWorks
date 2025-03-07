#pragma once
#include <pch.h>
#include "Game/Interface/IActionState.h"

#include "Game/Entities/CollisionEntity.h"

class CommonResources;
class Boomerang;
class Beam;
class Pillar;
class StageObjectManager;
class RisingPillarvAction;

// RisingPillarRise�N���X���`����
class RisingPillarRise : public IActionState
{
public:
	// �R���X�g���N�^
	RisingPillarRise(RisingPillarvAction* risingPillarvAction , StageObjectManager* stageObjectManager);
	// �f�X�g���N�^
	~RisingPillarRise();
	//������
	void Initialize(CommonResources* resources) override;
	// �X�V����
	IBehaviorNode::State Update(const float& elapsedTime);
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;


private:

	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	CollisionEntity* m_pillar;
	StageObjectManager* m_stageObjectManager;
	RisingPillarvAction* m_risingPillarvAction;

};

