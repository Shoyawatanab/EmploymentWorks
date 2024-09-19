
#include "pch.h"
#include "Game/Object/Boomerang/State/BoomerangDrop.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player/Player.h"

const DirectX::SimpleMath::Vector3 GENERATEDISTANCE(0.5f, 0.8f, 0.0f);

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

// ����������
void BoomerangDrop::Initialize()
{
	

}


// �X�V����
void BoomerangDrop::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;





	//�}�g���N�X�@�q���̌v�Z�@�e�̌v�Z�̏��Ԃł��Ȃ��Ƃ����Ȃ�
	m_worldMatrix = Matrix::CreateScale(m_boomerang->GetScale());
	m_worldMatrix *= Matrix::CreateFromQuaternion(m_boomerang->GetRotate());
	m_worldMatrix *= Matrix::CreateTranslation(m_boomerang->GetPosition());



}


void BoomerangDrop::Enter()
{
	using namespace DirectX::SimpleMath;




}

void BoomerangDrop::Exit()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;




}

void BoomerangDrop::RegistrationInformation(Boomerang* boomerang)
{

	m_boomerang = boomerang;


}
