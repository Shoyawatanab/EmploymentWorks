#pragma once
#include "Game/Entities/UIBaseEntity.h"
#include "Game/Interface/IObserver.h"

class UserInterface;

class BossEnemyHP : public UIBaseEntity , public IObserver<GamePlayMessageType>
{

private:


	//ボスHP関係
	static constexpr DirectX::SimpleMath::Vector2 ENEMY_HP_BASE_POSITION{640, 50};
	static constexpr DirectX::SimpleMath::Vector2 ENEMY_HP_BASE_SCALE{0.9f, 0.5f};

	static constexpr DirectX::SimpleMath::Vector2 ENEMY_HP_POSITION     {640, 50};
	static constexpr DirectX::SimpleMath::Vector2 ENEMY_HP_SCALE        {0.9f, 0.39f};

	static constexpr DirectX::SimpleMath::Vector2 ENEMY_NAME_POSITION     {640, 25};
	static constexpr DirectX::SimpleMath::Vector2 ENEMY_NAME_SCALE        {0.3f, 0.3f};


public:
	//コンストラクタ
	BossEnemyHP(CommonResources* resources);
	//デストラクタ
	~BossEnemyHP();

	//初期化
	void Initialize();
	//更新処理
	void  Update(const float& elapsedTime);
	//描画
	void Render();

private:

	//IObserver
//通知時に呼ばれる関数
	void Notify(const Telegram<GamePlayMessageType>& telegram)  override;


private:


	std::unique_ptr<UserInterface> m_enemyName;
	std::unique_ptr<UserInterface> m_enemyHP;
	std::unique_ptr<UserInterface> m_enemyHPBase;


};