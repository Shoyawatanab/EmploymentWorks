//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto	
// <製作開始日>		2025/06/04
// <file>			ParticleSystem.h
// <概要>		　　パーティクルのシステム　コンポーネント 
// <Version>		Ver1.0.0	仮組み立て完成　Mainモジュールのみ
//					Ver1.0.1	Emissionと、Sphereのサブモジュール完成
//					Ver1.0.2	Easingの概念を追加、次Ver2予定(リファクタリング)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"GameBase/Component/Components.h"
#include"GameBase/Component/Particle/ParticleUtility.h"
#include"Shape/Shapes.h"
#include"Shape/ShapeBase.h"
#include "Libraries/Easing.h"
#include"Instancing/SpriteInstancing.h"
#include"ValueWrapper.h"
#include"Compute/ParticleComputeShader.h"

class ParticleSystem : public Component
{
public:
	// ワールド座標でやるか、ローカル座標でやるか
	// ワールドだと、パーティクルの追従はしてこない。ローカルだと、パーティクルも追従してくるようになる
	enum class SimulationSpaceType
	{
		Local = 0,
		World = 1
	};
	// パーティクルのメインモジュール設定
	struct MainModule
	{
		// ループ一周の時間
		float Duration = 5.0f;
		// ループさせるかどうか true == する : false == しない
		bool Looping = true;
		// 最初のディレイ時間
		float DelayTime = 0.0f;
		// スキップされた状態で始まる true == する false == しない
		bool Prewarm = false;
		// 初期速度
		ValueWrapper<float> StartSpeed = 1.0f;
		// 生き残る時間の最小値、最大値
		ValueWrapper<float> LifeTime = { 5.0f,5.0f };
		// 速度
		DirectX::SimpleMath::Vector3 Velocity = { 0.0f,0.0f,0.0f };
		// 大きさの最小値
		ValueWrapper<DirectX::SimpleMath::Vector3> MinSize = { DirectX::SimpleMath::Vector3(1.0f,1.0f,1.0f) };
		// 大きさの最大値
		ValueWrapper<DirectX::SimpleMath::Vector3> MaxSize = { DirectX::SimpleMath::Vector3(1.0f,1.0f,1.0f)};
		// 初期回転
		ValueWrapper<DirectX::SimpleMath::Quaternion> StartRotate = { DirectX::SimpleMath::Quaternion(0.0f,0.0f,0.0f,1.0f) };
		// 最終回転
		ValueWrapper<DirectX::SimpleMath::Quaternion> EndRotate = { DirectX::SimpleMath::Quaternion(0.0f,0.0f,0.0f,1.0f) };
		// 重力
		ValueWrapper<DirectX::SimpleMath::Vector3> Gravity = { DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f) };
		// 初期の色
		ValueWrapper<DirectX::SimpleMath::Color> StartColor = { DirectX::SimpleMath::Quaternion(0.0f, 0.0f, 0.0f, 1.0f) };
		// 最終の色
		ValueWrapper<DirectX::SimpleMath::Color> EndColor = { DirectX::SimpleMath::Quaternion(1.0f, 1.0f, 1.0f, 0.0f) };
		// パーティクルを出す数の最大値
		int MaxParticles = 100;
		// 動きをローカルにするかワールドにするか
		SimulationSpaceType SimulationSpaceType = SimulationSpaceType::Local;
	};

	// バーストさせる
	struct Burst
	{
		// 発生させる時刻
		float Time = 0;
		// 一度に出すパーティクルの数
		int Count = 10;
		// すでに発生したかどうか
		bool IsFired = false;
		// 何回繰り返すか( -1でパーティクルがある限り無限)
		int Cycles = -1;
		// 現在の繰り返し回数保存用
		int CycleCount = 0;
	};

	// パーティクルの発生方法
	struct EmissionModule
	{
		// 秒間のパーティクル発生数
		int RateOverTime = 10;
		// バーストさせる
		std::vector<Burst> m_bursts;
	};


	// パーティクルの発射形状などの設定
	struct ShapeModule
	{
		// ビルボードの有無 true == あり ：false == なし
		bool IsBillboard = true;
		// パーティクルの形決定
		std::shared_ptr<ShapeBase> Shape = std::make_shared<ShapeCone>(1.0f ,25.0f ,DirectX::SimpleMath::Vector3(0,1,0));
	};

	// イージングで大きさ、色を変更させる
	struct EasingOverLifeTime
	{
		NakashiLib::Easing::EasingType SizeEasing = NakashiLib::Easing::EasingType::InSine;
		NakashiLib::Easing::EasingType ColorEasing = NakashiLib::Easing::EasingType::InSine;
	};

	// 時間に応じて速度加算
	struct ForceOverLifeTimeSpeed
	{
		ValueWrapper<DirectX::SimpleMath::Vector3> ForcePower = DirectX::SimpleMath::Vector3::Zero;
	};

	// インスタンスバッファ構造を定義
	struct ParticleInstanceData
	{
		DirectX::SimpleMath::Matrix Transform;
		DirectX::SimpleMath::Color Color;
	};

