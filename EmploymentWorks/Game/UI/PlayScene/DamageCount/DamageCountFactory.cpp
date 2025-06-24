#include "pch.h"
#include "DamageCountFactory.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "Game/UI/PlayScene/DamageCount/DamageCount.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Messenger/Messenger.h"

/// <summary>
/// コンストラク
/// </summary>
/// <param name="canvas">キャンバス</param>
DamageCountFactory::DamageCountFactory(Canvas* canvas)
	:
	Actor(canvas->GetScene())
	,m_damageCount{}
{
	//定数文事前に作成
	for (int i = 0; i < MAX; i++)
	{
		auto damageCount = GetScene()->AddActor<DamageCount>(canvas);
		m_damageCount.push_back(damageCount);
	}

	Messenger::GetInstance()->Rigister(
		{
			MessageType::ENEMY_DAMAGE
		}, this
	);

}

/// <summary>
/// デストラクタ
/// </summary>
DamageCountFactory::~DamageCountFactory()
{
}

/// <summary>
/// 通知を受け取る関数
/// </summary>
/// <param name="type">通知の種類</param>
/// <param name="datas">追加データ</param>
void DamageCountFactory::Notify(MessageType type, void* datas)
{

	switch (type)
	{
		case MessageType::ENEMY_DAMAGE:
			
			for (auto& ui : m_damageCount)
			{
				//非アクティブなら
				if (!ui->GetActive())
				{
					//アクティブに
					ui->SetActive(true);

					//追加データからダメージをキャスト
					ui->SetDamage(*static_cast<int*>(datas));

					break;
				}
			}

			break;
		default:
			break;
	}

}
