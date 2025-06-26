#include "pch.h"
#include "BossHp.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Image.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"
#include "Game/Messenger/Scene/SceneMessages.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
BossHp::BossHp(Canvas* canvas)
	:
	Actor(canvas->GetScene())
{
	using namespace DirectX::SimpleMath;

	//�w�i
	m_backGraund = GetScene()->AddActor<Image>(canvas, "BossHPBase");
	m_backGraund->GetTransform()->SetPosition(Vector3( 640, 50,0));
	m_backGraund->GetTransform()->SetScale(Vector3( 1, 0.9,0));

	//Hp�o�[
	m_hpBar = GetScene()->AddActor<Image>(canvas, "EnemyHP");
	m_hpBar->GetTransform()->SetPosition(Vector3(640, 50.5, 0));
	m_hpBar->GetTransform()->SetScale(Vector3(1, 0.85, 0));



	SceneMessenger::GetInstance()->Rigister(
		{
			SceneMessageType::BOSS_DAMAGE
		}, this
	);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossHp::~BossHp()
{
}

/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
void BossHp::Notify(SceneMessageType type, void* datas)
{
	switch (type)
	{
		case SceneMessageType::BOSS_DAMAGE:
		{
			//�L���X�g���Ċ��������߂�
			float* ratio = static_cast<float*>(datas);
			//�������L���X�g�ł��Ă��邩

			if (typeid(*ratio) == typeid(float))
			{
				//Hp�o�[�̓h��Ԃ������̕ύX
				m_hpBar->SetHorizontalFillAmount(*ratio);
			}
		}
			break;
		default:
			break;
	}
}
