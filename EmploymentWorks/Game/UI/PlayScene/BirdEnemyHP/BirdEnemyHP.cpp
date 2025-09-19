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
#include "Game/Enemies/BirdEnemy/BirdEnemy.h"
#include "Game/MathUtil.h"


/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
BirdEnemyHP::BirdEnemyHP(Canvas* canvas, Actor* owner)
	:
	Actor(canvas->GetScene())
	,m_owner{owner}
	,m_hpBar{}
	,m_backGraund{}
	,m_redHpBar{}
	,m_currentRatio{1.0f}
	,m_startRatio{}
	,m_endtRatio{}
	, m_isAnimation{false}
	,m_animationTime{ANIMATION_MAX_TIME}
{
	using namespace DirectX::SimpleMath;

	auto birdEnmey = static_cast<BirdEnemy*>(owner);

	birdEnmey->SetHpBar(this);

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

	//���W�̎w��
	GetTransform()->SetPosition(owner->GetTransform()->GetWorldPosition() + OFFSET_POSITION);




}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEnemyHP::~BirdEnemyHP()
{

}

/// <summary>
/// �P�̍X�V
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void BirdEnemyHP::UpdateActor(const float& deltaTime)
{

	//���W�̎w��
	GetTransform()->SetPosition(m_owner->GetTransform()->GetWorldPosition() + OFFSET_POSITION);

	//�A�j���[�V����
	if (m_isAnimation)
	{
		//���Ԃ̊��������߂�
		float timeRation = (ANIMATION_MAX_TIME - m_animationTime) / ANIMATION_MAX_TIME;
		//�\�����������߂�
		float ratio = MathUtil::Lerp(m_startRatio,m_endtRatio,timeRation);
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
/// �����̓o�^
/// </summary>
/// <param name="ration">����</param>
void BirdEnemyHP::SetRatio(float ration)
{
	
	m_startRatio =  m_currentRatio;

	m_endtRatio = ration;

	//�A�j���[�V������L����
	m_isAnimation = true;

	m_animationTime = ANIMATION_MAX_TIME;


	//HP�o�[��
	m_hpBar->SetHorizontalFillAmount(ration);

}