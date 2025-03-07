#include "pch.h"
#include "CollisionEntity.h"
#include "Libraries/WataLib/Bounding.h"
#include "Game/CollisiionManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
CollisionEntity::CollisionEntity(CommonResources* resources
	, const DirectX::SimpleMath::Vector3& scale
	, const DirectX::SimpleMath::Vector3& position
	, const DirectX::SimpleMath::Quaternion& rotation)
	:
	BaseEntity(resources, scale, position, rotation)
{

	m_bounding = std::make_unique<WataLib::Bounding>(resources);

}


/// <summary>
/// ������
/// </summary>
void CollisionEntity::Initialize()
{

	BaseEntity::Initialize();

	m_bounding->Initialize();

	//�ǂ̓����蔻��𐶐����邩�͔h���N���X�Œ�`

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void CollisionEntity::Update(const float& elapsedTime)
{

	BaseEntity::Update(elapsedTime);

}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void CollisionEntity::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	BaseEntity::Render(view, projection);

	m_bounding->Draw(BaseEntity::GetPosition(), BaseEntity::GetRotation(), view, projection);


}

/// <summary>
/// �����������ɌĂяo�����֐�
/// </summary>
/// <param name="object">����̃I�u�W�F�N�g</param>
/// <param name="tag">����̃^�O</param>
void CollisionEntity::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{

}

/// <summary>
/// �����蔻��N���X�ɒǉ�
/// </summary>
/// <param name="collsionManager">�����蔻��N���X</param>
void CollisionEntity::AddCollision(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
}

