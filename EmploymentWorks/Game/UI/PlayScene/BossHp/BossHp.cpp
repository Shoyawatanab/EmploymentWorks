/*
	�N���X��     : BossHp
	����         : �{�XHP��UI
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "BossHp.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Image.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Messenger/Messengers.h"
#include "Game/MathUtil.h"


/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
BossHp::BossHp(Canvas* canvas)
	:
	Actor(canvas->GetScene())
	,m_backGraund{}
	,m_hpBar{}
	,m_redHpBar{}
	,m_currentRatio{1.0f}
	,m_startRatio{}
	,m_endtRatio{}
	,m_animationTime{}
	,m_isAnimation{}
{
	using namespace DirectX::SimpleMath;

	//�w�i
	m_backGraund = GetScene()->AddActor<Image>(canvas, "BossHPBase");
	m_backGraund->GetTransform()->SetScale(BACKGRAUND_SCALE);
	m_backGraund->GetTransform()->SetParent(GetTransform());


	//�Ԃ�Hp�o�[
	m_redHpBar = GetScene()->AddActor<Image>(canvas, "EnemyHP");
	m_redHpBar->GetTransform()->SetScale(HP_BAR_SCALE);
	m_redHpBar->GetTransform()->SetParent(GetTransform());
	//�ԐF�Ɏw��
	m_redHpBar->SetColor(Vector4(255, 0, 0, 1));

	//Hp�o�[
	m_hpBar = GetScene()->AddActor<Image>(canvas, "EnemyHP");
	m_hpBar->GetTransform()->SetScale(HP_BAR_SCALE);
	m_hpBar->GetTransform()->SetParent(GetTransform());

	GetTransform()->SetPosition(POSITION);

	//�ʒm���󂯎��R���|�[�l���g�̒ǉ�
	auto ob = AddComponent<ObserverComponent<SceneMessageType>>(this);
	//�ǂ̒ʒm���̓o�^�ƌĂяo���֐��̓o�^
	ob->Rigister(
		{
			SceneMessageType::BOSS_DAMAGE
		}
		, std::bind(&BossHp::Notify, this, std::placeholders::_1, std::placeholders::_2)
	);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossHp::~BossHp()
{
}

/// <summary>
/// �ʍX�V
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void BossHp::UpdateActor(const float& deltaTime)
{

	//�A�j���[�V����
	if (m_isAnimation)
	{
		//���Ԃ̊��������߂�
		float timeRation = (ANIMATION_MAX_TIME - m_animationTime) / ANIMATION_MAX_TIME;
		//�\�����������߂�
		float ratio = MathUtil::Lerp(m_startRatio, m_endtRatio, timeRation);
		//�ԐF�̃o�[�̕ύX
		m_redHpBar->SetHorizontalFillAmount(ratio);

		//�A�j���[�V�����I����
		if (m_animationTime <= 0)
		{
			m_isAnimation = false;
			m_animationTime = ANIMATION_MAX_TIME;
		}

		//�o�ߎ��Ԃ̉��Z
		m_animationTime -= deltaTime;


	}

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

				m_startRatio = m_currentRatio;

				m_endtRatio = *ratio;

				//�A�j���[�V������L����
				m_isAnimation = true;

				m_animationTime = ANIMATION_MAX_TIME;

				//Hp�o�[�̓h��Ԃ������̕ύX
				m_hpBar->SetHorizontalFillAmount(*ratio);

			}
		}
			break;
		default:
			break;
	}
}
