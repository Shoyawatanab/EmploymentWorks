#include "pch.h"
#include "ItemEntity.h"
#include "Libraries/WataLib/Bounding.h"
#include "Game/CollisiionManager.h"
#include "Libraries/WataLib/Animation.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
ItemEntity::ItemEntity(CommonResources* resources
	, const DirectX::SimpleMath::Vector3& scale
	, const DirectX::SimpleMath::Vector3& position
	, const DirectX::SimpleMath::Quaternion& rotation)
	:
	MoveEntity(resources, scale,position,rotation)
{


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ItemEntity::~ItemEntity()
{
}



/// <summary>
/// ������
/// </summary>
void ItemEntity::Initialize()
{

	MoveEntity::Initialize();

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void ItemEntity::Update(const float& elapsedTime)
{

	MoveEntity::Update(elapsedTime);


}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void ItemEntity::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	MoveEntity::Render(view, projection);

}

/// <summary>
/// �����������ɌĂяo�����֐�
/// </summary>
/// <param name="object">����̃I�u�W�F�N�g</param>
/// <param name="tag">����̃^�O</param>
void ItemEntity::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{

	MoveEntity::OnCollisionEnter(object, tag);

}
