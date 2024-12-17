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
#include "Game/Screen.h"


#include "Game/Object/Player/Player.h"
#include "Game/Object/Enemy/BossEnemy.h"
#include "Libraries/MyLib/Camera/TPS_Camera.h"
#include "Libraries/MyLib/Camera/GameCameraManager.h"

const float LOCKONDISTANCE = 20.0f;
//視野角
const float VIEWANGLE = 60.0f;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
LockOn::LockOn()
	:
	m_windowHeight(0)
	, m_windowWidth(0)
	, m_pDR(nullptr),
	m_player{}
	, m_enemy{}
	, m_tpsCamera{ }
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
		, Vector2(300, 300)
		, Vector2(0.3f, 0.3f)
		, ANCHOR::MIDDLE_CENTER);

	m_isLockOn = false;

}

//

/// <summary>
/// 範囲内のオブジェクトを探す
/// </summary>
/// <param name="points">座標の配列</param>
/// <param name="center">中心座標</param>
/// <param name="range">半径</param>
/// <returns>範囲内の座標</returns>
DirectX::SimpleMath::Vector2 LockOn::FilterWithinRange(const std::vector<DirectX::SimpleMath::Vector3>& points, const DirectX::SimpleMath::Vector2& center, float range)
{

	using namespace DirectX::SimpleMath;
	//変数宣言
	DirectX::SimpleMath::Vector2 result = Vector2(-100, -100);

	float minLength = 1000;

	//
	for (const auto& point : points)
	{
		//座標をスクリーン座標に変換
		Vector2 ScreenPos = WorldToScreen(point,
			Matrix::Identity,
			m_tpsCamera->GetViewMatrix(),
			m_tpsCamera->GetProjectionMatrix(),
			m_windowWidth,
			m_windowHeight
		);

		float distance = Vector2::Distance(ScreenPos, center);

		//raneg内の座標かどうかの判定
		if (distance <= range)
		{
			//最小値よりも小さければ
			if (minLength > distance)
			{

				//配列に格納
				result = ScreenPos;
				//最小値を更新
				minLength = distance;
				//ターゲットを更新
				m_target = point;

			}

		}
	}

	return result;

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

	//ブーメランを構えていないなら
	if (m_player->GetUsingBoomerang()->GetBoomerangState() != m_player->GetUsingBoomerang()->GetBoomerangGetReady())
	{
		return;
	}

	std::vector<DirectX::SimpleMath::Vector3> positions;

	for (auto& object : m_targetObject)
	{
		positions.push_back(object->GetPosition());
	}

	DirectX::SimpleMath::Vector2 center = Vector2(Screen::CENTER_X, Screen::CENTER_Y);

	DirectX::SimpleMath::Vector2 result = FilterWithinRange(positions, center, 200.0f);

	if (result == Vector2(-100, -100))
	{
		return;
	}


	DirectX::SimpleMath::Vector2 minPosition;

	m_isLockOn = true;

	m_userInterface[0]->SetPosition(result);

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

void LockOn::RegistrationInformation(Player* player, Enemy* enemy, mylib::GameCameraManager* gameCamera)
{

	m_player = player;
	m_enemy = enemy;
	m_tpsCamera = gameCamera->GetTPSCamera();

}

void LockOn::Instances()
{



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
		, UserInterface::Kinds::LockOn);
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



