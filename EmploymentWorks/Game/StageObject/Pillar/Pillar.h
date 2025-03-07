/*
	@file	Pillar.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "Game/CollisiionManager.h"
#include "Game/Interface/IStateMachine.h"
#include "Game/Entities/MoveEntity.h"

// �O���錾
class CommonResources;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class Pillar : public MoveEntity
{
public:

	DirectX::SimpleMath::Vector3 GetInitialScale() { return m_initialScale; }
	
	IState* GetCurrentState() { return m_currentState; }




public:
	Pillar(CommonResources* resources);


	//�f�X�g���N�^
	~Pillar() override;

	//IObject
		//������
	void Initialize() override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//�X�V����
	void  Update(const float& elapsedTime) override;


	//ICollisionObject
	//�^�O�̎擾
	CollisionTag GetCollisionTag() override { return CollisionEntity::CollisionTag::Stage; };
	//�����蔻��N���X�ɓo�^
	void  AddCollision(CollisionManager* collsionManager) override;

	//�����������ɌĂяo�����
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;
	//�����蔻��̎�ނ̎擾
	const CollisionType GetCollisionType() override { return CollisionType::AABB; }
	//�����o�������邩�ǂ���
	const bool GetIsExtrusion() override { return false; };
	//�����蔻����s��Ȃ��^�O
	const std::vector<CollisionTag> GetNoHitDetectionTag() {
		return  {
			{CollisionTag::Stage}
		};
	}


	//��Ԃ̕ύX
	void ChangeState(IState* nextState);



private:


	DirectX::SimpleMath::Vector3 m_initialScale;

	//���݂̏��
	IState* m_currentState;

	// ���f��
	std::unique_ptr<DirectX::Model> m_model;





};
