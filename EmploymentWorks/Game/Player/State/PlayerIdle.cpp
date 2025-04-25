#include "pch.h"
#include "PlayerIdle.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Game/Player/Player.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Weapon/Boomerang/State/BoomerangStateMachine.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
PlayerIdle::PlayerIdle()
	:
	m_commonResources{}
	,m_position{}
	,m_scale{}
	,m_rotation{}
	,m_player{}
{


}

/// <summary>
/// デストラクタ
/// </summary>
PlayerIdle::~PlayerIdle()
{
}


/// <summary>
/// 必要なポインタの追加
/// </summary>
/// <param name="player">プレイヤ</param>
void PlayerIdle::AddPointer(Player* player)
{
	m_player = player;
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


	const auto& tracker = m_commonResources->GetInputManager()->GetMouseTracker();

	//左ボタンが押されたら
	if (tracker->leftButton == Mouse::ButtonStateTracker::ButtonState::PRESSED)
	{
		m_player->GetPlayerStateMachine()->ChangeState(m_player->GetPlayerStateMachine()->GetPlayerAttack());
	}


}

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



