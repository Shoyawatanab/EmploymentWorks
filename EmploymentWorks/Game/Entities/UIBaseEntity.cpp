#include "pch.h"
#include "UIBaseEntity.h"
#include "Game/Params.h"




/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="scale">�傫��</param>
/// <param name="position">���W</param>
/// <param name="rotation">��]</param>
UIBaseEntity::UIBaseEntity(CommonResources* resources)
	:
	m_commonResources{resources}
	,m_isEntityActive{true}
	,m_isUpdateActive{true}
	,m_isRenderActive{true}
{



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
UIBaseEntity::~UIBaseEntity()
{
}

/// <summary>
/// ������
/// </summary>
void UIBaseEntity::Initialize()
{
}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void UIBaseEntity::Update(const float& elapsedTime)
{

	UNREFERENCED_PARAMETER(elapsedTime);




}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void UIBaseEntity::Render()
{
	using namespace DirectX::SimpleMath;



}

