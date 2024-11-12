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
#include "Game/UI/UI.h"
#include "Game/Object/Ceiling.h"
#include "Game/Object/Pillar.h"
#include "Game/Object/Gimmick/Artillery/Artillery.h"
#include "Libraries/MyLib/LoadJson.h"
#include "Libraries/MyLib/Particle.h"
#include "Game/Observer/Messenger.h"
#include "Libraries/MyLib/Texture.h"

#include <functional>
#include <cassert>

const int WALLSIZE = 4;
const float WALLHEITH = 2;

//イベント名
const std::string SLOWMOTION = "SlowMotion";

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
	,m_ceiling{}
	,m_loadJson{}
{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
PlayScene::~PlayScene()
{
	// do nothing.

		// オーディオエンジンの後始末
	m_soundEffectInstanceBGM->Stop(true);
	if (m_audioEngine)
	{
		m_audioEngine->Suspend();
	}

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
		else if(parameter.ModelName == "Floor.cmo")
		{
			//床	 
			m_floor = std::make_unique<Floor>();
			m_floor->Initialize(m_commonResources, parameter.Position, parameter.Scale, parameter.Rotation,parameter.BoundingSphereRadius);

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
			artillery->Initialize(m_commonResources,this, parameter.Position, parameter.Scale, parameter.Rotation, parameter.BoundingSphereRadius);
			m_artillery.push_back(std::move(artillery));

		}
	}
	
	DirectX::SimpleMath::Quaternion rotation = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0), 0, DirectX::XMConvertToRadians(0));

	float scale = 1.0f;

	m_enemy = std::make_unique<Enemy>(m_commonResources,nullptr,  DirectX::SimpleMath::Vector3(scale, scale, scale), Vector3(0, 4, 0), rotation);
	m_player = std::make_unique<Player>(m_commonResources,nullptr, Vector3(0.2,0.2,0.2), Vector3(0, 0.75f, 15), 
		Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(180), DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(0)));
	m_cameraManager = std::make_unique<mylib::GameCameraManager>();

	m_lockOn = std::make_unique<LockOn>();
	m_collisionManager = std::make_unique<CollisionManager>();
	m_ui = std::make_unique<UI>();

	//各クラスに必要なクラスのインスタンス
	m_player->Instances();
	m_enemy->Instances();
	m_cameraManager->Instances();
	m_ui->Instances();
	
	//各クラスの情報を登録とインスタンス
	m_player->RegistrationInformation(m_enemy.get(),m_cameraManager->GetTPSCamera(),this);
	m_enemy->RegistrationInformation(m_player.get());
	m_cameraManager->RegistrationInformation(this, m_player.get(), m_enemy.get());
	m_lockOn->RegistrationInformation(m_player.get(), m_enemy.get(), m_cameraManager.get());
	m_ui->RegistrationInformation(this, m_player.get(), m_enemy.get());


	m_player->Initialize();
	m_enemy->Initialize();

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

	for (auto& wall : m_wall)
	{
		wall->RegistrationCollionManager(m_collisionManager.get());
	}

	for (auto& artillery : m_artillery)
	{
		artillery->RegistrationCollionManager(m_collisionManager.get());
	}

	for (auto& pillar : m_pillar)
	{
		pillar->RegistrationCollionManager(m_collisionManager.get());
	}

	//m_rock[0]->RegistrationCollionManager(m_collisionManager.get());
	//m_rock[1]->RegistrationCollionManager(m_collisionManager.get());


	//Rayとの当たり判定を取るためにBoundingの登録
	//m_commonResources->GetJudgement()->SetBounding(m_rock[0]->GetBounding());
	//m_commonResources->GetJudgement()->SetBounding(m_rock[1]->GetBounding());


	m_sky = std::make_unique<Sky>();
	m_sky->Initialize(m_commonResources);

	//決めた数だけ爆発エフェクトを生成しておく
	for (int i = 0; i < 10; i++)
	{
		auto particle = std::make_unique<Particle>();
		particle->Initialize(m_commonResources);
		m_particle.push_back(std::move(particle));
	}


	m_state = GameState::None;

	m_commonResources->GetTimer()->TimeReset();

		// オーディオエンジンのフラグ
	AUDIO_ENGINE_FLAGS eflags = AudioEngine_Default;
#ifdef _DEBUG
	eflags |= AudioEngine_Debug;
