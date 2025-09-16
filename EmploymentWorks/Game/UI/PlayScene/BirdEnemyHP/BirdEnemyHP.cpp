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

/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
BirdEnemyHP::BirdEnemyHP(Canvas* canvas)
	:
	Actor(canvas->GetScene())
{
	using namespace DirectX::SimpleMath;

	//背景
	m_backGraund = GetScene()->AddActor<Image>(canvas, "BossHPBase");
	m_backGraund->GetTransform()->SetScale(BACKGRAUND_SCALE);
	m_backGraund->GetTransform()->SetParent(GetTransform());

	//Hpバー
	m_hpBar = GetScene()->AddActor<Image>(canvas, "EnemyHP");
	m_hpBar->GetTransform()->SetScale(HP_BAR_SCALE);
	m_hpBar->GetTransform()->SetParent(GetTransform());

	GetTransform()->SetPosition(POSITION);

	////通知を受け取るコンポーネントの追加
	//auto ob = AddComponent<ObserverComponent<SceneMessageType>>(this);
	////どの通知かの登録と呼び出す関数の登録
	//ob->Rigister(
	//	{
	//		SceneMessageType::BOSS_DAMAGE
	//	}
	//	, std::bind(&BirdEnemyHP::Notify, this, std::placeholders::_1, std::placeholders::_2)
	//);


}

/// <summary>
/// デストラクタ
/// </summary>
BirdEnemyHP::~BirdEnemyHP()
{
}

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void BirdEnemyHP::Notify(SceneMessageType type, void* datas)
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
				//Hpバーの塗りつぶし割合の変更
				m_hpBar->SetHorizontalFillAmount(*ratio);
			}
		}
			break;
		default:
			break;
	}
}
