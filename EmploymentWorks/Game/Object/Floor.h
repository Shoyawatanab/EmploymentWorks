#pragma once
/*
	@file	Floor.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "pch.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Interface/ICollisionObject.h"


// �O���錾
class CommonResources;
class Bounding;




class Floor : public ICollisionObject

{
public:


private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	// ���f��
	std::unique_ptr<DirectX::Model> m_model;

	std::unique_ptr<Bounding> m_bounding;

	DirectX::SimpleMath::Vector3 m_position;
	float m_scale;


public:
	Floor();
	~Floor() ;

	void Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 Extens, float Scale);
	void Update(float elapsedTime, DirectX::SimpleMath::Quaternion cameraRotation);
	void Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection) ;
	void Finalize() ;

	void RegistrationCollionManager(CollisionManager* collsionManager) override;

	Bounding* GetBounding() const override { return m_bounding.get(); };

	CollsionObjectTag GetCollsionTag() const override { return CollsionObjectTag::NotMoveObject; }

	void SetPos(DirectX::SimpleMath::Vector3& Pos) override { }

	DirectX::SimpleMath::Vector3 GetPos() override { return DirectX::SimpleMath::Vector3::Zero; }


private:
};