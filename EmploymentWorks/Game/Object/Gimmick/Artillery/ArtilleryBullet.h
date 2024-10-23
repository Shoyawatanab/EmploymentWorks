#pragma once
/*
	@file	ArtilleryBullet.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "pch.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Interface/ICollisionObject.h"

// �O���錾
class CommonResources;
class Bounding;
class PlayScene;



class ArtilleryBullet : public ICollisionObject

{
public:
	enum  BulletState
	{
		Stock         //�X�g�b�N��ԁ@
 		,Loading      //���U���
		,Flying      //���ł�����

	};
public:
	//�e�̏�Ԃ̎擾
	BulletState& GetBulletState() { return m_bulletState; }
	//�e�̏�Ԃ�o�^
	void SetBulletState(BulletState State) { m_bulletState = State; }


private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	std::unique_ptr<Bounding> m_bounding;

	// ���f��
	std::unique_ptr<DirectX::Model> m_model;

	DirectX::SimpleMath::Vector3 m_initialPosition;
	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_scale;
	DirectX::SimpleMath::Quaternion m_rotate;

	BulletState m_bulletState;

	PlayScene* m_playScene;

public:
	ArtilleryBullet();
	~ArtilleryBullet() ;

	void Initialize(CommonResources* resources, PlayScene* playScene, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 Scale,DirectX::SimpleMath::Quaternion Rotate);
	void Update(float elapsedTime);
	void Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection) ;
	void Finalize() ;

	void RegistrationCollionManager(CollisionManager* collsionManager) override;

	Bounding* GetBounding() const override { return m_bounding.get(); };

	CollsionObjectTag GetCollsionTag() const override { return CollsionObjectTag::ArtilleryBullet; }

	void SetPosition(DirectX::SimpleMath::Vector3& Pos) override { m_position = Pos; }

	DirectX::SimpleMath::Vector3 GetPosition() override { return DirectX::SimpleMath::Vector3::Zero; }
	void OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos) override;

private:
};
