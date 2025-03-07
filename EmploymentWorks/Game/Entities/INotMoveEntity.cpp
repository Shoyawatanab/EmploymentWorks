#include "pch.h"
#include "INotMoveEntity.h"
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
INotMoveEntity::INotMoveEntity(CommonResources* resources
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
INotMoveEntity::~INotMoveEntity()
{
}

/// <summary>
/// ������
/// </summary>
void INotMoveEntity::Initialize()
{

	CollisionEntity::Initialize();

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime"></param>
void INotMoveEntity::Update(const float& elapsedTime)
{

	CollisionEntity::Update(elapsedTime);

}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void INotMoveEntity::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	CollisionEntity::Render(view, projection);

}

/// <summary>
/// �����������ɌĂяo�����֐�
/// </summary>
/// <param name="object">����̃I�u�W�F�N�g</param>
/// <param name="tag">����̃^�O</param>
void INotMoveEntity::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{

	CollisionEntity::OnCollisionEnter(object, tag);

}
