/*
* プレイヤの通常状態クラス
*/
#pragma once
#include "Game/Interface/IStateMachine.h"
#include "Game/Interface/IState.h"
#include "Game/UI/State/GamePlayUI.h"
#include "Game/UI/State/GameEndUI.h"

class Player;
class PlayScene;
class EnemyManager;

class UIStateMachine : public IStateMachine 
{
public:
	//コンストラクタ
	UIStateMachine() ;
	//デストラクタ
	~UIStateMachine() override;

	//初期化
	void Initialize(CommonResources* resources, IState* startState  =nullptr) override;
	// 更新する
	void Update(const float& elapsedTime) override;
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//状態の変更
	void ChangeState(IState* nextState) override;


	//必要なポインタの登録
	void AddPointer(Player* player, PlayScene* playScene, EnemyManager* enemyManager);
	//現在の状態の取得
	IState* GetCurrentState() { return m_currentState; }

	GamePlayUI* GetGamePlayUI() { return m_playUi.get(); }

	GameEndUI* GetGameEndUI() { return m_gameEndUI.get(); }





private:
	//現在の状態
	IState* m_currentState;
	//通常状態
	std::unique_ptr<GamePlayUI> m_playUi;
	//クリア
	std::unique_ptr<GameEndUI> m_gameEndUI;
	
};