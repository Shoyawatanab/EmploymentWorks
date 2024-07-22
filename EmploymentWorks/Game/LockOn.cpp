/*
	@file	LockOn.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "LockOn.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Object/Player.h"
#include "Game/Object/Enemy/Enemy.h"
#include "Libraries/MyLib/Camera/TPS_Camera.h"
#include "Libraries/MyLib/Camera/GameCameraManager.h"

const float LOCKONDISTANCE = 20.0f;
//視野角
const float VIEWANGLE = 60.0f;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
LockOn::LockOn(Player* player, Enemy* enemy, mylib::GameCameraManager* gameCamera)
	:
	m_windowHeight(0)
	, m_windowWidth(0)
	, m_pDR(nullptr),
	m_player{player}
	,m_enemy{enemy}
	, m_tpsCamera{ gameCamera->GetTPSCamera() }
	, m_isLockOn{ false }

{
	m_userInterface.clear();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
LockOn::~LockOn()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void LockOn::Initialize(DX::DeviceResources* pDR, int width, int height)
{
	using namespace DirectX::SimpleMath;
	assert(pDR);

	m_pDR = pDR;
	m_windowWidth = width;
	m_windowHeight = height;

	//  背景となるウィンドウ画像を読み込む

	//  草画像を読み込む
	Add(L"Resources/Textures/LockOnTex.png"
		,Vector2(300, 300)
		,Vector2(0.1f, 0.1f)
		,ANCHOR::MIDDLE_CENTER);
	m_isLockOn = false;

}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void LockOn::Update(float elapsedTime)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	UNREFERENCED_PARAMETER(elapsedTime);

	//ロックオンのリセット
	m_isLockOn = false;

	////視野角外なら
	if (!IsEnemyInview(m_player->GetPos(), m_player->GetPlayerForWard(), m_enemy->GetPos()))
	{
		return;
	}


	//ブーメランを構えていないなら

	if (m_player->GetBoomerang()->GetBoomerangState() != m_player->GetBoomerang()->GetBoomerangGetReady())
	{
		return;
	}



	Vector3 PlayerPos = m_player->GetPosition();
	Vector3 EnemyPos = m_enemy->GetPosition();

	Vector3 Distance = PlayerPos - EnemyPos;

	//距離外なら
	if (Distance.Length() >= LOCKONDISTANCE)
	{
		m_isLockOn = false;
		return;
	}
	else // 距離内なら
	{
   		m_isLockOn = true;


    		Vector2 ScreenPos = WorldToScreen(m_enemy->GetPosition(),
			Matrix::Identity,
			m_tpsCamera->GetViewMatrix(),
			m_tpsCamera->GetProjectionMatrix(),
			m_windowWidth,
			m_windowHeight
		);

		m_userInterface[0]->SetPosition(ScreenPos);

	}

}

//---------------------------------------------------------
// 描画する	
//---------------------------------------------------------
void LockOn::Render()
{
	using namespace DirectX::SimpleMath;

	if (!m_isLockOn)
	{
		return;
	}


	for (int i = 0; i < m_userInterface.size(); i++)
	{
		m_userInterface[i]->Render();
	}


}


void LockOn::Add(const wchar_t* path, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale, ANCHOR anchor)
{
	//  メニューとしてアイテムを追加する
	std::unique_ptr<UserInterface> userInterface = std::make_unique<UserInterface>();
	//  指定された画像を表示するためのアイテムを作成する
	userInterface->Create(m_pDR
		, path
		, position
		, scale
		, anchor
		,UserInterface::Kinds::LockOn);
	userInterface->SetWindowSize(m_windowWidth, m_windowHeight);

	//  アイテムを新しく追加
	m_userInterface.push_back(std::move(userInterface));





}

/// <summary>
/// ワールド座標をスクリーン座標に変換
/// </summary>
/// <param name="worldPos">ワールド座標</param>
/// <param name="worldMatrix">ワールドの行列</param>
/// <param name="viewMatrix"></param>
/// <param name="projectionMatrix"></param>
/// <param name="screenWidth"></param>
/// <param name="screenHeight"></param>
/// <returns></returns>
DirectX::SimpleMath::Vector2 LockOn::WorldToScreen(const DirectX::SimpleMath::Vector3& worldPos, 
	const DirectX::SimpleMath::Matrix& worldMatrix,
	const DirectX::SimpleMath::Matrix& viewMatrix,
	const DirectX::SimpleMath::Matrix& projectionMatrix,
	int screenWidth, int screenHeight)
{
	using namespace DirectX::SimpleMath;
	// ワールド座標を変換するための行列を結合
	Matrix transformMatrix = worldMatrix * viewMatrix * projectionMatrix;

	// ワールド座標をプロジェクション空間に変換
	Vector3 projectedPos = Vector3::Transform(worldPos, transformMatrix);

	// 射影された座標をスクリーン座標に変換
	float x = (projectedPos.x / projectedPos.z * 0.5f + 0.5f) * screenWidth;
	float y = (0.5f - projectedPos.y / projectedPos.z * 0.5f) * screenHeight;

	return Vector2(x, y);

}



/// <summary>
///  敵がプレイヤの視界に入っているかどうか
/// </summary>
/// <param name="playerPos">プレイヤ座標</param>
/// <param name="playerForward">プレイヤの向いている方向</param>
/// <param name="enemyPos">敵座標</param>
/// <returns></returns>
bool LockOn::IsEnemyInview(const DirectX::SimpleMath::Vector3& playerPos, const DirectX::SimpleMath::Vector3& playerForward, const DirectX::SimpleMath::Vector3& enemyPos)
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;
	//角度をラジアンに変換
	 float radianViewAngle = XMConvertToRadians(VIEWANGLE);
	float cosViewAngle = cos(radianViewAngle / 2);

	//敵へのベクトルの計算
	Vector3 enemyVector = enemyPos - playerPos;
	enemyVector.Normalize();

	//ドット積の計算
	float dotProduct = enemyVector.Dot(playerForward);

	return dotProduct >= cosViewAngle;

}

