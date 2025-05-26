
#include "pch.h"
#include "BoomerangDrop.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/ItemAcquisition.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
BoomerangDrop::BoomerangDrop(Boomerang* boomerang)
	:
	m_worldMatrix{},
	m_boomerang{boomerang}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BoomerangDrop::~BoomerangDrop()
{

}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void BoomerangDrop::Initialize(CommonResources* resources)
{
	UNREFERENCED_PARAMETER(resources);

}




/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BoomerangDrop::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);


	


}

void BoomerangDrop::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);

}

/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BoomerangDrop::Enter()
{
	using namespace DirectX::SimpleMath;

	ItemAcquisition::GetInstance()->AddItem(m_boomerang->GetID(), m_boomerang);


}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BoomerangDrop::Exit()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	ItemAcquisition::GetInstance()->DeleteItem(m_boomerang->GetID());


}

