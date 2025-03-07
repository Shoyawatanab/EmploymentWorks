
#include "pch.h"
#include "BoomerangDrop.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/ItemAcquisition.h"



// �R���X�g���N�^
BoomerangDrop::BoomerangDrop()
	:
	m_worldMatrix{},
	m_boomerang{}
{
}

// �f�X�g���N�^
BoomerangDrop::~BoomerangDrop()
{

}

void BoomerangDrop::Initialize(CommonResources* resources)
{
	
}




// �X�V����
void BoomerangDrop::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	


}

void BoomerangDrop::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
}


void BoomerangDrop::Enter()
{
	using namespace DirectX::SimpleMath;

	ItemAcquisition::GetInstance()->AddItem(m_boomerang->GetID(), m_boomerang);


}

void BoomerangDrop::Exit()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	ItemAcquisition::GetInstance()->DeleteItem(m_boomerang->GetID());


}

void BoomerangDrop::AddPointer(Boomerang* boomerang)
{

	m_boomerang = boomerang;


}
