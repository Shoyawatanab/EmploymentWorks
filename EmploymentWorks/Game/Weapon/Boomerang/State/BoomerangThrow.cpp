#include "pch.h"
#include "BoomerangThrow.h"
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
BoomerangThrow::BoomerangThrow()
	:
	m_commonResources{}
	,m_splineCurvePosition{}
	,m_index{}
	,m_totalTime{}
	,m_state{}
	,m_rotationDatas{}
	,m_horizontalRotation{}
	,m_initialRotation{}
{


}

/// <summary>
/// デストラクタ
/// </summary>
BoomerangThrow::~BoomerangThrow()
{
}


/// <summary>
/// 必要なポインタの追加
/// </summary>
/// <param name="boomerang">ブーメラン</param>
/// <param name="player">プレイヤ</param>
/// <param name="targetMarker">ターゲットマーカー</param>
/// <param name="tpsCamera">TPSカメラ</param>
void BoomerangThrow::AddPointer(Boomerang* boomerang, Player* player, TargetMarker* targetMarker,WataLib::TPS_Camera* tpsCamera)
{
	m_boomerang = boomerang;
	m_player = player;
	m_targetMarker = targetMarker;
	m_tpsCamera = tpsCamera;
}

/// <summary>
/// スプライン曲線の基準点の作成
/// </summary>
void BoomerangThrow::CreateSplineCurvePositon()
{

	std::vector<DirectX::SimpleMath::Vector3> basePosition = m_boomerang->GetThrowBasePosition();

	//ターゲットの取得
	Vector3 target;

	//ロックオンしていたら
	if (m_targetMarker->GetIsLockOn())
	{
		//ロックオンしている敵の座標に
		target = m_targetMarker->GetTargetPosition();
	}
	else
	{

		target = m_tpsCamera->GetCameraForward();

		target.Normalize();

		target *= TARGET_LENGTH;

		target += m_tpsCamera->GetTargetPosition();

	}
	
	//ブーメランからターゲットまでの距離
	Vector3 boomerangToTargetDistance = target - m_boomerang->GetPosition();
	//高さをゼロに
	boomerangToTargetDistance.y = 0.0f;
	//float型に変換　長さを半分に
	float boomerangToTargetLenght = boomerangToTargetDistance.Length();

	//基準点を変更
	for (int i = 0; i < basePosition.size(); i++)
	{
		////基準点から中心までの距離を求める
		//Vector3 distance = basePosition[i] - Vector3::Zero;
		//基準点から中心までの長さを求める
		float lenght = basePosition[i].Length();
		//割合を求める
		float ratio = (lenght == 0.0f) ? 0.0f : boomerangToTargetLenght / lenght;		
		//割合をもとに基準点を変更
		basePosition[i] *= ratio;
		//高さをブーメランの位置に合わせる
		basePosition[i].y = m_boomerang->GetPosition().y;

	}

	for (int i = 0; i < basePosition.size(); i++)
	{
		//一番遠い基準点との割合を求める
		float ratio = basePosition[i].z / basePosition[basePosition.size() / 2].z;
		//高さの調整
		basePosition[i].y = Lerp(m_boomerang->GetPosition().y, target.y, ratio);
	
	}
 
	Quaternion rotation = m_player->GetRotation();

	for (int i = 0; i < basePosition.size(); i++)
	{
		//プレイヤの回転に合わせる
		basePosition[i] = Vector3::Transform(basePosition[i], rotation);
		//プレイヤの座標を加算する
		basePosition[i].x += m_boomerang->GetPosition().x;
		basePosition[i].z += m_boomerang->GetPosition().z;
	}


	m_splineCurvePosition = basePosition;

}

float BoomerangThrow::Lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

/// <summary>
/// スプライン曲線
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BoomerangThrow::SplineCurve(const float& elapsedTime)
{
	//座標の距離を求める
	float distance = (m_splineCurvePosition[(m_index + 1) % m_splineCurvePosition.size()]
		- m_splineCurvePosition[(m_index) % m_splineCurvePosition.size()]).Length();
	

	//割合を求める
	float ratio = m_totalTime * Params::BOOMERANG_MOVE_SPEED / distance;

	//スプライン曲線を使用して座標を求める
	Vector3 position = Vector3::CatmullRom(
		m_splineCurvePosition[(m_index - 1) % m_splineCurvePosition.size()],
		m_splineCurvePosition[(m_index + 0) % m_splineCurvePosition.size()],
		m_splineCurvePosition[(m_index + 1) % m_splineCurvePosition.size()],
		m_splineCurvePosition[(m_index + 2) % m_splineCurvePosition.size()],
		ratio
	);

	//座標の登録
	m_boomerang->SetPosition(position);


	if (ratio > 1.0f)
	{
		//次の点と点に変更
		m_index++;
		m_totalTime = 0.0f;

		//半分まで行ったら
		if ((m_index ) % m_splineCurvePosition.size() == m_splineCurvePosition.size() / 2)
		{
			ChangeRotationDatas(Params::BOOMERANG_THROW_MIDDLE_ROTATION, Params::BOOMERANG_THROW_END_ROTATION);
		}

		//最後の基準点に来たら
		if ((m_index) % m_splineCurvePosition.size() == m_splineCurvePosition.size() - 1)
		{
			m_state = State::ChaseToPlayer;
		}
	}

	//経過時間の加算
	m_totalTime += elapsedTime;

}

