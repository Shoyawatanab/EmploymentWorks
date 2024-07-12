
#include "pch.h"
#include "Game/Object/Boomerang/State/BoomerangThrow.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player.h"
#include "Game/Object/Enemy.h"


const float SPEED = 2.0f;

const DirectX::SimpleMath::Vector3 AxisOfRotation(0,1,0);  //回転軸

// コンストラクタ
BoomerangThrow::BoomerangThrow(Boomerang* boomerang, Player* player, Enemy* enemy)
	:
	m_worldMatrix{},
	m_boundingSphereLeftLeg{},
	m_boomerang{ boomerang },
	m_player{ player }
	, m_enemy{ enemy },
	m_index{},
	m_moveSpeed{},
	m_rotateY{},
	m_rotationalMotion{},
	m_transformRatio{},
	m_startIndex{},
	m_totalTime{}
{
}

// デストラクタ
BoomerangThrow::~BoomerangThrow()
{

}

// 初期化する
void BoomerangThrow::Initialize()
{
	// 左脚境界球を生成する
	m_boundingSphereLeftLeg = DirectX::BoundingSphere();
	// 左脚境界球の半径を設定する
	m_boundingSphereLeftLeg.Radius = 0.01;

	m_csv = std::make_unique<CSV>();
	m_spherePos =  m_csv->LoadCSVBoomerang();

	for (int i = 0; i < m_spherePos.size(); i++)
	{
		m_moveSpherePos.emplace_back(DirectX::SimpleMath::Vector3());
	}
	m_worldMatrix = DirectX::SimpleMath::Matrix::Identity;

	
}



// 更新する
void BoomerangThrow::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX::SimpleMath;

	SplineCurve(elapsedTime);

	////回転運動
	//Quaternion RotationalMotion ;

	////軸の作成
	//Vector3 axis = m_direction.Cross(AxisOfRotation);
	//
	//if (axis == Vector3::Zero)
	//{
	//	axis = Vector3::UnitY;
	//}

	//float angle = m_rotationalMotion;

	//angle += 2.1f * elapsedTime;

	//RotationalMotion = Quaternion::CreateFromAxisAngle(axis,angle) ;

	//m_rotate = RotationalMotion;
	//m_rotationalMotion = angle;
	m_rotateY += elapsedTime * 20.0f;


	m_worldMatrix = Matrix::CreateScale(m_boomerang->GetScale());
	m_worldMatrix *= Matrix::CreateFromQuaternion(m_rotate);
	m_worldMatrix *= Matrix::CreateRotationY(m_rotateY);
	m_worldMatrix *= Matrix::CreateTranslation(m_boomerang->GetPosition());

	m_previousFrameDirection = m_direction;

}


void BoomerangThrow::Enter()
{
	using namespace DirectX::SimpleMath;

	m_index = m_spherePos.size() - 1;
	m_startIndex = m_index;
	m_transformRatio = 0;
	m_totalTime = 0;
	m_initialRotate = Quaternion::Identity;
	m_moveSpeed = SPEED;
	m_rotate = Quaternion::Identity;
	m_direction = Vector3::Zero;
	m_rotateY = 0;
	m_rotationalMotion = 0;

	m_initialRotate = m_boomerang->GetRotate();
	m_position = m_boomerang->GetPosition();
	m_previousFrameDirection = m_position;

	Matrix SphereMatrix = Matrix::Identity;
	SphereMatrix *= Matrix::CreateFromQuaternion(m_initialRotate);
	//プレイヤと敵の距離
	Vector3 PlayerToEnemyDistance = m_enemy->GetPosition() - m_player->GetPosition();
	//距離をflaotに変換して半分にする
	float PlayerToEnemyLenght = PlayerToEnemyDistance.Length() / 2;

	//ロックオン状態じゃなければ
	if (!m_player->GetIsLockOn())
	{
		//距離を自分で決めたものにする
		PlayerToEnemyLenght = 1;

	}



	//回転の地点を回転させる
	for (int i = 0; i < m_spherePos.size(); i++)
	{
		Vector3 Pos = m_spherePos[i];
		//Sphereとゼロ地点の距離
		Vector3 Distance = Pos - Vector3::Zero;
		//上の距離をfloatがたに変換
		float Lenght = Distance.Length();
		//敵との距離とSphereとの距離の倍率を求める
		float Magnification = PlayerToEnemyLenght / Lenght;
		Distance *= Magnification;
		Pos = Distance;;
		//距離の半分を加算
		Pos.z -= PlayerToEnemyLenght;


		//プレイヤの回転をもとに回転させる
		m_moveSpherePos[i] = Vector3::Transform(Pos, SphereMatrix);
		//原点からになっているからブーメランの位置を加算する
		m_moveSpherePos[i] += m_position;

	}
}

void BoomerangThrow::Exit()
{

}

/// <summary>
/// スプライン曲線
/// </summary>
/// <param name="elapsedTime"></param>
void BoomerangThrow::SplineCurve(const float& elapsedTime)
{
	using namespace DirectX::SimpleMath;

	//m_moveSpeed -= 0.12f * elapsedTime;


	float distance = (m_moveSpherePos[(m_index + 2) % m_moveSpherePos.size()] -
		m_moveSpherePos[(m_index + 1) % m_moveSpherePos.size()]).Length();
	//移動割合
	m_transformRatio = m_totalTime * m_moveSpeed / distance;

	Vector3 Pos = m_boomerang->GetPosition();
		Pos = Vector3::CatmullRom(
			m_moveSpherePos[(m_index + 0) % m_moveSpherePos.size()] ,
			m_moveSpherePos[(m_index + 1) % m_moveSpherePos.size()],
			m_moveSpherePos[(m_index + 2) % m_moveSpherePos.size()],
			m_moveSpherePos[(m_index + 3) % m_moveSpherePos.size()],
			m_transformRatio
		);

	m_boomerang->SetPosition(Pos);
	m_direction = Pos - m_previousFrameDirection;

	if (m_transformRatio > 1.0f)
	{
		m_index++;
		m_totalTime = 0.0f;
	}

	if (m_index >= m_startIndex * 2 + 1)
	{

		//状態遷移
		m_boomerang->ChangeState(m_boomerang->GetBoomerangIdling());

	}


	m_totalTime += elapsedTime;
}