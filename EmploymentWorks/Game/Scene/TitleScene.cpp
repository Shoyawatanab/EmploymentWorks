/*
	@file	TitleScene.cpp
	@brief	タイトルシーンクラス
*/
#include "pch.h"
#include "TitleScene.h"
#include "Game/Screen.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/MyLib/InputManager.h"
#include <cassert>

#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/Texture.h"
#include "Libraries/MyLib/Model3D.h"
#include "Libraries/MyLib/Camera/TitleCamera.h"
#include "Game/Object/Wall.h"
#include "Game/Object/Rock.h"
#include "Game/Object/Ceiling.h"
#include "Game/Object/Pillar.h"
#include "Game/Object/Floor.h"
#include "Game/Object/Player/Player.h"
#include "Game/Object/Enemy/Enemy.h"

#include "Game/Object/Gimmick/Artillery/Artillery.h"
#include "Libraries/MyLib/LoadJson.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

const float SELECTTEXTURESCALE = 1.0f;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
TitleScene::TitleScene()
	:
	m_commonResources{},
	m_camera{},
	m_isChangeScene{},
	m_logo{},
	m_playTexture{},
	m_exitTexture{},
	m_state{},
	m_boomerangTexture{},
	m_models{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
TitleScene::~TitleScene()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void TitleScene::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

	//auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	//auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();

	RECT rect{ m_commonResources->GetDeviceResources()->GetOutputSize() };

	m_projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.1f, 1000.0f
	);

	m_camera = std::make_unique<mylib::TitleCamera>();
	m_camera->Initialize();

	m_logo = std::make_unique<mylib::Texture>();
	m_logo->Initialize(m_commonResources, L"Resources/Textures/Logo.png", DirectX::SimpleMath::Vector2(420,160), 1.0f);

	m_playTexture = std::make_unique<mylib::Texture>();
	m_playTexture->Initialize(m_commonResources, L"Resources/Textures/PLAY.png", DirectX::SimpleMath::Vector2(620, 500), SELECTTEXTURESCALE * 1.3f);

	m_exitTexture = std::make_unique<mylib::Texture>();
	m_exitTexture->Initialize(m_commonResources, L"Resources/Textures/EXIT.png", DirectX::SimpleMath::Vector2(620, 600), SELECTTEXTURESCALE);

	m_boomerangTexture = std::make_unique<mylib::Texture>();
	m_boomerangTexture->Initialize(m_commonResources, L"Resources/Textures/Boomerang.png", DirectX::SimpleMath::Vector2(100, 130), 0.4f);

	m_state = NextState::PLAY;

	//プレイヤモデルの追加
	auto model = std::make_unique<mylib::Model3D>();
	model->Initialize(m_commonResources, L"Resources/Models/Player.cmo" ,Vector3(0, 0.75f, 15),0.4f);
	model->SetRotate(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle( DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(180)));
	m_models.push_back(std::move(model));
	//敵
	model = std::make_unique<mylib::Model3D>();
	model->Initialize(m_commonResources, L"Resources/Models/BossEnemy.cmo", Vector3(0, 5.0f, 0), 1.0f);
	model->SetRotate(DirectX::SimpleMath::Quaternion::CreateFromAxisAngle(DirectX::SimpleMath::Vector3::UnitY, DirectX::XMConvertToRadians(0)));
	m_models.push_back(std::move(model));

	// シーン変更フラグを初期化する
	m_isChangeScene = false;


	m_loadJson = std::make_unique<mylib::LoadJson>();

	//ステージのデータを読み込む
	std::vector<mylib::LoadJson::Parameters> parameters = m_loadJson->GetStageDatas(L"Resources/Dates/Stage.json");


	//ステージオブジェックとの生成
	for (auto& parameter : parameters)
	{

		//ステージの壁
		if (parameter.ModelName == "Stage.cmo")
		{
			auto wall = std::make_unique<Wall>();
			wall->Initialize(m_commonResources, parameter.Position, parameter.Scale, parameter.Rotation, parameter.BoundingSphereRadius);
			m_wall.push_back(std::move(wall));
		}
		else if (parameter.ModelName == "Floor.cmo")
		{
			//床	 
			m_floor = std::make_unique<Floor>();
			m_floor->Initialize(m_commonResources, parameter.Position, parameter.Scale, parameter.Rotation, parameter.BoundingSphereRadius);

		}
		else if (parameter.ModelName == "Ceiling.cmo")
		{
			//天井
			m_ceiling = std::make_unique<Ceiling>();
			m_ceiling->Initialize(m_commonResources, parameter.Position, parameter.Scale, parameter.Rotation, parameter.BoundingSphereRadius);

		}
		else if (parameter.ModelName == "Pillar.cmo")
		{
			//柱
			auto pillar = std::make_unique<Pillar>();
			pillar->Initialize(m_commonResources, parameter.Position, parameter.Scale, parameter.Rotation, parameter.BoundingSphereRadius);
			m_pillar.push_back(std::move(pillar));

		}
		else if (parameter.ModelName == "Artillery.cmo")
		{
			//砲台
			auto artillery = std::make_unique<Artillery>();
			artillery->Initialize(m_commonResources,nullptr, parameter.Position, parameter.Scale, parameter.Rotation, parameter.BoundingSphereRadius);
			m_artillery.push_back(std::move(artillery));

		}
	}



}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void TitleScene::Update(float elapsedTime)
{
	// 宣言をしたが、実際は使用していない変数
	UNREFERENCED_PARAMETER(elapsedTime);

	// キーボードステートトラッカーを取得する
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	//PLAYを選ぶ
	if (kbTracker->released.W)
	{
		m_playTexture->SetScale(SELECTTEXTURESCALE * 1.3f);
		m_exitTexture->SetScale(SELECTTEXTURESCALE);
		m_state = NextState::PLAY;
	}
	//EXITを選ぶ
	if (kbTracker->released.S)
	{
		m_playTexture->SetScale(SELECTTEXTURESCALE);
		m_exitTexture->SetScale(SELECTTEXTURESCALE * 1.3f);
		m_state = NextState::EXIT;

	}


	// スペースキーが押されたら
	if (kbTracker->released.Space)
	{
		switch (m_state)
		{
			case TitleScene::NextState::PLAY:
				m_isChangeScene = true;
				break;
			case TitleScene::NextState::EXIT:
				PostQuitMessage(0);
				break;
			default:
				break;
		}
	}

	float rotate = m_boomerangTexture->GetRotate();
	rotate += 1 * elapsedTime;

	m_camera->Update(elapsedTime);

	//m_boomerangTexture->SetRotate(rotate);

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void TitleScene::Render()
{

	// ビュー行列を取得する
	const Matrix&view = m_camera->GetViewMatrix();
	

	for (auto& model : m_models)
	{
		model->Render(view, m_projection);
	}



	m_floor->Render(view, m_projection);

	for (auto& wall : m_wall)
	{
		wall->Render(view, m_projection);
	}

	for (auto& pillar : m_pillar)
	{
		pillar->Render(view, m_projection);
	}

	//m_ceiling->Render(view, m_projection);




	for (auto& artillery : m_artillery)
	{
		artillery->Render(view, m_projection);
	}




	m_boomerangTexture->Render();
	m_logo->Render();
	m_playTexture->Render();
	m_exitTexture->Render();


}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void TitleScene::Finalize()
{
	// do nothing.
}

//---------------------------------------------------------
// 次のシーンIDを取得する
//---------------------------------------------------------
IScene::SceneID TitleScene::GetNextSceneID() const
{
	// シーン変更がある場合
	if (m_isChangeScene)
	{
		return IScene::SceneID::PLAY;
	}

	// シーン変更がない場合
	return IScene::SceneID::NONE;
}


