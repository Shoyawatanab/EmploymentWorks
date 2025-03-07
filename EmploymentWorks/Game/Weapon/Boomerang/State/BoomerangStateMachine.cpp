#include "pch.h"
#include "BoomerangStateMachine.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// �R���X�g���N�^
/// </summary>
BoomerangStateMachine::BoomerangStateMachine()
	:
	m_currentState{}
	,m_idle{}
	,m_getReady{}
{
	m_idle = std::make_unique<BoomerangIdle>();
	m_getReady = std::make_unique<BoomerangGetReady>();
	m_throw = std::make_unique<BoomerangThrow>();
	m_repelled = std::make_unique<BoomerangRepelled>();
	m_drop = std::make_unique<BoomerangDrop>();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BoomerangStateMachine::~BoomerangStateMachine()
{
}


/// <summary>
/// �K�v�ȃ|�C���^�̒ǉ�
/// </summary>
/// <param name="boomerang">�u�[������</param>
/// <param name="player">�v���C��</param>
/// <param name="targetMarker">�^�[�Q�b�g�}�[�J�[</param>
/// <param name="tpsCamera">TPS�J����</param>
void BoomerangStateMachine::AddPointer(Boomerang* boomerang, Player* player, TargetMarker* targetMarker, WataLib::TPS_Camera* tpsCamera)
{
	m_idle->AddPointer(player, boomerang);
	m_getReady->AddPointer(boomerang);
	m_throw->AddPointer(boomerang,player,targetMarker,tpsCamera);
	m_repelled->AddPointer(boomerang);
	m_drop->AddPointer(boomerang);
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
	m_throw->Initialize(resources);
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


