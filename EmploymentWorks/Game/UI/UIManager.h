#pragma once
/*
	@file	UIManager.h.h
	@brief	敵の管理クラス
*/
#pragma once
#include "pch.h"
#include "Game/Interface/IObserver.h"

// 前方宣言
class CommonResources;
class UIStateMachine;
class Player;
class PlayScene;

class UIManager :  public IObserver<GamePlayMessageType>
{


public:
	//コンストラクタ
	UIManager();
	//デストラクタ
	~UIManager() ;
	//初期化
	void Initialize(CommonResources* resources);
	//更新処理
	void Update(const float& elapsedTime);
	//描画処理
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) ;
	//
	void Finalize() ;

	//必要なポインタの登録
	void AddPointer(PlayScene* playScene);

	//IObserver
//通知時に呼ばれる関数
	void Notify(const Telegram<GamePlayMessageType>& telegram)  override;

private:
	// 共通リソース
	CommonResources* m_commonResources;
	//ステートマシーン
	std::unique_ptr<UIStateMachine> m_stateMahine;

};
