#include "pch.h"
#include "BoomerangThrowUI.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Image.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
BoomerangThrowUI::BoomerangThrowUI(Canvas* canvas)
	:
	Actor(canvas->GetScene())
	,m_leftThrow{}
	,m_rightThrow{}
{
	using namespace DirectX::SimpleMath;
	
	//�E����UI
	m_rightThrow = GetScene()->AddActor<Image>(canvas, "RightThrow");
	m_rightThrow->GetTransform()->SetPosition(RIGHT_UI_POSITION + OFFSET);
	m_rightThrow->GetTransform()->SetScale(RIGHT_UI_SCALE);
	//������UI
	m_leftThrow = GetScene()->AddActor<Image>(canvas, "LeftThrow");
	m_leftThrow->GetTransform()->SetPosition(LEFT_UI_POSITION);
	m_leftThrow->GetTransform()->SetScale(LEFT_UI_SCALE);

	//�ʒm���󂯎���ނ̐ݒ�
	SceneMessenger::GetInstance()->Rigister(
		{
			SceneMessageType::MOUSE_WHEEL_UP
			,SceneMessageType::MOUSE_WHEEL_DOWN
		}, this
	);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BoomerangThrowUI::~BoomerangThrowUI()
{
}


/// <summary>
/// �ʒm���ɌĂяo�����֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
void BoomerangThrowUI::Notify(SceneMessageType type, void* datas)
{
	UNREFERENCED_PARAMETER(datas);
	switch (type)
	{
		case SceneMessageType::MOUSE_WHEEL_UP:
			m_rightThrow->GetTransform()->SetPosition(RIGHT_UI_POSITION + OFFSET);
			m_leftThrow->GetTransform()->SetPosition(LEFT_UI_POSITION);
			break;
		case SceneMessageType::MOUSE_WHEEL_DOWN:
			m_rightThrow->GetTransform()->SetPosition(RIGHT_UI_POSITION );
			m_leftThrow->GetTransform()->SetPosition(LEFT_UI_POSITION + OFFSET);
			break;
		default:
			break;
	}

}
