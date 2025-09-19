/*
	クラス名     : BirdEnemyHP
	説明         : 鳥敵のHPのUI
	補足・注意点 :
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
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
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

	//背景
	m_backGraund = GetScene()->AddActor<Image>(canvas, "BossHPBase");
	m_backGraund->GetTransform()->SetScale(BACKGRAUND_SCALE);
	m_backGraund->GetTransform()->SetParent(GetTransform());

	//赤のHpバー
	m_redHpBar = GetScene()->AddActor<Image>(canvas, "EnemyHP");
	m_redHpBar->GetTransform()->SetScale(HP_BAR_SCALE);
	m_redHpBar->GetTransform()->SetParent(GetTransform());
	//赤色に指定
	m_redHpBar->SetColor(Vector4(255, 0, 0, 1));



	//Hpバー
	m_hpBar = GetScene()->AddActor<Image>(canvas, "EnemyHP");
	m_hpBar->GetTransform()->SetScale(HP_BAR_SCALE);
	m_hpBar->GetTransform()->SetParent(GetTransform());

	//座標の指定
	GetTransform()->SetPosition(owner->GetTransform()->GetWorldPosition() + OFFSET_POSITION);




}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyHP::~BirdEnemyHP()
{

}

/// <summary>
/// 単体更新
/// </summary>
/// <param name="deltaTime">経過時間</param>
void BirdEnemyHP::UpdateActor(const float& deltaTime)
{

	//座標の指定
	GetTransform()->SetPosition(m_owner->GetTransform()->GetWorldPosition() + OFFSET_POSITION);

	//アニメーション
	if (m_isAnimation)
	{
		//時間の割合を求める
		float timeRation = (ANIMATION_MAX_TIME - m_animationTime) / ANIMATION_MAX_TIME;
		//表示割合を求める
		float ratio = MathUtil::Lerp(m_startRatio,m_endtRatio,timeRation);
		//赤色のバーの変更
		m_redHpBar->SetHorizontalFillAmount(ratio);

		//アニメーション終了時
		if (m_animationTime <= 0)
		{
			m_isAnimation = false;
			m_animationTime = ANIMATION_MAX_TIME;
		}

		//経過時間の加算
		m_animationTime -= deltaTime;

	}


}

/// <summary>
/// 割合の登録
/// </summary>
/// <param name="ration">割合</param>
void BirdEnemyHP::SetRatio(float ration)
{
	
	m_startRatio =  m_currentRatio;

	m_endtRatio = ration;

	//アニメーションを有効に
	m_isAnimation = true;

	m_animationTime = ANIMATION_MAX_TIME;


	//HPバーを
	m_hpBar->SetHorizontalFillAmount(ration);

}