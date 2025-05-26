#include "pch.h"
#include "PlayerIdle.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Game/Player/Player.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Weapon/Boomerang/State/BoomerangStateMachine.h"



/// <summary>
/// コンストラクタ
/// </summary>
PlayerIdle::PlayerIdle(Player* player)
	:
	m_commonResources{}
	,m_position{}
	,m_scale{}
	,m_rotation{}
	,m_player{player}
{


}

/// <summary>
/// デストラクタ
/// </summary>
PlayerIdle::~PlayerIdle()
{
}




/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void PlayerIdle::Initialize(CommonResources* resources)
{
	m_commonResources = resources;




}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void PlayerIdle::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	using namespace DirectX;


	const auto& tracker = m_commonResources->GetInputManager()->GetMouseTracker();

	//左ボタンが押されたら
	if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		m_player->GetPlayerStateMachine()->ChangeState(m_player->GetPlayerStateMachine()->GetPlayerAttack());
	}


}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void PlayerIdle::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);

}

/// <summary>
/// 状態に入った時
/// </summary>
void PlayerIdle::Enter()
{

	m_player->ChangeAnimation("Idle");


}

/// <summary>
/// 状態を抜けた時
/// </summary>
void PlayerIdle::Exit()
{
}



