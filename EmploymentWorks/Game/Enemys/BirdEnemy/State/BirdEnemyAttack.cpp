
#include "pch.h"
#include "BirdEnemyAttack.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Player/Player.h"
#include "Game/Enemys/BirdEnemy/BirdEnemy.h"
#include "Game/Enemys/BirdEnemy/Beam/BirdEnemyBeam.h"



/// <summary>
/// コンストラクタ
/// </summary>
BirdEnemyAttack::BirdEnemyAttack()
	:
	m_commonResources{},
	m_player{}
	,m_birdEnemy{}
	,m_accumulationTime{}
	,m_shotTime{}
	,m_bulletCount{}
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
void BirdEnemyAttack::Initialize(CommonResources* resoure)
{

	m_commonResources = resoure;


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

	m_birdEnemy->Rotate(elapsedTime);




}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void BirdEnemyAttack::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

}

/// <summary>
/// 状態に入った時
/// </summary>
void BirdEnemyAttack::Enter()
{
	m_accumulationTime = 0;
	m_shotTime = 0;

	m_bulletCount = 0;


	std::vector<std::unique_ptr<BirdEnemyBeam>>& beams = m_birdEnemy->GetBeams();



	for (auto& beam : beams)
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

/// <summary>
/// 必要なポインタの追加
/// </summary>
/// <param name="player">プレイヤ</param>
/// <param name="birdEnemy">鳥の敵</param>
void BirdEnemyAttack::AddPointer(Player* player, BirdEnemy* birdEnemy)
{
	m_player = player;
	m_birdEnemy = birdEnemy;

}

