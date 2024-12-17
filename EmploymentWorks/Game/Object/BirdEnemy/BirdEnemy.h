#pragma once
#ifndef BirdEnemy_DEFINED
#define BirdEnemy_DEFINED
#include "Interface/IComponent.h"
#include  "Game/Object/BirdEnemy/BirdEnemyBase.h"
#include "Interface/IBirdEnemyState.h"
#include "Game/Object/BirdEnemy/State/BirdEnemyIdling.h"
#include "Game/Object/BirdEnemy/State/BirdEnemyAttack.h"
//#include "Game/Object/BirdEnemy/State/BirdEnemyUsually.h"

class Player;

// �u�C���v�N���X���`����
class BirdEnemy : public BirdEnemyBase
{
public:
	//���݂̑傫���̎擾
	DirectX::SimpleMath::Vector3 GetScale() const override { return m_scale; }
	// ���݂̉�]�p���擾����
	DirectX::SimpleMath::Quaternion GetAngle() const { return m_rotate; }
	// ���݂̉�]�p��ݒ肷��
	void SetAngle(const DirectX::SimpleMath::Quaternion& currentAngle) { m_rotate = currentAngle; }
	// ���f�����擾����
	DirectX::Model* GetModel() { return nullptr; }
	// ���[���h�s����擾����
	DirectX::SimpleMath::Matrix& GetWorldMatrix() { return m_worldMatrix; }

	//State
	IBirdEnemyState* GetCurrentState() { return m_currentState; }
	BirdEnemyldling* GetIdling() { return m_idling.get(); }
	BirdEnemyAttack* GetAttack() { return m_attack.get(); }

public:
	// �R���X�g���N�^
	BirdEnemy(CommonResources* resources, IComponent* parent, DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle);
	// �f�X�g���N�^
	~BirdEnemy() override;
	// ����������
	void Initialize() override;
	// �L�[�{�[�h�C�x���g����������
	inline void HandleKeyboardEvent();
	// �X�V����
	void Update(const float& elapsdTime) override;
	// �`�悷��
	void Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection) override;
	// �㏈�����s��
	void Finalize() override;
	// �C�����E�X�t�B�A���쐬����
	DirectX::BoundingSphere CreateBoundingSphere(const float& radius);


	void SetAnimation(std::string name);

	//�N���X�ɕK�v�ȏ��i�|�C���^�j��o�^����
	void RegistrationInformation(Player* player);

	//�N���X�̃C���X�^���X
	void Instances();


	void RegistrationCollionManager(CollisionManager* collsionManager) override;

	Bounding* GetBounding() const override { return m_bounding.get(); };

	CollsionObjectTag GetCollsionTag() const override { return CollsionObjectTag::Enemy; }

	void SetPosition(DirectX::SimpleMath::Vector3& Pos) override { m_position = Pos; }

	DirectX::SimpleMath::Vector3 GetPosition()override { return m_position; }


	void OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos) override;

	//State


private:


	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Quaternion m_initialRotate;
	DirectX::SimpleMath::Quaternion m_rotate;
	std::unique_ptr<Bounding> m_bounding;
	DirectX::SimpleMath::Matrix m_worldMatrix;

	DirectX::SimpleMath::Vector3 m_scale;

	Player* m_player;


	//State
	IBirdEnemyState* m_currentState;
	std::unique_ptr<BirdEnemyldling> m_idling;
	std::unique_ptr<BirdEnemyAttack> m_attack;



};

#endif		// BirdEnemy_DEFINED


//BirdEnemy�S�̂̏�������