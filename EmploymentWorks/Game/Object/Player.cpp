/*
	@file	Player.cpp
	@brief	プレイシーンクラス
*/
#include "pch.h"
#include "Player.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Object/Enemy/Enemy.h"
#include "Libraries/MyLib/Bounding.h"
#include "Game/DetectionCollision/CollisionManager.h"


const float MOVE_SPEED = 5.0f;                                        //動く時のスピード
const DirectX::SimpleMath::Vector3 INITIAL_DIRECTION( 0.0f,0.0f,-1.0f); //初期の向いている方向
//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
Player::Player(Enemy* enemy)
	:
	m_commonResources{},
	m_model{},
	m_position{},
	m_direction{INITIAL_DIRECTION},
	m_boomerang{},
	m_enemy{ enemy },
	m_graivty{},
	m_isLockOn{}

{
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
Player::~Player()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void Player::Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position)
{
	using namespace DirectX::SimpleMath;


	assert(resources);
	m_commonResources = resources;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();




	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Player.cmo", *fx);

	m_position = position;

	m_boomerang = std::make_unique<Boomerang>(this,m_enemy);
	m_boomerang->Initialize(m_commonResources);

	m_bounding = std::make_unique<Bounding>();
	m_bounding->CreateBoundingBox(m_commonResources, m_position, Vector3(0.4f, 0.8f, 0.4f));
	m_bounding->CreateBoundingSphere(m_commonResources, m_position, 1.0f);

	m_graivty = 0.05f;
	m_isLockOn = false;

}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void Player::Update(float elapsedTime, DirectX::SimpleMath::Quaternion cameraRotation)
{
	UNREFERENCED_PARAMETER(elapsedTime);


	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	// キーボードステートを取得する
	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();

	Vector3 moveDirection = Vector3::Zero;

	if (key.IsKeyDown(Keyboard::Keyboard::W))
	{
		moveDirection.z--;
	}
	if (key.IsKeyDown(Keyboard::Keyboard::S))
	{
		moveDirection.z++;
	}
	if (key.IsKeyDown(Keyboard::Keyboard::A))
	{
		moveDirection.x--;
	}
	if (key.IsKeyDown(Keyboard::Keyboard::D))
	{
		moveDirection.x++;
	}

	moveDirection = Vector3::Transform(moveDirection, cameraRotation);

	
	Rotate(elapsedTime, moveDirection);

	Move(elapsedTime, moveDirection);
	Attack(elapsedTime, key);

	m_position.y -= m_graivty;


	m_boomerang->Update(elapsedTime);

}

//---------------------------------------------------------
// 描画する
//---------------------------------------------------------
void Player::Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{
	using namespace DirectX::SimpleMath;

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();


	// ワールド行列を更新する
	Matrix world = Matrix::CreateScale(0.3f);
	world *= Matrix::CreateFromQuaternion(m_rotate);
	world *= Matrix::CreateTranslation(m_position);


	// モデルを描画する
	m_model->Draw(context, *states, world, view, projection);
	m_bounding->DrawBoundingBox(m_position, view, projection);
	m_bounding->DrawBoundingSphere(m_position, view, projection);

	m_boomerang->Render(view, projection);



}

//---------------------------------------------------------
// 後始末する
//---------------------------------------------------------
void Player::Finalize()
{
	// do nothing.
}


void Player::Move(float elapsedTime, DirectX::SimpleMath::Vector3 moveDirection)
{
	using namespace DirectX::SimpleMath;

	if (moveDirection == Vector3::Zero)
	{
		return;
	}

	moveDirection ;
	m_position += moveDirection *= MOVE_SPEED * elapsedTime;

}

void Player::Attack(float elapsedTime, DirectX::Keyboard::State key)
{
	using namespace DirectX;

	Mouse::State a;


	//投げる
	if (m_boomerang->GetBoomerangState() == m_boomerang->GetBoomerangGetReady()
		&& key.IsKeyUp(Keyboard::Keys::Space))
	{
		m_boomerang->ChangeState(m_boomerang->GetBoomerangThrow());
	}
	//構える
	if (m_boomerang->GetBoomerangState() == m_boomerang->GetBoomerangIdling()
		&& key.IsKeyDown(Keyboard::Keys::Space))
	{
		m_boomerang->ChangeState(m_boomerang->GetBoomerangGetReady());
	}



	//if (m_boomerang->GetBoomerangState() == m_boomerang->GetBoomerangGetReady()
	//	&& key.IsKeyUp(Keyboard::Keys::Space))

	
}


void Player::Rotate(float elapsedTime, DirectX::SimpleMath::Vector3 moveDirection)
{

	using namespace DirectX::SimpleMath;

	if (m_boomerang->GetBoomerangState() == m_boomerang->GetBoomerangGetReady())
	{
		//カメラの向いている方向にプレイヤの正面を合わせる

		m_rotate = m_cameraRatate;
		m_direction = Vector3::Transform(INITIAL_DIRECTION, m_rotate);

		m_direction.Normalize();


	}
	else
	{
		if (moveDirection == Vector3::Zero)
		{
			return;
		}
		moveDirection.Normalize();
		//現在の向きと動く方向から軸を作る
		Vector3 axis = moveDirection.Cross(m_direction);

		if (axis == Vector3::Zero)
		{
			axis = Vector3::UnitY;
		}

		//
		axis *= -1;

		float  angle = Vector3::Distance(moveDirection, m_direction);
		angle *= elapsedTime * 10.0f;
		Quaternion rotation = m_rotate;
		rotation *= Quaternion::CreateFromAxisAngle(axis, angle);

		m_rotate = rotation;


		m_direction = Vector3::Transform(INITIAL_DIRECTION, rotation);

		m_direction.Normalize();
	}
}


void Player::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
	m_boomerang->RegistrationCollionManager(collsionManager);
}


void Player::OnCollision(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{


}
