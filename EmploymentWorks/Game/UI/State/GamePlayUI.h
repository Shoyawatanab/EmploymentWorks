/*
* プレイヤの通常状態クラス
*/
#pragma once
#include <unordered_map>
#include "Game/Interface/IState.h"
#include "Game/Interface/IObserver.h"

#include "Libraries/WataLib/UserInterface.h"


class Player;
class UserInterface;

class EnemyManager;
namespace WataLib 
{
	class DamageCountUI;
}


class GamePlayUI : public IState ,  public IObserver<GameMessageType>
{

private :

	//プレイヤHP関係
	static constexpr int HP_COUNT{ 3 };
	static constexpr DirectX::SimpleMath::Vector2 HP_POSITION        { 50.0f,680.0f};
	static constexpr DirectX::SimpleMath::Vector2 HP_POSITION_OFFSET { 70.0f,1.0f};
	static constexpr DirectX::SimpleMath::Vector2 HP_SCALE { 1.0f,1.0f};
	//ブーメラン関係
	static constexpr int BOOMERANG_COUNT{ 3 };
	static constexpr DirectX::SimpleMath::Vector2 BOOMERANG_POSITION        { 50.0f, 600.0f};
	static constexpr DirectX::SimpleMath::Vector2 BOOMERANG_POSITION_OFFSET { 70.0f, 1.0f};
	static constexpr DirectX::SimpleMath::Vector2 BOOMERANG_SCALE { 0.1f, 0.1f};

	static constexpr DirectX::SimpleMath::Vector2 MOVEPOSITION = { -50.0f,0.0f };

	static constexpr int MAXDAMAGEUICOUNT = 10;

	//ボスHP関係
	static constexpr DirectX::SimpleMath::Vector2 ENEMY_HP_BASE_POSITION{640,50};
	static constexpr DirectX::SimpleMath::Vector2 ENEMY_HP_BASE_SCALE{0.9f,0.5f};

	static constexpr DirectX::SimpleMath::Vector2 ENEMY_HP_POSITION     {640, 50};
	static constexpr DirectX::SimpleMath::Vector2 ENEMY_HP_SCALE        {0.9f,0.39f};

	static constexpr DirectX::SimpleMath::Vector2 ENEMY_NAME_POSITION     {640, 25};
	static constexpr DirectX::SimpleMath::Vector2 ENEMY_NAME_SCALE        {0.3f, 0.3f};

	//ブーメランの投げ方のUI
	static constexpr DirectX::SimpleMath::Vector2 RIGHT_THROW_POSITION {1220, 500};
	static constexpr DirectX::SimpleMath::Vector2 RIGHT_THROW_SCALE {0.2f, 0.2f};
	
	static constexpr DirectX::SimpleMath::Vector2 FRONT_THROW_POSITION {1220, 550};
	static constexpr DirectX::SimpleMath::Vector2 FRONT_THROW_SCALE {0.2f, 0.2f};
	
	static constexpr DirectX::SimpleMath::Vector2 LEFT_THROW_POSITION {1220, 600};
	static constexpr DirectX::SimpleMath::Vector2 LEFT_THROW_SCALE {0.2f, 0.2f};


public:
	//コンストラクタ
	GamePlayUI() ;
	//デストラクタ
	~GamePlayUI() override;

	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//初期化
	void Initialize(CommonResources* resources) override;
	// 更新する
	void Update(const float& elapsedTime) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;

	//必要なポインタの登録
	void AddPointer(Player* player, EnemyManager* enemyManager);

	//画像の読み込み
	std::unique_ptr<UserInterface> AddTexture(std::string key
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		);

private:
	//敵HPの作成
	void CreateEnemyHP();
	//プレイヤHPの作成
	void CreatePlayerHP();
	//ブウーメランUIの作成
	void CreateBoomerang();
	//ダメージUIの作成
	void CreateDamageUI(void* datas);

	//IObserver
//通知時に呼ばれる関数
	void Notify(const Telegram<GameMessageType>& telegram)  override;

private:
	//プレイヤがダメージを受けた時
	void PlayerDamage();

private:
	// 共通リソース
	CommonResources* m_commonResources;
	//プレイアy
	Player* m_player;
	//プレイヤHP
	std::vector<std::unique_ptr<UserInterface>> m_playerHP;
	//ブーメラン残機			 
	std::vector<std::unique_ptr<UserInterface>> m_boomerang;

	std::unique_ptr<UserInterface> m_enemyHP;
	std::vector<std::unique_ptr<UserInterface>> m_enemyHPBase;
	//アイテムを回収するときのUI
	std::unique_ptr<UserInterface> m_itemAcquisitionUI;

	//投げ状態のUI
	std::vector<std::unique_ptr<UserInterface>> m_throwUI;
	//敵マネージャー
	EnemyManager* m_enemyManager;
	//画面サイズ
	std::pair<int, int> m_windowSize;

	//座標
	DirectX::SimpleMath::Vector3 m_position;
	//大きさ
	DirectX::SimpleMath::Vector3 m_scale;
	//回転
	DirectX::SimpleMath::Quaternion m_rotation;
	//プレイヤHP
	int m_playerHPCount;
	//ブーメランの数
	int m_boomerangCount;
	//ダメージUI
	std::vector<std::unique_ptr<WataLib::DamageCountUI>> m_damageCountUI;
	


};