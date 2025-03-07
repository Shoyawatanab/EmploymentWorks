#include "pch.h"
#include "EnemyEntity.h"
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
EnemyEntity::EnemyEntity(CommonResources* resources
	, const DirectX::SimpleMath::Vector3& scale
	, const DirectX::SimpleMath::Vector3& position
	, const DirectX::SimpleMath::Quaternion& rotation)
	:
	CompositeEntity(resources,scale,position,rotation)
	,m_enemyMangaer{}
{


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EnemyEntity::~EnemyEntity()
{
}

/// <summary>
/// ������
/// </summary>
void EnemyEntity::Initialize()
{

	CompositeEntity::Initialize();

}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void EnemyEntity::Update(const float& elapsedTime)
{

	CompositeEntity::Update(elapsedTime);

}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void EnemyEntity::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	CompositeEntity::Render(view, projection);

}

/// <summary>
/// �����������ɌĂяo�����֐�
/// </summary>
/// <param name="object">����̃I�u�W�F�N�g</param>
/// <param name="tag">����̃^�O</param>
void EnemyEntity::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{

	CompositeEntity::OnCollisionEnter(object, tag);

}

/// <summary>
/// �}�l�[�W���[�̃|�C���^�̒ǉ�
/// </summary>
/// <param name="enemyManager">�G�l�~�[�}�l�[�W���[</param>
void EnemyEntity::SetManager(EnemyManager* enemyManager)
{

	m_enemyMangaer = enemyManager;

}
