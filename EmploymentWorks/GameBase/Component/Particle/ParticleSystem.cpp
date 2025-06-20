//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2025/06/04
// <file>			ParticleSystem.cpp
// <概要>		　　パーティクルのシステム　コンポーネント
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"ParticleSystem.h"
#include "Libraries/MyLib/BinaryFile.h"
#include <random>
#include"GameBase/Scene/Scene.h"
#include"GameBase/Manager/RenderManager.h"
#include "GameBase/Common/Commons.h"
/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="owner"></param>
ParticleSystem::ParticleSystem(Actor* owner)
	:
	Component{owner},
	m_pDR{nullptr},
	m_timer{},
	m_oneLapTime{},
	m_emitTimer{},
	m_isStopping{false}
{
	
	GetActor()->GetScene()->GetRenderMangaer()->AddParticle(this);
	Create();
	Prewarm();
}

/// <summary>
/// デストラクタ
/// </summary>
ParticleSystem::~ParticleSystem()
{
	//GetActor()->GetScene()->GetRenderManager()->RemoveParticle(this);
}

/// <summary>
/// やり直し用
/// </summary>
void ParticleSystem::ReStart()
{
	m_isStopping = false;
	m_particleUtility.clear();
	m_emitTimer = 0;
	m_timer = 0;
	m_oneLapTime = 0;
	Prewarm();
}

/// <summary>
/// 生成関数
/// </summary>
/// <param name="pDR"></param>
void ParticleSystem::Create()
{
	m_pDR = CommonResources::GetInstance()->GetDeviceResources();
	ID3D11Device* device = m_pDR->GetD3DDevice();

	m_particleComputeShader = std::make_unique<ParticleComputeShader>(m_pDR);

	m_spriteInstancing.Initialize(device, m_mainModule.MaxParticles);
	m_spriteInstancing.SetTexture(m_particleComputeShader->GetSRV());
}

