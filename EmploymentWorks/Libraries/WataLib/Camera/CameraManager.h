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
	class CameraManager : public IObserver
	{
	public:

		const DirectX::SimpleMath::Matrix& GetViewMatrix() const { return m_currentState->GetViewMatrix(); }

		ICamera* GetGameCameraState() { return m_currentState; }

		WataLib::TPS_Camera* GetTPSCamera() { return m_tpsCamera.get(); }

		WataLib::GameEndCamera* GetEndCamera() { return m_endCamera.get(); }

		

	public:
		// コンストラクタ
		CameraManager();

		// デストラクタ
		~CameraManager();

		void Initialize(CommonResources* resources);


		// 更新処理
		void Update(float elapsedTime);

		void ChangeState(ICamera* nestState);

		//クラスに必要な情報（ポインタ）を登録する
		void AddPointer(Player* Player,EnemyManager* enemyManger);

		//IObserver
//通知時に呼ばれる関数
		void Notify(const Telegram& telegram)  override;

	private:

		ICamera* m_currentState;
		std::unique_ptr<WataLib::TPS_Camera> m_tpsCamera;

		std::unique_ptr<WataLib::GameEndCamera> m_endCamera;

		Player* m_player;


	};
}
