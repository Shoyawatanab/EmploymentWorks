#include "pch.h"
#include "MoveEntity.h"
#include "Libraries/WataLib/Bounding.h"
#include "GameBase/Manager/CollisiionManager.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
MoveEntity::MoveEntity(CommonResources* resources
	, const DirectX::SimpleMath::Vector3& scale
	, const DirectX::SimpleMath::Vector3& position
	, const DirectX::SimpleMath::Quaternion& rotation)
	:
	CollisionEntity(resources, scale,position,rotation)
{



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
MoveEntity::~MoveEntity()
{
}

/// <summary>
/// ������
/// </summary>
void MoveEntity::Initialize()
{

	CollisionEntity::Initialize();

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void MoveEntity::Update(const float& elapsedTime)
{

	CollisionEntity::Update(elapsedTime);

}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void MoveEntity::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	CollisionEntity::Render(view, projection);

}


/// <summary>
/// �����������ɌĂяo�����֐�
/// </summary>
/// <param name="object">����̃I�u�W�F�N�g</param>
/// <param name="tag">����̃^�O</param>
void MoveEntity::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{

	CollisionEntity::OnCollisionEnter(object, tag);

}
