#include "pch.h"
#include "BirdEnemyBeamStateMachine.h"


/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player">�v���C��</param>
/// <param name="enemy">���̓G</param>
/// <param name="beam">�r�[��</param>
BirdEnemyBeamStateMachine::BirdEnemyBeamStateMachine(BirdEnemy* enemy, BirdEnemyBeam* beam)
	:
	m_currentState{}
	,m_idle{}
	,m_attack{}
	,m_preliminaryAction{}
{
	//�e�X�e�[�g�𐶐�
	m_idle = std::make_unique<BirdEnemyBeamIdling>(enemy,beam);
	m_attack = std::make_unique<BirdEnemyBeamAttack>(enemy,beam);
	m_preliminaryAction = std::make_unique<BirdEnemyBeamPreliminaryAction>( enemy, beam);
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEnemyBeamStateMachine::~BirdEnemyBeamStateMachine()
{



}



/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void BirdEnemyBeamStateMachine::Initialize(CommonResources* resources, IState* startState)
{
	//������
	m_idle->Initialize(resources);
	m_attack->Initialize(resources);
	m_preliminaryAction->Initialize(resources);
	//������Ԃ�ݒ�
	m_currentState = startState;



}


/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BirdEnemyBeamStateMachine::Update(const float& elapsedTime)
{
	//�X�e�[�g���X�V
	m_currentState->Update(elapsedTime);
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void BirdEnemyBeamStateMachine::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	m_currentState->Render(view, projection);
}

/// <summary>
/// ��ԕύX
/// </summary>
/// <param name="nextState">���̏��</param>
void BirdEnemyBeamStateMachine::ChangeState(IState* nextState)
{

	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();

}


