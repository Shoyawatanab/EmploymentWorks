
#include "pch.h"
#include "Game/Object/Enemy/Beam/BeamState/BeamAttack.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Object/Enemy/Beam/Beam.h"
#include "Game/Object/Enemy/Beam/BeamRays.h"
#include "Game/Object/Enemy/Beam/BeamEnergyBall.h"

const float MOVE_SPEED = 1.0f;                                        //�������̃X�s�[�h



// �R���X�g���N�^
BeamAttack::BeamAttack()
	:
	m_commonResources{}
{



}

// �f�X�g���N�^
BeamAttack::~BeamAttack()
{

}

// ����������
void BeamAttack::Initialize()
{
}



// �X�V����
void BeamAttack::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();


	Vector3 position = m_beam->GetBeamEnergyBall()->GetPosition();

	Vector3 moveDirection = Vector3::UnitZ;

	moveDirection *= elapsedTime * m_beam->GetBeamParamater()->MoveSpeed;

	position += moveDirection;

	//position = Vector3::Transform(position, m_beam->GetRotate());

	m_beam->GetBeamEnergyBall()->SetPosition(position);

	//�r�[�������̑傫���̎擾
	Vector3 scale = m_beam->GetBeamRays()->GetScale();

	//�r�[���̋��������߂�
	float distance = Vector3::Distance(Vector3::Zero, m_beam->GetBeamEnergyBall()->GetPosition());

	//���f���̃T�C�Y�̂���0.5�����炻�̂܂܂ł����v
	//�������T�C�Y��
	scale.z = distance;

	//�r�[�������̑傫����
	m_beam->GetBeamRays()->SetScale(scale);



}


void BeamAttack::Enter()
{

	m_beam->GetBeamRays()->SetScale(m_beam->GerBeamRaysParameter()->MaxScale);

	m_beam->SetClassState(Beam::CurrentClassState::Attack);




}

void BeamAttack::Exit()
{

	//m_beam->SetScale(m_beam->GetInitialScale());

}

void BeamAttack::RegistrationInformation(CommonResources* resoure, Beam* beam)
{
	m_commonResources = resoure;
	m_beam = beam;

}

