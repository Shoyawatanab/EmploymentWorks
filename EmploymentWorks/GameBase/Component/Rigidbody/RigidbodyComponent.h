#pragma once
#include "GameBase/Component.h"
#include "GameBase/Actor.h"


class RigidbodyComponent : public Component
{

public:
	//���x�擾
	DirectX::SimpleMath::Vector3 GetVelocity() const { return m_velocity; }
	//���x�ݒ�
	void SetVelocity(const DirectX::SimpleMath::Vector3& velocity) { m_velocity = velocity; }
	//�ǉ����x�擾
	DirectX::SimpleMath::Vector3 GetAddforce() const { return m_addforce; }
	//�ǉ����x�ݒ�
	void SetAddForce(const DirectX::SimpleMath::Vector3& addforce) { m_addforce = addforce; }
	//�ǉ����x����
	void AddForce(const DirectX::SimpleMath::Vector3& addforce) { m_addforce += addforce; }
	//�Œ�t���O�擾
	bool GetFixed() const { return m_isFixed; }
	//�Œ�t���O�ݒ�
	void SetFixed(float fixed) { m_isFixed = fixed; }
	//�������̃Z�b�g
	void  SetDeceleration(const float& deceleration) { m_deceleration = deceleration; }
	//�d�̓t���O�̎擾
	bool GetIsGravity() const { return m_isGravity; }
	//�d�̓t���O�̃Z�b�g
	void SetIsGravity(bool isGravity) { m_isGravity = isGravity; }
	//�d�͂̃��Z�b�g
	void ResetGravity() { m_addforce.y = 0.0f; }
public:
	//�R���X�g���N�^
	RigidbodyComponent(Actor* actor);
	//�f�X�g���N�^
	~RigidbodyComponent() override;
	//�X�V����
	void Update(const float& deltaTime) override;

private:
	//���x
	DirectX::SimpleMath::Vector3 m_velocity;
	//
	DirectX::SimpleMath::Vector3 m_addforce;
	//�Œ肩�ǂ����@true�F�@�Œ�@false�F�@��Œ�
	bool m_isFixed;
	//������
	float m_deceleration;
	//�d�͂����邩�ǂ��� true : ���� false : �Ȃ�
	bool m_isGravity;

};