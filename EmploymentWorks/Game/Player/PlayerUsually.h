/*
* プレイヤの常時の更新のクラス
*/
#pragma once
#include"Game/Interface/IObserver.h"

// 前方宣言
class CommonResources;
class Player;

namespace WataLib
{
	class TPS_Camera;
}

class PlayerUsually  : public IObserver<GameMessageType>
{
public:
	//コンストラクタ
	PlayerUsually() ;
	//デストラクタ
	~PlayerUsually();
	//
	void AddPointer(Player* player, WataLib::TPS_Camera* tpsCamera);

	//初期化
	void Initialize(CommonResources* resources);
	// 更新する
	void Update(const float& elapsedTime);
	//動き
	void Move(const float& elapsedTime, DirectX::SimpleMath::Vector3 moveDirection);
	//回転
	void Rotation(const float& elapsedTime, DirectX::SimpleMath::Vector3 moveDirection);

	//IObserver
	//通知時に呼ばれる関数
	void Notify(const Telegram<GameMessageType>& telegram)  override;


private:
	//ポインタ
	//プレイヤ
	Player* m_palyer;
	//カメラ
	WataLib::TPS_Camera* m_tpsCamera;
	// 共通リソース
	CommonResources* m_commonResources;

	//構えているかどうか
	bool m_isGetReady;

};