#endif

	// オーディオエンジンを作成する
	m_audioEngine = std::make_unique<AudioEngine>(eflags);

	// サウンドエフェクトBGMをロードする
	m_soundEffectBGM = std::make_unique<SoundEffect>(
		m_audioEngine.get(), L"Resources/Sounds/maou_game_dangeon08.wav");

	// サウンドエフェクトBGMをインスタンス化する
	m_soundEffectInstanceBGM = m_soundEffectBGM->CreateInstance();
	// BGMのループ再生
	m_soundEffectInstanceBGM->Play(true);

	m_startCountDown = 0;

	m_slowMotionSpeed = 1.0f;
	m_slowMotionTime = 0;
	m_isSlowMotion = false;

	//イベントの登録 プレイシーンの最後で行う
	//スロー演出の開始イベント
 	Messenger::Attach(Messenger::SLOWMOTION, std::bind(&PlayScene::BoomerangSlowMotion,this));
	//スロー演出の終了イベント
	Messenger::Attach(Messenger::SLOWMOTIONEND, std::bind(&PlayScene::BoomerangSlowMotionEnd, this));

	m_slowTexture = std::make_unique<mylib::Texture>();
	m_slowTexture->Initialize(m_commonResources, L"Resources/Textures/SlowMotionTex.png", Vector2(640, 360), 1.0f);

}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void PlayScene::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);


	if (m_startCountDown < 0.5f)
	{
		m_startCountDown += elapsedTime;
		return;
	}

	//イベントの更新
	for (auto& ecent : m_eventUpdate)
	{
		ecent.second(elapsedTime);
	}

	//イベント名があればイベント関数から削除する
	m_deleteEventName.erase(
		std::remove_if(m_deleteEventName.begin(), m_deleteEventName.end(),
			[this](const auto& name) 
			{
				//nameを削除する
				m_eventUpdate.erase(name);
				//ture : nameを削除対象にする
				return true;
			}
		),
		m_deleteEventName.end()
	);



	m_cameraManager->Update(elapsedTime);

	//スロー演出の速度をかける
	elapsedTime *= m_slowMotionSpeed;


	switch (m_state)
	{
		case PlayScene::GameState::None:


			if (m_cameraManager->GetGameCameraState() != m_cameraManager->GetGameStartCamera())
			{
				m_enemy->Update(elapsedTime);
				for (auto& artillery : m_artillery)
				{
					artillery->Update(elapsedTime);
				}
			}


			//ゲームクリア時に１度だけ呼びたい
			if (m_enemy->GetHp() <= 0)
			{
				//カメラの切り替え
				m_cameraManager->ChangeState(m_cameraManager->GetGameEndCamera());
				//ゲーム状態をクリアに変更
				m_state = GameState::Clear;
				m_enemy->SetAnimation("FallDown");
			}

			//ゲームオーバーに変更
			if (m_player->GetPlayerHP() <= 0)
			{
				m_state = GameState::GameOver;
			}

			m_lockOn->Update(elapsedTime);



			m_commonResources->GetTimer()->Update(elapsedTime);


			break;
		case PlayScene::GameState::Clear:

			//TPSカメラになってゲームが通常状態の時
			if (m_cameraManager->GetGameCameraState() != m_cameraManager->GetGameStartCamera())
			{
				
				if (m_enemy->FallDwonAnimation(elapsedTime) == Animation::AnimationState::End && m_ui->GetCurrentUIState() != m_ui->GetGameClearUI())
				{
					m_ui->ChangeState(m_ui->GetGameClearUI());
				}
			
			}


			break;
		case PlayScene::GameState::GameOver:

			if (m_ui->GetCurrentUIState() != m_ui->GetGameOverUI())
			{
				m_ui->ChangeState(m_ui->GetGameOverUI());
			}

			break;
		default:
			break;
	}



	m_player->Update(elapsedTime);



	m_ui->Update(elapsedTime);

	m_collisionManager->Update();

	for (auto& particle : m_particle)
	{
		if (particle->GetState() == Particle::State::Using)
		{
			particle->Update(elapsedTime);
		}
	}


	m_player->SetisLockOn(m_lockOn->GetIsLOckOn());

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void PlayScene::Render()
{
	using namespace DirectX::SimpleMath;


	// ビュー行列を取得する
	const Matrix& view = m_cameraManager->GetViewMatrix();


	m_floor->Render(view, m_projection);

	for (auto& wall : m_wall)
	{
		wall->Render(view, m_projection);
	}

	for (auto& pillar : m_pillar)
	{
		pillar->Render(view, m_projection);
	}

	//m_ceiling->Render(m_view, m_projection);

	m_enemy->Render(view, m_projection);


	m_sky->Render(view, m_projection);

	for (auto& artillery : m_artillery)
	{
		artillery->Render(view, m_projection);
	}


	if (m_state == GameState::None)
	{
		m_player->Render(view, m_projection);
		m_lockOn->Render();
	}


	for (auto& particle : m_particle)
	{
		if (particle->GetState() == Particle::State::Using)
		{
			particle->Render(view, m_projection);
		}
	}

	if (m_isSlowMotion)
	{
		m_slowTexture->Render();
		m_ui->GetGamePlayUI()->BoomerangMakerRender();

	}

	m_ui->Render();

	m_commonResources->GetTimer()->PlaySceneRender(Vector2(100, 50), 0.3f);

#ifdef _DEBUG

	//// デバッグ情報を「DebugString」で表示する
	auto debugString = m_commonResources->GetDebugString();
	//debugString->AddString("Play Scene");
	debugString->AddString("PlayerPos: %f, %f,%f", m_player->GetPosition().x, m_player->GetPosition().y, m_player->GetPosition().z);
	//debugString->AddString("EyePos: %f, %f,%f", m_cameraManager->GetTPSCamera()->GetEyePosition().x, m_cameraManager->GetTPSCamera()->GetEyePosition().y, m_cameraManager->GetTPSCamera()->GetEyePosition().z);
	//debugString->AddString("Pos: %f, %f", m_player->GetPos().x, m_player->GetPos().z);
	//debugString->AddString("Pos: %f, %f", m_enemy->GetPos().x, m_enemy->GetPos().z);
	//debugString->AddString("IsLockOn: %d ", m_lockOn->GetIsLOckOn());
#endif

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

//爆発エフェクトを生成する
void PlayScene::CreateParticle(DirectX::SimpleMath::Vector3 Pos)
{
	//Bulletで生成している

	for (auto& particle : m_particle)
	{
		//使用していなければ
		if (particle->GetState() == Particle::State::None)
		{
			particle->Create(Pos);
			break;
		}


	}

}



//　ブーメランを投げるときのスロー演出
void PlayScene::BoomerangSlowMotion()
{
	//スロー演出の時間の
	m_slowMotionSpeed = 0.3f;

	//スロー演出の最大時間
	m_slowMotionMaxTime = 3.0f;
	
	m_isSlowMotion = true;

	m_slowMotionTime = 0;

	//進行割合の初期化
	m_progressRate = 0.0f;


	//スロー演出のUpdateの追加
	m_eventUpdate[SLOWMOTION] = std::function<void(float)>(std::bind(&PlayScene::SlowMotion, this, std::placeholders::_1));

}

void PlayScene::BoomerangSlowMotionEnd()
{

	//名前を削除に登録
	m_deleteEventName.push_back(SLOWMOTION);

	//時間の初期化
	m_slowMotionTime = 0;

	m_isSlowMotion = false;

	//進行割合を最大に
	m_progressRate = 1.0f;

	//スロースピードの初期化
	m_slowMotionSpeed = 1.0f;

	m_progressRate = 0.0f;
}

void PlayScene::SlowMotion(float elapsdTime)
{

	m_ui->GetGamePlayUI()->BoomerangMakerUpdate();


	if (m_slowMotionTime >= m_slowMotionMaxTime)
	{
		//名前を削除に登録
		m_deleteEventName.push_back(SLOWMOTION);

		//時間の初期化
		m_slowMotionTime = 0;

		m_isSlowMotion = false;

		//進行割合を最大に
		m_progressRate = 1.0f;

		//スロースピードの初期化
		m_slowMotionSpeed = 1.0f;

		m_progressRate = 0.0f;

		if (m_player->GetUsingBoomerang()->GetBoomerangState() == m_player->GetUsingBoomerang()->GetBoomerangGetReady())
		{
			
			m_player->GetUsingBoomerang()->ChangeState(m_player->GetUsingBoomerang()->GetBoomerangThrow());
			m_player->ChangeState(m_player->GetPlayerIding());
		}






		return;
	}

	m_slowMotionTime += elapsdTime;

	//進行割合を求める
	m_progressRate = m_slowMotionTime / m_slowMotionMaxTime;

}




