#include "pch.h"
#include "BoomerangGetReady.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Params.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
BoomerangGetReady::BoomerangGetReady()
	:
	m_commonResources{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
BoomerangGetReady::~BoomerangGetReady()
{
}


/// <summary>
/// 必要なポインタの追加
/// </summary>
/// <param name="boomerang">ブーメラン</param>
void BoomerangGetReady::AddPointer(Boomerang* boomerang)
{
	m_boomerang = boomerang;
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void BoomerangGetReady::Initialize(CommonResources* resources)
{
	m_commonResources = resources;

}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BoomerangGetReady::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);



}

void BoomerangGetReady::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);

}

/// <summary>
/// 状態に入った時
/// </summary>
void BoomerangGetReady::Enter()
{
	//ローカル回転の設定
	m_boomerang->SetLocalRotation(Params::BOOMERANG_GETREADY_ROTATION);
	//ローカル座標の設定
	m_boomerang->SetLocalPosition(Params::BOOMERANG_GETREADY_POSITION);
}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BoomerangGetReady::Exit()
{


}



