#include "pch.h"
#include "IdleingAction.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
IdleingAction::IdleingAction()
{



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
IdleingAction::~IdleingAction()
{
	// do nothing.
}


/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
/// <returns>�p�����I����</returns>
IdleingAction:: ActionState IdleingAction::Update(const float& elapsedTime)
{

	return ActionState::END;

}


/// <summary>
/// ��Ԃɓ�������
/// </summary>
void IdleingAction::Enter()
{

}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void IdleingAction::Exit()
{
}
