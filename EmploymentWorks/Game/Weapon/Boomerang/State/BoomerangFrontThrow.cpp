#include "pch.h"
#include "BoomerangFrontThrow.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"

#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Player/Player.h"
#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Game/Params.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
BoomerangFrontThrow::BoomerangFrontThrow()
	:
	m_commonResources{}
	,m_totalTime{}
	,m_state{}
{


}

/// <summary>
/// デストラクタ
/// </summary>
BoomerangFrontThrow::~BoomerangFrontThrow()
{
}


/// <summary>
/// 必要なポインタの追加
/// </summary>
/// <param name="boomerang">ブーメラン</param>
/// <param name="player">プレイヤ</param>
/// <param name="targetMarker">ターゲットマーカー</param>
/// <param name="tpsCamera">TPSカメラ</param>
void BoomerangFrontThrow::AddPointer(Boomerang* boomerang, Player* player, TargetMarker* targetMarker,WataLib::TPS_Camera* tpsCamera)
{
	m_boomerang = boomerang;
	m_player = player;
	m_targetMarker = targetMarker;
	m_tpsCamera = tpsCamera;
}


float BoomerangFrontThrow::Lerp(float a, float b, float t)
{
	return a + t * (b - a);
}




/// <summary>
/// ターゲットに向かう
/// </summary>
/// <param name="elapsedTime">経過時間</param>
/// <returns>ture:到着したら  false: 近くない</returns>
bool BoomerangFrontThrow::ChaseToTarget(const float& elapsedTime)
{

	//ブーメランの座標を取得
	DirectX::SimpleMath::Vector3 BoomerangPos = m_boomerang->GetPosition();


	//進む方向
	DirectX::SimpleMath::Vector3 MoveDirection = m_targetPosistion - BoomerangPos;
	MoveDirection.Normalize();
	//どれだけ移動するか求める
	MoveDirection *= Params::BOOMERANG_MOVE_SPEED * elapsedTime;
	//移動値の加算
	BoomerangPos += MoveDirection;
	//座標の登録
	m_boomerang->SetPosition(BoomerangPos);

	//プレイヤとの距離を求める
	float distance = (m_targetPosistion - BoomerangPos).Length();

	//近づいたら
	if (distance <= 0.5f)
	{

		return true;

	}

	return false;

}

/// <summary>
/// 回転
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BoomerangFrontThrow::Rotation(const float& elapsedTime)
{
	//横回転を求める
	Quaternion horizontalRotation = Quaternion::CreateFromAxisAngle(Vector3::UnitY, Params::BOOMERANG_HORIZONTAL_ROTATION_SPEED * elapsedTime);

	m_boomerang->SetRotation(m_boomerang->GetRotation() * horizontalRotation);

	

}

/// <summary>
/// 回転のデータの切り替え
/// </summary>
/// <param name="firstVec">初期値</param>
/// <param name="secondVec">終了値</param>
void BoomerangFrontThrow::ChangeRotationDatas(DirectX::SimpleMath::Quaternion firstVec, DirectX::SimpleMath::Quaternion secondVec)
{




}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void BoomerangFrontThrow::Initialize(CommonResources* resources)
{
	m_commonResources = resources;
	
}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BoomerangFrontThrow::Update(const float& elapsedTime)
{
	//回転
	Rotation(elapsedTime);

	switch (m_state)
	{
		case BoomerangFrontThrow::State::SplineCurve:
			{
			
				if (ChaseToTarget(elapsedTime))
				{
					m_targetPosistion = m_player->GetPosition();
					m_state = State::ChaseToPlayer;

				}

			}
			break;
		case BoomerangFrontThrow::State::ChaseToPlayer:
			
			m_targetPosistion = m_player->GetPosition();

			if (ChaseToTarget(elapsedTime))
			{

				m_boomerang->GetBoomerangStatemachine()->ChangeState(m_boomerang->GetBoomerangStatemachine()->GetBoomerangIdel());


			}

			break;
		default:
			break;
	}
	

}

void BoomerangFrontThrow::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
}

/// <summary>
/// 状態に入った時
/// </summary>
void BoomerangFrontThrow::Enter()
{
	//ブーメランの親子関係を切る
	m_boomerang->SetParent(nullptr);

	//1ブーメランの行列から大きさ座標回転の抽出
	Matrix matrix = m_boomerang->GetWorldMatrix();
	Vector3 scale;
	Vector3 position;
	Quaternion rotation;
	matrix.Decompose(scale,rotation,position);
	m_boomerang->SetScale(scale);
	m_boomerang->SetRotation(Quaternion::Identity);
	m_boomerang->SetPosition(position);

	m_state = State::SplineCurve;


	//回転の情報を切り替える 左回りなのでEnd回転から求めている　
	//ChangeRotationDatas(Params::BOOMERANG_THROW_END_ROTATION, Params::BOOMERANG_THROW_MIDDLE_ROTATION);
	
	m_targetPosistion = m_targetMarker->GetTargetPosition();

	m_boomerang->SetIsCollisionActive(true);
}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BoomerangFrontThrow::Exit()
{
	m_boomerang->SetIsCollisionActive(false);

}



