#include "pch.h"
#include "UIStateMachine.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
UIStateMachine::UIStateMachine()
	:
	m_currentState{}
	, m_playUi{}
{

	m_playUi = std::make_unique<GamePlayUI>();
	m_gameEndUI = std::make_unique<GameEndUI>();

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
UIStateMachine::~UIStateMachine()
{
}



/// <summary>
/// �K�v�ȃ|�C���^�̒ǉ�
/// </summary>
/// <param name="player">�v���C��</param>
/// <param name="playScene">�v���C�V�[��</param>
/// <param name="enemyManager">�G�l�~�[�}�l�[�W���[</param>
void UIStateMachine::AddPointer(PlayScene* playScene)
{
	m_gameEndUI->AddPointer(playScene);
}

/// <summary>
/// ������
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
void UIStateMachine::Initialize(CommonResources* resources, IUIState* startState)
{

	m_playUi->Initialize(resources);
	m_gameEndUI->Initialize(resources);

	m_currentState = startState;



}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void UIStateMachine::Update(const float& elapsedTime)
{
	m_currentState->Update(elapsedTime);
}

void UIStateMachine::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	m_currentState->Render(view, projection);
}


/// <summary>
/// �X�e�[�g�̐؂�ւ�
/// </summary>
/// <param name="nextState">���̃X�e�[�g</param>
void UIStateMachine::ChangeState(IUIState* nextState)
{

	m_currentState->Exit();
	m_currentState = nextState;
	m_currentState->Enter();



}


