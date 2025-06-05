#include "pch.h"
#include "BoomerangIdle.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Player/Player.h"
#include "Game/Observer/Messenger.h"
#include "Game/Params.h"
#include "Game/InstanceRegistry.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
BoomerangIdle::BoomerangIdle(Boomerang* boomerang)
	:
	m_commonResources{}
	,m_boomerang{boomerang}
	,m_player{}
{



}

/// <summary>
/// デストラクタ
/// </summary>
BoomerangIdle::~BoomerangIdle()
{
}



/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void BoomerangIdle::Initialize(CommonResources* resources)
{
	m_commonResources = resources;


	m_player = InstanceRegistry::GetInstance()->GetRegistryInstance<Player>("Player");


}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BoomerangIdle::Update(const float& elapsedTime)
{

	UNREFERENCED_PARAMETER(elapsedTime);


}



/// <summary>
/// 状態に入った時
/// </summary>
void BoomerangIdle::Enter()
{

	//親を登録
	m_boomerang->SetParent(m_player);
	//ローカル回転の設定
	m_boomerang->SetLocalRotation(Params::BOOMERANG_IDLE_ROTATION);
	//ローカル座標の設定
	m_boomerang->SetLocalPosition(Params::BOOMERANG_IDLE_POSITION);
	//ローカルサイズの設定
	m_boomerang->SetLocalScale(Vector3(10,10,10));
	//通知をする
	Messenger::GetInstance()->Notify(GamePlayMessageType::GET_BOOMERANG, nullptr);

	
}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BoomerangIdle::Exit()
{
}



