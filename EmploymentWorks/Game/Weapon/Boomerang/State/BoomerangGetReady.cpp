#include "pch.h"
#include "BoomerangGetReady.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Params.h"


#include "Libraries/Microsoft/DebugDraw.h"




/// <summary>
/// コンストラクタ
/// </summary>
BoomerangGetReady::BoomerangGetReady(Boomerang* boomerang)
	:
	m_commonResources{}
	,m_boomerang{boomerang}
{
}

/// <summary>
/// デストラクタ
/// </summary>
BoomerangGetReady::~BoomerangGetReady()
{
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



