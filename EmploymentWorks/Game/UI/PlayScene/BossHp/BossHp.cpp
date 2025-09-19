/*
	クラス名     : BossHp
	説明         : ボスHPのUI
	補足・注意点 :
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
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
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

	GetTransform()->SetPosition(POSITION);

	//通知を受け取るコンポーネントの追加
	auto ob = AddComponent<ObserverComponent<SceneMessageType>>(this);
	//どの通知かの登録と呼び出す関数の登録
	ob->Rigister(
		{
			SceneMessageType::BOSS_DAMAGE
		}
		, std::bind(&BossHp::Notify, this, std::placeholders::_1, std::placeholders::_2)
	);

}

/// <summary>
/// デストラクタ
/// </summary>
BossHp::~BossHp()
{
}

/// <summary>
/// 個別更新
/// </summary>
/// <param name="deltaTime">経過時間</param>
void BossHp::UpdateActor(const float& deltaTime)
{

	//アニメーション
	if (m_isAnimation)
	{
		//時間の割合を求める
		float timeRation = (ANIMATION_MAX_TIME - m_animationTime) / ANIMATION_MAX_TIME;
		//表示割合を求める
		float ratio = MathUtil::Lerp(m_startRatio, m_endtRatio, timeRation);
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
/// 通知を受け取る関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void BossHp::Notify(SceneMessageType type, void* datas)
{
	switch (type)
	{
		case SceneMessageType::BOSS_DAMAGE:
		{
			//キャストして割合を求める
			float* ratio = static_cast<float*>(datas);
			//正しくキャストできているか

			if (typeid(*ratio) == typeid(float))
			{

				m_startRatio = m_currentRatio;

				m_endtRatio = *ratio;

				//アニメーションを有効に
				m_isAnimation = true;

				m_animationTime = ANIMATION_MAX_TIME;

				//Hpバーの塗りつぶし割合の変更
				m_hpBar->SetHorizontalFillAmount(*ratio);

			}
		}
			break;
		default:
			break;
	}
}
