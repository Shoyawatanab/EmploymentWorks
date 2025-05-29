/*
* プレイヤの通常状態クラス
*/
#pragma once
#include <unordered_map>
#include "Game/Interface/IState.h"

//前方宣言
class Player;
class UserInterface;
class PlayScene;



class GameEndUI : public IState
{
private :

	//初めの何も表示しない時間　（敵の倒れるアニメーションが終わるまでの時間）
	static constexpr float ENEMYANIMATIONTIME{ 3.0f };


	//UIの中心座標
	static constexpr DirectX::SimpleMath::Vector2 CENTERPOSITION {640,360};
	//アニメーション時間
	static constexpr float MAXANIMATIONTIME{ 1.5f };
	//最大の大きさ
	static constexpr DirectX::SimpleMath::Vector2 ENDSCSLE { 1.0f, 1.0f };
	//各UIの最終座標
	static constexpr DirectX::SimpleMath::Vector2 BACKGRAUNDENDPOSITION {640, 360};
	static constexpr DirectX::SimpleMath::Vector2 TITLEUIENDPOSITION {640, 500 };
	static constexpr DirectX::SimpleMath::Vector2 RETRYUIENDPOSITION {640, 370 };
	//拡大率
	static constexpr float EXPANSION{ 1.5f };

	static constexpr DirectX::SimpleMath::Vector2 CHANGEUI_POSITION {200, 650};
	static constexpr DirectX::SimpleMath::Vector2 CHANGEUI_SCALE{0.4f, 0.4f};

	static constexpr DirectX::SimpleMath::Vector2 DECISIONUI_POSITION{570, 650};
	static constexpr DirectX::SimpleMath::Vector2 DECISIONUI_SCALE {0.4f, 0.4f};
	
	static constexpr DirectX::SimpleMath::Vector2 ARROW_UP_POSITION{450, 360};
	static constexpr DirectX::SimpleMath::Vector2 ARROW_DOWN_POSITION2{450, 500};
	static constexpr DirectX::SimpleMath::Vector2 ARROW_SCALE{0.2f, 0.2f};


public:

	//状態
	enum  class State
	{
		TITLE
		,RETRY

	};

public:
	//コンストラクタ
	GameEndUI() ;
	//デストラクタ
	~GameEndUI() override;
	//描画
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//初期化
	void Initialize(CommonResources* resources) ;
	// 更新する
	void Update(const float& elapsedTime) override;
	//状態に入った時
	void Enter() override;
	//状態を抜けた時
	void Exit() override;

	//必要なポインタの登録
	void AddPointer(PlayScene* playScene);


	/// <summary>
	/// 背景の設定
	/// </summary>
	/// <param name="isClear"> ture :クリア  false: ゲームオーバー </param>
	void SetBackGraund(const bool& isClear) {

		if (isClear)
		{
			m_backGraund = m_clearBackGraund.get();
		}
		else
		{
			m_backGraund = m_overBackGraund.get();
			m_enemyAnimationTime = ENEMYANIMATIONTIME;
		}

	}

private:
	//画像の作成
	void CreateTexture();

	//アニメーション
	void Animation(const float& elapsedTime);




private:
	// 共通リソース
	CommonResources* m_commonResources;
	//プレイアy
	Player* m_player;
	//背景
	std::unique_ptr<UserInterface> m_clearBackGraund;
	std::unique_ptr<UserInterface> m_overBackGraund;
	//タイトルUI	
	std::unique_ptr<UserInterface> m_titleUI;
	//リザルトUI	
	std::unique_ptr<UserInterface> m_reTryUI;
	//状態
	State m_state;
	//使用背景
	UserInterface* m_backGraund;
	//プレイシーン
	PlayScene* m_playScene;
	//画像
	std::vector < std::unique_ptr<UserInterface>> m_textures;
	
	std::unique_ptr<UserInterface> m_arrow;
	//画面サイズ
	std::pair<int, int> m_windowSize;
	//座標
	DirectX::SimpleMath::Vector3 m_position;
	//大きさ
	DirectX::SimpleMath::Vector3 m_scale;
	//回転
	DirectX::SimpleMath::Quaternion m_rotation;
	//アニメーション時間
	float m_animationTime;

	float m_enemyAnimationTime;

};