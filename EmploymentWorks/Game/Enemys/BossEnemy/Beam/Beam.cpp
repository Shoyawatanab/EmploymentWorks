/*
	@file	Beam.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "Beam.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Enemys/BossEnemy/Beam/BeamRays.h"
#include "Game/Enemys/BossEnemy/Beam/BeamEnergyBall.h"
#include "Game/Enemys/BossEnemy/Beam/BeamChargeEffect.h"
#include "Game/CollisiionManager.h"
#include "Game/Params.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;




/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
Beam::Beam(CommonResources* resources)
	:
	BaseEntity(resources,Params::BOSSENEMY_BEAM_SCALE,Params::BOSSENEMY_BEAM_POSITION,Params::BOSSENEMY_BEAM_ROTATION)
	,m_initialScale{}
	,m_energyBall{}
	,m_preliminaryActitonTime{}
	,m_chargeEffect{}
	,m_deleteChargeEffect{}
	,m_rays{}
	
{
	m_energyBall = std::make_unique<BeamEnergyBall>(resources,this);
	m_rays = std::make_unique<BeamRays>(resources,this);

}

/// <summary>
/// デストラクタ
/// </summary>
Beam::~Beam()
{
	// do nothing.
}

/// <summary>
/// 初期化
/// </summary>
void Beam::Initialize()
{


	m_energyBall->Initialize();
	m_rays->Initialize();




	
}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void Beam::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	BaseEntity::Render(view, projection);


	m_energyBall->Render(view, projection);
	for (auto& partcle : m_chargeEffect)
	{
		partcle->Render(view, projection);
	}
	m_rays->Render(view, projection);




}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void Beam::Update(const float& elapsedTime)
{




	for (auto& effect : m_deleteChargeEffect)
	{
		m_chargeEffect.erase(
			std::remove_if(
				m_chargeEffect.begin(), m_chargeEffect.end(),
				[&effect](const std::unique_ptr<BeamChargeEffect>& particle) {
					return particle.get() == effect; // 一致するかを判定
				}
			),
			m_chargeEffect.end()
		);
	}

	m_deleteChargeEffect.clear();


}


/// <summary>
/// 必要なポインタの追加
/// </summary>
/// <param name="bossEnemy">ボス敵</param>
/// <param name="player">プレイヤ</param>
void Beam::AddPointer(BossEnemy* bossEnemy, Player* player)

{
	m_energyBall->AddPointer(this);
	m_rays->AddPointer(this);

}

/// <summary>
/// 当たり判定に追加
/// </summary>
/// <param name="collsionManager">当たり判定クラス</param>
void Beam::AddCollionManager(CollisionManager* collsionManager)
{
	m_energyBall->AddCollision(collsionManager);
}

/// <summary>
/// パーティクルを生成
/// </summary>
void Beam::CreateParticle()
{

	std::vector<Vector3> position;
	std::vector<Quaternion> rotate;


	float radius = 0.9f;

	for (int angle = 0; angle < 360; angle += 45)
	{
		// 角度をラジアンに変換   スタートを上から始めるために９０度プラスする　９０足さないと右から始まる
		float radian = DirectX::XMConvertToRadians(angle) + DirectX::XMConvertToRadians(90);

		// 座標を計算（上から反時計回りにする）
		float x = radius * cos(radian); // X座標
		float y = radius * sin(radian); // Y座標

		// 座標を追加
		position.push_back(Vector3(x, y, 0.0f));

		// 回転を追加（座標と同じ基準で回転を作成）
		rotate.push_back(Quaternion::CreateFromAxisAngle(Vector3::UnitZ, DirectX::XMConvertToRadians(angle)));

	}


	for (int i = 0; i < position.size(); i++)
	{
		auto particle = std::make_unique<BeamChargeEffect>();
		particle->AddPointer(this);
		particle->Initialize(BaseEntity::GetCommonResources(), position[i], rotate[i]);

		m_chargeEffect.push_back(std::move(particle));

	}
}

/// <summary>
/// 削除パーティクルの追加
/// </summary>
/// <param name="effect">削除するパーティクル</param>
void Beam::RegistrationDeleteParticle(BeamChargeEffect* effect)
{
	m_deleteChargeEffect.push_back(effect);

}

/// <summary>
/// パーティクルのクリア
/// </summary>
void Beam::DeleteParticle()
{

	m_chargeEffect.clear();

}


