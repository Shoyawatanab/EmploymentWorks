/*
	@file	PlayScene.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "PlayScene.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Libraries/WataLib/Fade.h"
#include <cassert>

#include "Game/StageObject/StageObjectManager.h"
#include "Game/Player/Player.h"
#include "Libraries/WataLib/Json.h"
#include "Libraries/WataLib/Camera/CameraManager.h"
#include "Game/Enemys/EnemyManager.h"
#include "Game/CollisiionManager.h"
#include "Game/UI/UIManager.h"
#include "Game//TargetMarker.h"
#include "Game/Effect/EffectsManager.h"
#include "Game/StageObject/Sky.h"
#include "Game/StageObject/Floor.h"
#include "Game/StageObject/Wall.h"
#include "Game/ItemAcquisition.h"
#include "Game/Score.h"
#include "Libraries/WataLib/UserInterface.h"
#include "Game/Sound/SoundManager.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayScene::PlayScene(SceneManager::StageID stageID)
	:
	m_commonResources{},
	m_projection{},
	m_isChangeScene{},
	m_player{}
	,m_stageObjectManager{}
	,m_enemyManager{}
	,m_cameraManager{}
	,m_collisionManager{}
	,m_uiManager{}
	,m_targetMarker{}
	,m_effectsManager{}
	,m_nextScene{SceneID::NONE}
	,m_stageID{stageID}
	,m_tutorialTex{}
	,m_isTutolialTex{}
{
	Messenger::GetInstance()->Clear();
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayScene::~PlayScene()
{

	// do nothing.



}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void PlayScene::Initialize(CommonResources* resources)
{
	assert(resources);
	m_commonResources = resources;

	// デバッグカメラを作成する
	RECT rect{ m_commonResources->GetDeviceResources()->GetOutputSize() };

	// 射影行列を作成する
	m_projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.1f, 150.0f
	);


	m_nextScene = SceneID::NONE;

	//クラスの生成
	m_stageObjectManager = std::make_unique<StageObjectManager>(m_commonResources);
	m_player = std::make_unique<Player>(m_commonResources);
	m_cameraManager = std::make_unique<WataLib::CameraManager>();
	m_enemyManager = std::make_unique<EnemyManager>(m_player.get(),m_stageObjectManager.get());
	m_collisionManager = std::make_unique<CollisionManager>();
	m_uiManager = std::make_unique<UIManager>();
	m_targetMarker = std::make_unique<TargetMarker>();
	m_effectsManager = std::make_unique<EffectsManager>();
	m_sky = std::make_unique<Sky>(m_commonResources,Vector3::Zero,Vector3::Zero,Quaternion::Identity);


	//各クラスに必要なポインタを登録
	m_cameraManager->AddPointer(m_player.get(),m_enemyManager.get());
	m_player->AddPointer(m_cameraManager->GetTPSCamera(),m_targetMarker.get());
	m_uiManager->AddPointer(m_player.get(),this,m_enemyManager.get());
	m_targetMarker->AddPointer(m_cameraManager->GetTPSCamera());

	//ステージの作成
	CreateStageObject();


	//初期化
	m_stageObjectManager->Initialize();
	m_enemyManager->Initialize(m_commonResources);
	m_player->Initialize();
	m_cameraManager->Initialize(m_commonResources);
	m_collisionManager->Initialize(m_commonResources);
	m_uiManager->Initialize(m_commonResources);
	m_targetMarker->Initialize(m_commonResources);
	m_effectsManager->Initialize(m_commonResources);
	m_sky->Initialize();
	ItemAcquisition::GetInstance()->Initialize(m_commonResources);

	//当たり判定の登録
	m_player->AddCollision(m_collisionManager.get());
	m_enemyManager->AddCollision(m_collisionManager.get());
	m_stageObjectManager->AddCollision(m_collisionManager.get());

	//ターゲットの追加
	m_targetMarker->AddTargetObject(m_enemyManager->GetEnemys());

	//アイテム回収クラスに
	ItemAcquisition::GetInstance()->AddPlayer(m_player.get());


	// シーン変更フラグを初期化する
	m_isChangeScene = false;
	
	//フェードアウトの開始
	m_commonResources->GetFade()->StartNormalFadeOut();


	// オーディオエンジンのフラグ
	AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
	eflags |= AudioEngine_Debug;
#endif


	m_tutorialTex = std::make_unique<UserInterface>();
	m_tutorialTex->Create(m_commonResources, "Tex", Vector2(640, 360), Vector2::One);

	m_isTutolialTex = false;

	m_commonResources->GetScore()->AddScore(100.0f);

	ShowCursor(FALSE);


	m_soundManager = SoundManager::GetInstance();

	m_soundManager->PlaySoundBGM("Play");
	m_soundManager->PlaySoundSE("BoomerangHit");

}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayScene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	//フェードが終わるまで
	if (m_commonResources->GetFade()->GetFadeState() != Fade::FadeState::None)
	{
		return;
	}

	// キーボードステートトラッカーを取得する
	const auto& kbTracker = m_commonResources->GetInputManager()->GetKeyboardTracker();

	if (m_isTutolialTex && kbTracker->released.Space)
	{
		m_tutorialTex->SetScale(Vector2::Zero);
		m_isTutolialTex = false;
	}

	if (m_isTutolialTex)
	{
		return;
	}

	CheckMouseWheel();

	//更新
	m_player->Update(elapsedTime);
	m_enemyManager->Update(elapsedTime);
	ItemAcquisition::GetInstance()->Update();
	m_collisionManager->Update();
	m_cameraManager->Update(elapsedTime);
	m_uiManager->Update(elapsedTime);
	m_targetMarker->Update(elapsedTime);
	m_effectsManager->Update(elapsedTime);



}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayScene::Render()
{
	// ビュー行列を取得する
	const Matrix& view = m_cameraManager->GetViewMatrix();

	//描画
	m_sky->Render(view, m_projection);
	m_stageObjectManager->Render(view, m_projection);
	m_player->Render(view, m_projection);
	m_enemyManager->Render(view, m_projection);
	m_effectsManager->Render(view, m_projection);
	m_uiManager->Render(view, m_projection);
	m_targetMarker->Render();

	//if (m_stageID == SceneManager::Stage1)
	//{
	//	m_tutorialTex->Render();
	//}

	

}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void PlayScene::Finalize()
{
	// do nothing.
}

//---------------------------------------------------------
// 次のシーンIDを取得する
//---------------------------------------------------------
IScene::SceneID PlayScene::GetNextSceneID() const
{

	if (m_nextScene == IScene::SceneID::NONE)
	{
		return  m_nextScene;
	}

	//フェード中でないなら
	if (m_commonResources->GetFade()->GetFadeState() == Fade::FadeState::None)
	{
		//フェードインを開始
		m_commonResources->GetFade()->StartNormalFadeIn();

	}

	//Noneなら切り替えしない
	return m_nextScene;
}

void PlayScene::CreateStageObject()
{

	std::vector<WataLib::Json::StageData> stageParameters;

	std::unique_ptr<WataLib::Json> json = std::make_unique<WataLib::Json>();

	switch (m_stageID)
	{
		case SceneManager::Stage1:
			stageParameters = json->LoadStageDatas(L"Stage2");
			m_isTutolialTex = true;
			break;
		case SceneManager::Stage2:
			stageParameters = json->LoadStageDatas(L"Stage");
			m_isTutolialTex = false;
			break;
		default:
			break;
	}

	//ステージオブジェックとの生成
	for (auto& parameter : stageParameters)
	{

		if (parameter.ModelName == "Floor")
		{
			auto floor = std::make_unique<Floor>(
				m_commonResources,
				parameter.Scale, parameter.Position,
				Quaternion::CreateFromYawPitchRoll(
					DirectX::XMConvertToRadians(parameter.Rotation.y),
					DirectX::XMConvertToRadians(parameter.Rotation.x),
					DirectX::XMConvertToRadians(parameter.Rotation.z)));

			m_stageObjectManager->AddObject(parameter.ModelName, std::move(floor));

		}
		else if (parameter.ModelName == "Wall")
		{

			auto wall = std::make_unique<Wall>(
				m_commonResources,
				parameter.Scale, parameter.Position,
				Quaternion::CreateFromYawPitchRoll(
					DirectX::XMConvertToRadians(parameter.Rotation.y),
					DirectX::XMConvertToRadians(parameter.Rotation.x),
					DirectX::XMConvertToRadians(parameter.Rotation.z)));

			m_stageObjectManager->AddObject(parameter.ModelName, std::move(wall));

		}
		else if (parameter.ModelName == "BossEnemy" || parameter.ModelName == "BirdEnemy")
		{

			m_enemyManager->AddEnemyData(parameter);

		}

	}
}

void PlayScene::CheckMouseWheel()
{

	const auto& state = m_commonResources->GetInputManager()->GetMouseState();

	int scrollWheelValue = state.scrollWheelValue;

	//上に回転
	if (scrollWheelValue > 0)
	{
		Messenger::GetInstance()->Notify(::GameMessageType::MouseWheelUp, nullptr);
	}
	//下に回転
	else if (scrollWheelValue < 0)
	{

		Messenger::GetInstance()->Notify(::GameMessageType::MouseWheelDown, nullptr);

	}

	Mouse::Get().ResetScrollWheelValue();

}