public:
	// コンストラクタ、デストラクタ
	ParticleSystem(Actor* owner);
	~ParticleSystem();
	
	// 更新処理
	void Update(const float& deltaTime) override;
	// 描画処理
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);

	// やり直し用関数
	void ReStart();
	// 止める用関数
	void Stop() { m_isStopping = true; }
	// 止めたところから開始
	void Play() { m_isStopping = false;}
	// パーティクルの生成のみとめる
	void StopParticle() { m_isStopParticle = true; }
	// パーティクルの生成を開始
	void PlayParticle() { m_isStopParticle = false; }

	// メソッドチェーンで読み込むようにする+++++++++++++++++++++++++++++++
	// テクスチャ読み込み
	ParticleSystem* SetTexture(ID3D11ShaderResourceView* texture) { m_spriteInstancing.SetTexture(texture); return this; }
	// 設定の変更												// メインモジュールの変更と同時に、インスタンシングの最大パーティクルも変わるため、変更をする
	ParticleSystem* SetMainModule(const MainModule& setting) { m_mainModule = setting; InitInstancing(); Prewarm(); return this; }
	// エミッターの設定
	ParticleSystem* SetEmission(const EmissionModule& emission) { m_emission = emission; return this; }
	// バーストの設定
	ParticleSystem* AddBurst(float time, int count) { m_emission.m_bursts.push_back({ time , count , false , -1 , 0 }); return this; }
	// 細かいバーストの設定をした追加
	ParticleSystem* AddBurst(const Burst& burst) { m_emission.m_bursts.push_back(burst); return this; }
	// 形の設定
	ParticleSystem* SetShape(std::shared_ptr<ShapeBase> shape) { m_shape.Shape = shape; return this; }
	// ビルボードの有無
	ParticleSystem* SetBillboardEnabled(bool enabled) { m_shape.IsBillboard = enabled; m_spriteInstancing.SetBillboard(m_shape.IsBillboard); return this; }
	// 追加の速度の設定
	ParticleSystem* SetForce(ForceOverLifeTimeSpeed addVelocity) { m_addForceSpeed = addVelocity; return this; }
	// イージングによる変更の設定
	ParticleSystem* SetEasing(const EasingOverLifeTime& easing) { m_easing = easing; return this; }
private:
	// パーティクルの作成
	ParticleUtility CreateNewParticle();
	// 作成する
	void Create();
	// インスタンシング用初期化
	void InitInstancing();

	// パーティクルの更新
	void UpdateParticle(float deltaTime);
	// ループ有無
	bool CheckLoop();
	// エミッター計算
	void EmissionControl(float deltaTime);
	// バースト計算
	void BurstControl(float deltaTime);

	// プリウォームするかどうか用
	void Prewarm();
private:// 変数
	// デバイスリソース
	DX::DeviceResources* m_pDR;

	std::unique_ptr<ParticleComputeShader> m_particleComputeShader;

	std::list<ParticleUtility> m_particleUtility;
	// パーティクルの情報
	MainModule m_mainModule;
	// エミッターの情報
	EmissionModule m_emission;
	// 形の情報
	ShapeModule m_shape;
	// 追加の速度
	ForceOverLifeTimeSpeed m_addForceSpeed;
	// イージング
	EasingOverLifeTime m_easing;

	// 時間
	float m_timer;
	// 一周の時間計測用
	float m_oneLapTime;
	// パーティクルを出すための時間計測
	float m_emitTimer;

	// 止め有無 true == 止まっている false == 止まっていない
	bool m_isStopping;

	bool m_isStopParticle;

	// インスタンシング
	SpriteInstancing m_spriteInstancing;
	std::vector<SpriteInstancing::SpriteInstanceData> m_spriteInstances;
};