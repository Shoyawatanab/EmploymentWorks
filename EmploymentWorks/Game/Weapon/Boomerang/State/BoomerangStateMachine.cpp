#include "pch.h"
#include "BoomerangStateMachine.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
BoomerangStateMachine::BoomerangStateMachine(Boomerang* boomerang)
	:
	m_currentState{}
	,m_idle{}
	,m_getReady{}
{
	m_idle = std::make_unique<BoomerangIdle>(boomerang);
	m_getReady = std::make_unique<BoomerangGetReady>(boomerang);
	m_rigntThrow = std::make_unique<BoomerangRightThrow>(boomerang);
	m_leftThrow = std::make_unique<BoomerangLeftThrow>(boomerang);
	m_frontThrow = std::make_unique<BoomerangFrontThrow>(boomerang);
	m_repelled = std::make_unique<BoomerangRepelled>(boomerang);
	m_drop = std::make_unique<BoomerangDrop>(boomerang);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BoomerangStateMachine::~BoomerangStateMachine()
{
}




/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
/// <param name="startState">�����X�e�[�g</param>
void BoomerangStateMachine::Initialize(CommonResources* resources, IState* startState)
{
	//������
	m_idle->Initialize(resources);
	m_getReady->Initialize(resources);
	m_rigntThrow->Initialize(resources);
	m_leftThrow->Initialize(resources);
	m_frontThrow->Initialize(resources);
	m_repelled->Initialize(resources);
	m_drop->Initialize(resources);

	//�X�e�[�g��ݒ�
	m_currentState = startState;
	m_currentState->Enter();


}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BoomerangStateMachine::Update(const float& elapsedTime)
{
	//�X�e�[�g�̍X�V
	m_currentState->Update(elapsedTime);
}

void BoomerangStateMachine::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	
	m_currentState->Render(view, projection);
}


/// <summary>
/// �X�e�[�g�̐؂�ւ�
/// </summary>
/// <param name="nextState">���̃X�e�[�g</param>
void BoomerangStateMachine::ChangeState(IState* nextState)
{

	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();



}


