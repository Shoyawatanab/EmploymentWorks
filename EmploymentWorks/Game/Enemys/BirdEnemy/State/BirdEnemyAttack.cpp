
#include "pch.h"
#include "BirdEnemyAttack.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Player/Player.h"
#include "Game/Enemys/BirdEnemy/BirdEnemy.h"
#include "Game/Enemys/BirdEnemy/Beam/BirdEnemyBeam.h"
#include "Game/InstanceRegistry.h"


/// <summary>
/// コンストラクタ
/// </summary>
BirdEnemyAttack::BirdEnemyAttack(BirdEnemy* owner, std::vector<std::unique_ptr<BirdEnemyBeam>>& beams)
	:
	m_player{}
	,m_birdEnemy{owner}
	,m_accumulationTime{}
	,m_shotTime{}
	,m_bulletCount{}
	,m_beams{beams}
{

}



/// <summary>
/// デストラク
/// </summary>
BirdEnemyAttack::~BirdEnemyAttack()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resoure">共通リソース</param>
void BirdEnemyAttack::Initialize()
{

	m_player = InstanceRegistry::GetInstance()->GetRegistryInstance<Player>("Player");


}


/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BirdEnemyAttack::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//回転の更新
	m_birdEnemy->Rotate(elapsedTime);



}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void BirdEnemyAttack::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);


}

/// <summary>
/// 状態に入った時
/// </summary>
void BirdEnemyAttack::Enter()
{
	//初期化
	m_accumulationTime = 0;
	m_shotTime = 0;
	m_bulletCount = 0;

	//ビーム
	for (auto& beam : m_beams)
	{
		//通常状態かどうか
		if (beam->GetStateMahine()->GetCurrentState() == beam->GetStateMahine()->GetBirdEnemyBeamIdle())
		{
			beam->GetStateMahine()->ChangeState(beam->GetStateMahine()->GetBirdEnemyBeamPreliminaryAction());
			return;
		}

	}


}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BirdEnemyAttack::Exit()
{

}