/// <summary>
/// プレイヤを追いかける
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BoomerangThrow::ChaseToPlayer(const float& elapsedTime)
{
	//ブーメランの座標を取得
	DirectX::SimpleMath::Vector3 BoomerangPos = m_boomerang->GetPosition();
	//プレイヤの座標を取得
	DirectX::SimpleMath::Vector3 PlayerPos = m_player->GetPosition();


	//進む方向
	DirectX::SimpleMath::Vector3 MoveDirection = PlayerPos - BoomerangPos;
	MoveDirection.Normalize();
	//どれだけ移動するか求める
	MoveDirection *= Params::BOOMERANG_MOVE_SPEED * elapsedTime;
	//移動値の加算
	BoomerangPos += MoveDirection;
	//座標の登録
	m_boomerang->SetPosition(BoomerangPos);

	//プレイヤとの距離を求める
	float distance = (PlayerPos - BoomerangPos).Length();

	//近づいたら
	if (distance <= 2.0f)
	{
		//状態変化
		m_boomerang->GetBoomerangStatemachine()->ChangeState(m_boomerang->GetBoomerangStatemachine()->GetBoomerangIdel());
	}


}

/// <summary>
/// 回転
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BoomerangThrow::Rotation(const float& elapsedTime)
{

	//横回転
	m_horizontalRotation *= Quaternion::CreateFromAxisAngle(Vector3::Up, Params::BOOMERANG_HORIZONTAL_ROTATION_SPEED *elapsedTime);

	//斜めの回転
	Quaternion rotation;
	//スタート地点から中間地点までのベクトル
	Vector3 startToMidleVec = m_splineCurvePosition[m_splineCurvePosition.size() / 2] - m_splineCurvePosition[0];
	startToMidleVec.Normalize();
	//スタート地点からブーメランまでのベクトル
	Vector3 startToBoomerangVec = m_boomerang->GetPosition() - m_splineCurvePosition[0];
	//投影ベクトル
	Vector3 projectionVec = startToMidleVec * startToBoomerangVec.Dot(startToMidleVec);

	Vector3 pos = m_splineCurvePosition[0] + projectionVec;

	float distance = Vector3::Distance(m_splineCurvePosition[0], pos);
	//割合を求める
	float ratio = distance / Vector3::Distance(m_splineCurvePosition[m_splineCurvePosition.size() / 2] , m_splineCurvePosition[0]);
	ratio = std::min(ratio, 1.0f);
	//斜めの回転を求める
	rotation = Quaternion::Lerp(m_rotationDatas.first, m_rotationDatas.second, ratio);
	//回転の設定　横の回転　斜めの回転　初期の回転
	m_boomerang->SetRotation(m_horizontalRotation * rotation * m_initialRotation);
	//m_boomerang->SetRotation(m_horizontalRotation);
}

/// <summary>
/// 回転のデータの切り替え
/// </summary>
/// <param name="firstVec">初期値</param>
/// <param name="secondVec">終了値</param>
void BoomerangThrow::ChangeRotationDatas(DirectX::SimpleMath::Quaternion firstVec, DirectX::SimpleMath::Quaternion secondVec)
{

	m_rotationDatas.first = firstVec;
	m_rotationDatas.second = secondVec;



}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void BoomerangThrow::Initialize(CommonResources* resources)
{
	m_commonResources = resources;



	
}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BoomerangThrow::Update(const float& elapsedTime)
{
	//回転
	Rotation(elapsedTime);

	switch (m_state)
	{
		case BoomerangThrow::State::SplineCurve:
			SplineCurve(elapsedTime);
			break;
		case BoomerangThrow::State::ChaseToPlayer:
			ChaseToPlayer(elapsedTime);
			break;
		default:
			break;
	}
	

}

void BoomerangThrow::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
}

/// <summary>
/// 状態に入った時
/// </summary>
void BoomerangThrow::Enter()
{
	//1ブーメランの行列から大きさ座標回転の抽出
	Matrix matrix = m_boomerang->GetWorldMatrix();
	Vector3 scale;
	Vector3 position;
	Quaternion rotation;
	matrix.Decompose(scale,rotation,position);
	m_boomerang->SetScale(scale);
	m_boomerang->SetRotation(rotation);
	m_boomerang->SetPosition(position);

	//基準点を作る
	CreateSplineCurvePositon();
	//初期化
	m_index = 0;
	m_horizontalRotation = Quaternion::Identity;
	m_state = State::SplineCurve;

	//ブーメランの親子関係を切る
	//m_boomerang->SetIsParentActive(false);
	m_boomerang->SetParent(nullptr);

	//回転の情報を切り替える
	ChangeRotationDatas(Params::BOOMERANG_THROW_START_ROTATION, Params::BOOMERANG_THROW_MIDDLE_ROTATION);
	
	//初期回転をプレイヤの回転に
	m_initialRotation = m_player->GetRotation();
}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BoomerangThrow::Exit()
{
}



