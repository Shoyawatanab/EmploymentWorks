/*
	@file	DamageCountUI.cpp
	@brief	タイトルシーンクラス
*/
#include "pch.h"
#include "DamageCountUI.h"
#include "Game/Screen.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/MyLib/InputManager.h"
#include <cassert>


#include "Libraries/MyLib/DebugString.h"
#include "Libraries/WataLib/UserInterface.h"
#include "Libraries/WataLib/DrawNumber.h"


using namespace DirectX;
using namespace DirectX::SimpleMath;

void WataLib::DamageCountUI::SetPosition(DirectX::SimpleMath::Vector3 Pos)
{
	 m_position = Pos;
}

void WataLib::DamageCountUI::SetScale(DirectX::SimpleMath::Vector2 scale)
{
	m_scale = scale;
	m_backGraund->SetScale(m_scale);
	m_numberUI->SetScale(m_scale);
}

void WataLib::DamageCountUI::SetRotate(float rotate)
{
	m_rotate = rotate;
	m_backGraund->SetRenderRatio(rotate);
}


void WataLib::DamageCountUI::SetDamage(int damage)
{

	m_damage = damage;


	m_digitNumber.clear();

	//２桁あるかどうか
	if (m_damage >= 10)
	{
		std::pair<int, DirectX::SimpleMath::Vector2> datas;

		//2桁目
		datas.first = m_damage / 10;
		datas.second = DirectX::SimpleMath::Vector2(-DIGITWIDTH, 0);

		m_digitNumber.push_back(datas);

		//1桁目
		datas.first = m_damage % 10;
		datas.second = DirectX::SimpleMath::Vector2(DIGITWIDTH, 0);

		m_digitNumber.push_back(datas);

	}
	else
	{
		std::pair<int, DirectX::SimpleMath::Vector2> datas;

		//１桁目
		datas.first = m_damage % 10;
		datas.second = DirectX::SimpleMath::Vector2::Zero;

		m_digitNumber.push_back(datas);

	}

}

void WataLib::DamageCountUI::SetScreenPosition(DirectX::SimpleMath::Vector2 position)
{

	m_screenPosition = position;

	m_backGraund->SetPosition(m_screenPosition);
	m_numberUI->SetPosition(m_screenPosition);

}

// コンストラクタ
//---------------------------------------------------------
WataLib::DamageCountUI::DamageCountUI(CommonResources* resources)
	:
	m_commonResources{resources},
	m_texture{},
	m_texCenter{},
	m_position{},
	m_scale{},
	m_rotate{}
	,m_backGraund{}
	,m_numberUI{}
	,m_damage{}
	,m_screenPosition{}
	,m_isActive{false}
	,m_digitNumber{}
	,m_time{}
{

	m_numberUI = std::make_unique<DrawNumber>();

}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
WataLib::DamageCountUI::~DamageCountUI()
{
	// do nothing.


}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void WataLib::DamageCountUI::Initialize()
{


	m_backGraund = std::make_unique<UserInterface>();
	m_backGraund = LoadTexture("DamageBackGraund"
		, Vector2(640, 50)
		, Vector2(1.0f, 1.0f)
	);


	m_numberUI->Create(m_commonResources->GetDeviceResources(),
		L"Resources/Textures/Number.png"
		, Vector2::Zero
		, Vector2::One);

	m_scale = Vector2(0.1f, 0.1f);

	SetPosition(m_position);
	SetScale(m_scale);

}


void WataLib::DamageCountUI::Update(const float& elapsedTime)
{

	if (!m_isActive)
	{
		return;
	}

	if (m_time >= MAXTIME)
	{

		m_isActive = false;
		m_time = 0;
		return;
	}


	m_time += elapsedTime;

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void WataLib::DamageCountUI::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	if (!m_isActive)
	{
		return;
	}

	//座標をスクリーン座標に変換して登録
	SetScreenPosition(WorldToScreen(m_position,
		Matrix::Identity, view, projection, Screen::WIDTH, Screen::HEIGHT));

	m_backGraund->Render();
	
	m_damage = 1;
	
	for (int i = 0; i < m_digitNumber.size(); i++)
	{
		m_numberUI->Render(m_digitNumber[i].first % 10,m_digitNumber[i].second);
	}



}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void WataLib::DamageCountUI::Finalize()
{
	// do nothing.

}

std::unique_ptr<UserInterface> WataLib::DamageCountUI::LoadTexture(std::string key, DirectX::SimpleMath::Vector2 position, DirectX::SimpleMath::Vector2 scale)
{
	//  メニューとしてアイテムを追加する
	std::unique_ptr<UserInterface> userInterface = std::make_unique<UserInterface>();
	//  指定された画像を表示するためのアイテムを作成する
	userInterface->Create(m_commonResources
		, key
		, position
		, scale
	);

	return userInterface;
}

DirectX::SimpleMath::Vector2 WataLib::DamageCountUI::WorldToScreen(const DirectX::SimpleMath::Vector3& worldPos, const DirectX::SimpleMath::Matrix& worldMatrix, const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix, int screenWidth, int screenHeight)
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