void ParticleSystem::InitInstancing()
{
	ID3D11Device* device = m_pDR->GetD3DDevice();
	m_spriteInstancing.Initialize(device, m_mainModule.MaxParticles);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void ParticleSystem::Update(const float& deltaTime)
{
	// ストップ中の処理は早期リターンする
	if (m_isStopping == true) { return; }
	// 全体の時間を計測する
	m_timer += deltaTime;
	// 最初のディレイ時間前なら更新を行わないように早期returnさせる
	if (m_timer <= m_mainModule.DelayTime) { return; }
	// 一周の時間を計測する
	m_oneLapTime += deltaTime;
	// パーティクルの更新
	UpdateParticle(deltaTime);

	if (m_isStopParticle == true) { return; }

	// ループの有無
	if (CheckLoop()) { return; };
	// エミッション管理
	EmissionControl(deltaTime);
	// バースト管理
	BurstControl(deltaTime);

}

/// <summary>
/// パーティクルの更新
/// </summary>
void ParticleSystem::UpdateParticle(float deltaTime)
{
	// いまあるパーティクル分回す
	for (auto ite = m_particleUtility.begin(); ite != m_particleUtility.end();)
	{
		// 個々のアップデートでfalseが返された場合は中身を消す
		if (!ite->Update(deltaTime)){ite = m_particleUtility.erase(ite);}
		// それ以外は、次のパーティクルの一つへ進む
		else{	ite++;	}
	}
}

/// <summary>
/// ループの有無
/// </summary>
/// <returns></returns>
bool ParticleSystem::CheckLoop()
{
	// Durationを超えた場合に、停止するのか、ループするのか
	if (m_oneLapTime >= m_mainModule.Duration)
	{
		// ループしないなら返す		// 描画もしない
		if (!m_mainModule.Looping) { return true; }
		// もう一度Duration計算
		m_oneLapTime = 0.0f;
		for (auto& bursts : m_emission.m_bursts)
		{
			bursts.IsFired = false;
		}
	}
	return false;
}

/// <summary>
/// エミッション管理
/// </summary>
void ParticleSystem::EmissionControl(float deltaTime)
{
	// 一秒間に0回以下出すばあいはないので、早期リターン
	if (m_emission.RateOverTime <= 0) { return; }
	// 1秒間に何個だすのか、一個ごとの間隔
	float emissionInterval = 1.0f / m_emission.RateOverTime;
	m_emitTimer += deltaTime;
	// エミットのカウント
	int emitCount = 0;
	// パーティクルの維持
	while (m_emitTimer >= emissionInterval && m_particleUtility.size() < m_mainModule.MaxParticles)
	{
		// パーティクルの追加
		m_particleUtility.push_back(CreateNewParticle());
		m_emitTimer -= emissionInterval;
		emitCount++;
	}

}

/// <summary>
/// バースト管理
/// </summary>
void ParticleSystem::BurstControl(float deltaTime)
{
	// そもそもバーストの数が0以下なら返す
	if (m_emission.m_bursts.size() <= 0) { return; }
	// 一個前のフレームを求める
	float prevLapTime = m_oneLapTime - deltaTime;
	// バーストが追加された分だけ回す
	for (auto& bursts : m_emission.m_bursts)
	{
		// サイクルが-1でないかつ、設定していた場合のサイクルカウントを上回っているときは処理しない
		if (bursts.Cycles != -1 && bursts.CycleCount >= bursts.Cycles) { continue; }
		// バーストさせる時間が、前のフレームと、今のフレームの間にある場合かつ、まだ使用していない場合
		if (prevLapTime <= bursts.Time && bursts.Time <= m_oneLapTime && bursts.IsFired == false)
		{
			// そのバーストのカウント分回す
			for (int i = 0; i < bursts.Count; i++)
			{
				m_particleUtility.push_back(CreateNewParticle());
			}
			// バーストの終了判定をtrueにする
			bursts.IsFired = true;
			bursts.CycleCount += 1;
		}
	}
}

/// <summary>
/// 初期操作スキップ用（フレーム飛ばし）
/// </summary>
void ParticleSystem::Prewarm()
{
	if (!m_mainModule.Prewarm) return;

	const float duration = m_mainModule.Duration;
	const float step = 1.0f / 60.0f; // 60FPS 相当でスキップ実行

	m_timer = 0.0f;
	m_oneLapTime = 0.0f;
	m_emitTimer = 0.0f;
	m_particleUtility.clear();

	for (float t = 0.0f; t < duration; t += step)
	{
		Update(step);
	}

	// 時間をDurationにリセットしておく（ループさせないため）
	m_oneLapTime = duration;
}

/// <summary>
/// 描画処理
/// </summary>
void ParticleSystem::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	m_particleComputeShader->CalculateImage();
	m_spriteInstances.clear();

	for (auto& p : m_particleUtility)
	{
		SpriteInstancing::SpriteInstanceData data{};
		data.position = p.GetPosition();
		data.size = p.GetNowScale(); 
		data.color = p.GetNowColor();
		data.texCoord = DirectX::SimpleMath::Vector4(0, 0, 1, 1); // 今回使わない
		data.rotation = p.GetNowRotate();

		if (m_mainModule.SimulationSpaceType == SimulationSpaceType::Local)
		{
			data.position += GetActor()->GetTransform()->GetWorldPosition();
		}
		m_spriteInstances.push_back(data);
	}

	if (!m_spriteInstances.empty())
	{
	
		m_spriteInstancing.Render(
			m_pDR->GetD3DDeviceContext(),
			CommonResources::GetInstance()->GetCommonStates(),
			view,
			proj,
			m_spriteInstances);
	
	}

}

/// <summary>
/// 新規パーティクルを作成する
/// </summary>
ParticleUtility ParticleSystem::CreateNewParticle()
{
	
	// 位置をVector3型に代入
	// 所属アクターの、Transformの位置に応じた場所から出すようにする
	DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3::Zero;

	if (m_mainModule.SimulationSpaceType == SimulationSpaceType::World)
	{
		position = GetActor()->GetTransform()->GetWorldPosition();
	}
	
	auto velocity = DirectX::SimpleMath::Vector3::Zero;
	if (m_shape.Shape)
	{
		m_shape.Shape->Generate();

		position += m_shape.Shape->GetPosition();
		velocity += m_shape.Shape->GetVelocity();
	}
	// 設定されたUtilityとして返すために設定
	ParticleUtility particle = ParticleUtility(
		m_mainModule.LifeTime.Get(),
		position,
		velocity * m_mainModule.StartSpeed.Get(),
		m_mainModule.Gravity.Get(),
		m_mainModule.MinSize.Get(),
		m_mainModule.MaxSize.Get(),
		m_mainModule.StartRotate.Get(),
		m_mainModule.EndRotate.Get(),
		m_mainModule.StartColor.Get(),
		m_mainModule.EndColor.Get());

	particle.SetAddForce(m_addForceSpeed.ForcePower.Get());
	particle.SetEasing(m_easing.SizeEasing);
	return particle;

}
