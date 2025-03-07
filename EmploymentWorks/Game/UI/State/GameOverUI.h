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

namespace WataLib
{
	class DrawTexture;
}

class GameOverUI : public IState ,  public IObserver
{

private :

	static constexpr int HP_COUNT{ 3 };
	static constexpr DirectX::SimpleMath::Vector2 HP_POSITION        { 50.0f,680.0f};
	static constexpr DirectX::SimpleMath::Vector2 HP_POSITION_OFFSET { 70.0f,1.0f};
	static constexpr DirectX::SimpleMath::Vector2 HP_SCALE { 1.0f,1.0f};

	static constexpr int BOOMERANG_COUNT{ 3 };
	static constexpr DirectX::SimpleMath::Vector2 BOOMERANG_POSITION        { 50.0f, 600.0f};
	static constexpr DirectX::SimpleMath::Vector2 BOOMERANG_POSITION_OFFSET { 70.0f, 1.0f};
	static constexpr DirectX::SimpleMath::Vector2 BOOMERANG_SCALE { 0.1f, 0.1f};

public:
	//コンストラクタ
	GameOverUI() ;
	//デストラクタ
	~GameOverUI() override;

	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;

	//必要なポインタの登録
	void AddPointer(Player* player);

private:

	//画像の読み込み
	std::unique_ptr<UserInterface> AddTexture(const wchar_t* path
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, ANCHOR anchor
		, UserInterface::Kinds kind);



	void CreateEnemyHP();

	void CreatePlayerHP();

	void CreateBoomerang();



//継承関数
public:
//IState
	//初期化
	void Initialize(CommonResources* resources) override;
	// 更新する
	void Update(const float& elapsedTime) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;


	//IObserver
//通知時に呼ばれる関数
	void Notify(EventManager::EventTypeName type) override;

public:
	// 共通リソース
	CommonResources* m_commonResources;
	//プレイアy
	Player* m_player;
	//プレイヤHP
	std::vector<std::unique_ptr<WataLib::DrawTexture>> m_playerHP;
	//ブーメラン残機
	std::vector<std::unique_ptr<WataLib::DrawTexture>> m_boomerang;

	std::unique_ptr<UserInterface> m_enemyHP;
	std::vector<std::unique_ptr<UserInterface>> m_enemyHPBase;



private :

	std::pair<int, int> m_windowSize;

	//座標
	DirectX::SimpleMath::Vector3 m_position;
	//大きさ
	DirectX::SimpleMath::Vector3 m_scale;
	//回転
	DirectX::SimpleMath::Quaternion m_rotation;
	
	int m_playerHPCount;

	int m_boomerangCount;
	

};