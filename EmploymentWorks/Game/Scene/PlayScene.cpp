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

#include "Libraries/MyLib/Camera/GameCameraManager.h"
#include "Game/Object/Player/Player.h"
#include "Game/Object/Enemy/Enemy.h"
#include "Game/Object/Floor.h"
#include "Game/LockOn.h"
#include "Game/DetectionCollision/CollisionManager.h"
#include "Game/Object/Wall.h"
#include "Game/EnemyHP.h"
#include "Game/Object/Rock.h"
#include "Game/Object/Sky.h"
#include "Game/UI.h"

#include <cassert>

const int WALLSIZE = 4;
const float WALLHEITH = 2;


//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
PlayScene::PlayScene()
	:
	m_commonResources{},
	//m_debugCamera{},
	m_gridFloor{},
	m_projection{},
	m_player{},
	m_enemy{},
	m_cameraManager{},
	m_floor{}
	, m_lockOn{}
	, m_rock{}
	, m_sky{}
	, m_nextScene{ SceneID::NONE }
	,m_state{}
{
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
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	assert(resources);
	m_commonResources = resources;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();

	m_nextScene = SceneID::NONE;

	// グリッド床を作成する
	m_gridFloor = std::make_unique<mylib::GridFloor>(device, context, states);

	// デバッグカメラを作成する
	RECT rect{ m_commonResources->GetDeviceResources()->GetOutputSize() };
	//m_debugCamera = std::make_unique<mylib::DebugCamera>();
	//m_debugCamera->Initialize(rect.right, rect.bottom);



	// 射影行列を作成する
	m_projection = SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		XMConvertToRadians(45.0f),
		static_cast<float>(rect.right) / static_cast<float>(rect.bottom),
		0.1f, 1000.0f
	);



	m_floor = std::make_unique<Floor>();
	m_enemy = std::make_unique<Enemy>();
	m_player = std::make_unique<Player>();
	m_cameraManager = std::make_unique<mylib::GameCameraManager>();
	m_wall = std::make_unique<Wall>();
	m_lockOn = std::make_unique<LockOn>();
	m_collisionManager = std::make_unique<CollisionManager>();
	m_ui = std::make_unique<UI>();
	//石　岩
	auto rock = std::make_unique<Rock>();
	rock->Initialize(m_commonResources, Vector3(15, 0, 0), Vector3(3.8, 3.5f, 2.5f), 2);
	m_rock.emplace_back(std::move(rock));

	rock = std::make_unique<Rock>();
	rock->Initialize(m_commonResources, Vector3(-15, 0, 0), Vector3(3.8, 3.5f, 2.5f), 2);
	m_rock.emplace_back(std::move(rock));

	//各クラスに必要なクラスのインスタンス
	m_player->Instances();
	m_enemy->Instances();
	m_cameraManager->Instances();



	//各クラスの情報を登録とインスタンス
	m_player->RegistrationInformation(m_enemy.get(), m_cameraManager->GetTPSCamera());
	m_enemy->RegistrationInformation(m_player.get());
	m_cameraManager->RegistrationInformation(this, m_player.get(), m_enemy.get());
	m_lockOn->RegistrationInformationAndInstances(m_player.get(), m_enemy.get(), m_cameraManager.get());
	m_ui->RegistrationInformationAndInstances(this, m_player.get(), m_enemy.get());


	m_floor->Initialize(m_commonResources, Vector3::Zero, Vector3(36, 0.2f, 36), 8.0f);
	m_player->Initialize(m_commonResources, Vector3(0, 3.75f, 10));
	m_enemy->Initialize(m_commonResources, Vector3(0, 5.75f, -10));
	//Wallクラスは当たり判定を持っているだけモデルの描画はない
	m_wall->Initialize(m_commonResources,Vector3::Zero, 36.0f);
	m_cameraManager->Initialize();
	m_lockOn->Initialize(m_commonResources->GetDeviceResources(),
		m_commonResources->GetDeviceResources()->GetOutputSize().right,
		m_commonResources->GetDeviceResources()->GetOutputSize().bottom);
	m_collisionManager->Initialize(m_commonResources, m_player.get(), m_enemy.get());
	m_ui->Initialize(m_commonResources,
		m_commonResources->GetDeviceResources()->GetOutputSize().right,
		m_commonResources->GetDeviceResources()->GetOutputSize().bottom);




	m_collisionManager->SetTPS_Camera(m_cameraManager->GetTPSCamera());





	///当たり判定をManagerに追加
	m_player->RegistrationCollionManager(m_collisionManager.get());
	m_enemy->RegistrationCollionManager(m_collisionManager.get());
	m_floor->RegistrationCollionManager(m_collisionManager.get());

	m_wall->RegistrationCollionManager(m_collisionManager.get());

	m_rock[0]->RegistrationCollionManager(m_collisionManager.get());
	m_rock[1]->RegistrationCollionManager(m_collisionManager.get());


	//Rayとの当たり判定を取るためにBoundingの登録
	m_commonResources->GetJudgement()->SetBounding(m_rock[0]->GetBounding());
	m_commonResources->GetJudgement()->SetBounding(m_rock[1]->GetBounding());


	m_sky = std::make_unique<Sky>();
	m_sky->Initialize(m_commonResources);

	m_state = GameState::None;
	//m_state = GameState::GameOver;
}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayScene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	m_cameraManager->Update(elapsedTime);


	m_player->Update(elapsedTime, m_cameraManager->GetTPSCamera()->GetRotationX());

	switch (m_state)
	{
		case PlayScene::GameState::None:


			if (m_cameraManager->GetGameCameraState() != m_cameraManager->GetGameStartCamera())
			{
				m_enemy->Update(elapsedTime);
			}


			//ゲームクリア時に１度だけ呼びたい
			if (m_enemy->GetHp() <= 0)
			{
				//カメラの切り替え
				m_cameraManager->ChangeState(m_cameraManager->GetGameEndCamera());
				//ゲーム状態をクリアに変更
				m_state = GameState::Clear;
			}

			//ゲームオーバーに変更
			if (m_player->GetPlayerHP() <= 0)
			{
				m_state = GameState::GameOver;
			}

			m_lockOn->Update(elapsedTime);


			m_ui->Update(elapsedTime);

			break;
		case PlayScene::GameState::Clear:

			//TPSカメラになってゲームが通常状態の時
			if (m_cameraManager->GetGameCameraState() != m_cameraManager->GetGameStartCamera())
			{
				m_enemy->ReduceSize(elapsedTime);
			}

			//敵を倒したときのアニメーションが終わったら
			if (m_enemy->GetScale() <= 0)
			{
				m_ui->GameClearUpdate(elapsedTime);
			}

			if (m_ui->GetIsChangeResultScene())
			{

				SetNextSceneID(SceneID::RESULT);
			}



			break;
		case PlayScene::GameState::GameOver:

			m_ui->GameOverUpdate(elapsedTime);

			break;
		default:
			break;
	}

	m_collisionManager->Update();


	m_commonResources->GetTimer()->Update(elapsedTime);

	m_player->SetisLockOn(m_lockOn->GetIsLOckOn());
}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayScene::Render()
{
	using namespace DirectX::SimpleMath;


	// ビュー行列を取得する
	const Matrix& view = m_cameraManager->GetViewMatrix();;


	m_floor->Render(view, m_projection);

	m_wall->Render(view, m_projection);


	m_enemy->Render(view, m_projection);


	for (auto& rock : m_rock)
	{
		rock->Render(view, m_projection);
	}

	m_sky->Render(view, m_projection);

	m_ui->Render();

	switch (m_state)
	{
		case PlayScene::GameState::None:
			m_lockOn->Render();

			break;
		case PlayScene::GameState::Clear:
			m_ui->ClearTexRender();
			break;
		case PlayScene::GameState::GameOver:
			m_ui->GameOverRender();
			break;
		default:
			break;
	}

	m_player->Render(view, m_projection);


	m_commonResources->GetTimer()->PlaySceneRender(Vector2(100, 50), 0.3f);

	//// デバッグ情報を「DebugString」で表示する
	auto debugString = m_commonResources->GetDebugString();
	//debugString->AddString("Play Scene");
	//debugString->AddString("direction: %f, %f,%f", m_enemy->Getforward().x, m_enemy->Getforward().y, m_enemy->Getforward().z);
	debugString->AddString("EyePos: %f, %f,%f", m_cameraManager->GetTPSCamera()->GetEyePosition().x, m_cameraManager->GetTPSCamera()->GetEyePosition().y, m_cameraManager->GetTPSCamera()->GetEyePosition().z);

	//debugString->AddString("Pos: %f, %f", m_player->GetPos().x, m_player->GetPos().z);
	//debugString->AddString("Pos: %f, %f", m_enemy->GetPos().x, m_enemy->GetPos().z);
	//debugString->AddString("IsLockOn: %d ", m_lockOn->GetIsLOckOn());
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

	//Noneなら切り替えしない
	return m_nextScene;

}



