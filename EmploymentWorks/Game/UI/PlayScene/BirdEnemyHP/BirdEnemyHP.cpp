/*
	�N���X��     : BirdEnemyHP
	����         : ���G��HP��UI
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "BirdEnemyHP.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Image.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Messenger/Messengers.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
BirdEnemyHP::BirdEnemyHP(Canvas* canvas)
	:
	Actor(canvas->GetScene())
{
	using namespace DirectX::SimpleMath;

	//�w�i
	m_backGraund = GetScene()->AddActor<Image>(canvas, "BossHPBase");
	m_backGraund->GetTransform()->SetScale(BACKGRAUND_SCALE);
	m_backGraund->GetTransform()->SetParent(GetTransform());

	//Hp�o�[
	m_hpBar = GetScene()->AddActor<Image>(canvas, "EnemyHP");
	m_hpBar->GetTransform()->SetScale(HP_BAR_SCALE);
	m_hpBar->GetTransform()->SetParent(GetTransform());

	GetTransform()->SetPosition(POSITION);

	////�ʒm���󂯎��R���|�[�l���g�̒ǉ�
	//auto ob = AddComponent<ObserverComponent<SceneMessageType>>(this);
	////�ǂ̒ʒm���̓o�^�ƌĂяo���֐��̓o�^
	//ob->Rigister(
	//	{
	//		SceneMessageType::BOSS_DAMAGE
	//	}
	//	, std::bind(&BirdEnemyHP::Notify, this, std::placeholders::_1, std::placeholders::_2)
	//);


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEnemyHP::~BirdEnemyHP()
{
}

/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
void BirdEnemyHP::Notify(SceneMessageType type, void* datas)
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
