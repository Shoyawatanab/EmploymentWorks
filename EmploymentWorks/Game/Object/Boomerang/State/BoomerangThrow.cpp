
#include "pch.h"
#include "Game/Object/Boomerang/State/BoomerangThrow.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player/Player.h"
#include "Game/Object/Enemy/BossEnemy.h"
#include "Game/Object/Boomerang/BoomerangOrbit.h"


const float SPEED = 10.0f;

const float ROTATESPEED = 100.0f;

const DirectX::SimpleMath::Vector3 AxisOfRotation(0,1,0);  //回転軸

const DirectX::SimpleMath::Quaternion STARTROTATE(DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, 0.0f, DirectX::XMConvertToRadians(45)));

const DirectX::SimpleMath::Quaternion MIDDLEROTATE(DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, 0.0f, DirectX::XMConvertToRadians(0)));

const DirectX::SimpleMath::Quaternion ENDROTATE(DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(0.0f, 0.0f, DirectX::XMConvertToRadians(-45)));


static float Lerp(float a, float b, float t)
{
	return a + t * (b - a);
}

// コンストラクタ
BoomerangThrow::BoomerangThrow()
	:
	m_worldMatrix{},
	m_boundingSphereLeftLeg{},
	m_boomerang{},
	m_player{}
	, m_enemy{},
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

	
	m_startRotate = STARTROTATE;

	m_endRotate = MIDDLEROTATE;

	m_rotateRate = 0;

}



// 更新する
void BoomerangThrow::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX::SimpleMath;

	switch (m_state)
	{
		case BoomerangThrow::BoomerangThrowState::SplineCurve:
			SplineCurve(elapsedTime);
			break;
		case BoomerangThrow::BoomerangThrowState::ChaseToPlayer:
			ChaseToPlayer(elapsedTime);
			break;
		default:
			break;
	}

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
	m_rotateY += elapsedTime * ROTATESPEED;

	//vec13 = maxDistance

	//1になる前に戻りになってしまうから0.94にしている
	if (m_rotateRate < 0.999f)
	{
		//外積を利用して距離を求める

		Vector3 vec13 = m_moveSpherePos[m_moveSpherePos.size() / 2] - m_startPosition;
		Vector3 vec12 = m_boomerang->GetPosition() - m_startPosition;

		vec13;
		vec13.Normalize();

		Vector3 projection = vec13 * vec12.Dot(vec13);

		Vector3 pos = m_startPosition + projection;

		float distance = Vector3::Distance(m_startPosition, pos);

		m_rotateRate = distance / m_maxDistance;

		m_rotate = Quaternion::Lerp(m_startRotate, m_endRotate, m_rotateRate);

	}
	else
	{
		m_startRotate = m_rotate;

		m_endRotate = ENDROTATE;

		m_rotateRate = 0;
	}



	m_worldMatrix = Matrix::CreateScale(m_boomerang->GetScale());
	//回転
	m_worldMatrix *= Matrix::CreateRotationY(m_rotateY);
	//傾き
	m_worldMatrix *= Matrix::CreateFromQuaternion(m_rotate);
	m_worldMatrix *= Matrix::CreateTranslation(m_boomerang->GetPosition());

	m_previousFrameDirection = m_direction;

}


void BoomerangThrow::Enter()
{
	using namespace DirectX::SimpleMath;

	m_index = static_cast<int>(m_spherePos.size() - 1);
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
	m_previousFrameDirection = m_boomerang->GetPosition();


	m_moveSpherePos = m_boomerang->GetOrbit()->GetMovePos();

	m_state = BoomerangThrowState::SplineCurve;

	m_boomerang->SetUseState(Boomerang::UseState::Throw);

	m_startPosition = m_boomerang->GetPosition();

	int index = static_cast<int>( m_moveSpherePos.size() / 2);

	//距離を求める
	m_maxDistance =  Vector3::Distance( m_moveSpherePos[index], m_startPosition);


	m_startRotate = STARTROTATE;

	m_endRotate = MIDDLEROTATE;

	m_rotateRate = 0;


}

void BoomerangThrow::Exit()
{

}

void BoomerangThrow::RegistrationInformation(Boomerang* boomerang, Player* player, Enemy* enemy)
{

	m_boomerang = boomerang;
	m_player = player;
	m_enemy = enemy;

}

/// <summary>
/// スプライン曲線
/// </summary>
/// <param name="elapsedTime"></param>
void BoomerangThrow::SplineCurve(const float& elapsedTime)
{
	using namespace DirectX::SimpleMath;

	//距離を求める
	float distance = (m_moveSpherePos[(m_index + 2) % m_moveSpherePos.size()] -
		m_moveSpherePos[(m_index + 1) % m_moveSpherePos.size()]).Length();
	//移動割合
	m_transformRatio = m_totalTime * m_moveSpeed / distance;

	Vector3 Pos = m_boomerang->GetPosition();
	//スプライン曲線をもとに座標を
	Pos = Vector3::CatmullRom(
			m_moveSpherePos[(m_index + 0) % m_moveSpherePos.size()] ,
			m_moveSpherePos[(m_index + 1) % m_moveSpherePos.size()],
			m_moveSpherePos[(m_index + 2) % m_moveSpherePos.size()],
			m_moveSpherePos[(m_index + 3) % m_moveSpherePos.size()],
			m_transformRatio
		);
	
	//座標の更新
	m_boomerang->SetPosition(Pos);
	
	m_direction = Pos - m_previousFrameDirection;

	//割合が１を超えたら次の点に移動
	if (m_transformRatio > 1.0f)
	{
		m_index++;
		m_totalTime = 0.0f;
	}

	//最後の点についたらプレイヤを追いかける処理に切り替える
	if (m_index >= m_startIndex * 2 )
	{

		//状態遷移
		//m_boomerang->ChangeState(m_boomerang->GetBoomerangIdling());
		m_state = BoomerangThrowState::ChaseToPlayer;

	}


	m_totalTime += elapsedTime;
}

void BoomerangThrow::ChaseToPlayer(const float& elapsedTime)
{

	DirectX::SimpleMath::Vector3 BoomerangPos = m_boomerang->GetPosition();

	DirectX::SimpleMath::Vector3 PlayerPos = m_player->GetPosition();


	//進む方向
	DirectX::SimpleMath::Vector3 MoveDirection = PlayerPos - BoomerangPos;
	MoveDirection.Normalize();

	MoveDirection *= SPEED * elapsedTime;

	BoomerangPos += MoveDirection;

	m_boomerang->SetPosition(BoomerangPos);

	float distance = (PlayerPos - BoomerangPos).Length();




	//近づいたら
	if (distance <= 2.0f)
	{
		m_boomerang->ChangeState(m_boomerang->GetBoomerangIdling());

	}


}
