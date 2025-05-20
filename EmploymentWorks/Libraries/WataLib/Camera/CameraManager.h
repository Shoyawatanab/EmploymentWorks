/*
	@file	GameCameraManager.h
	@brief	TPSカメラクラス
*/
#pragma once
#include "Game/Interface/ICamera.h"
#include "Game/Interface/IObserver.h"


class Player;
class EnemyManager;

namespace WataLib
{
	class TPS_Camera;
	class GameEndCamera;
}

namespace WataLib
{
	class CameraManager : public IObserver<GameMessageType>
	{
	public:
		//ビュー行列の取得
		const DirectX::SimpleMath::Matrix& GetViewMatrix() const { return m_currentState->GetViewMatrix(); }
		
		ICamera* GetGameCameraState() { return m_currentState; }

		WataLib::TPS_Camera* GetTPSCamera() { return m_tpsCamera.get(); }

		WataLib::GameEndCamera* GetEndCamera() { return m_endCamera.get(); }

		

	public:
		// コンストラクタ
		CameraManager();

		// デストラクタ
		~CameraManager();
		//初期化
		void Initialize(CommonResources* resources);

		// 更新処理
		void Update(float elapsedTime);
		//カメラの切り替え
		void ChangeState(ICamera* nestState);

		//クラスに必要な情報（ポインタ）を登録する
		void AddPointer(Player* Player,EnemyManager* enemyManger);

		//IObserver
//通知時に呼ばれる関数
		void Notify(const Telegram<GameMessageType>& telegram)  override;

	private:
		//現在のカメラ
		ICamera* m_currentState;
		//TPSカメラ
		std::unique_ptr<WataLib::TPS_Camera> m_tpsCamera;
		//ゲーム終了カメラ
		std::unique_ptr<WataLib::GameEndCamera> m_endCamera;
		//プレイヤ
		Player* m_player;


	};
}
