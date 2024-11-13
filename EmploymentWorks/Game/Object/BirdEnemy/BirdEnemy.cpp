#include "pch.h"
#include "Game/Object/BirdEnemy/BirdEnemy.h"

#include "Game/Object/BirdEnemy/BirdEnemyBody.h"
#include "Game/DetectionCollision/CollisionManager.h"
#include "Libraries/MyLib/Bounding.h"

// コンストラクタ
BirdEnemy::BirdEnemy(CommonResources* resources,IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	BirdEnemyBase(resources,parent, initialScale,DirectX::SimpleMath::Vector3::Zero, initialAngle),
	m_commonResources{resources},
	m_position{initialPosition},

	m_worldMatrix{}
{
}

// デストラクタ
BirdEnemy::~BirdEnemy()
{
	Finalize();
}

// 初期化する
void BirdEnemy::Initialize()
{
	using namespace DirectX::SimpleMath;

	//「Body」を生成する
	Attach(std::make_unique<BirdEnemyBody>(BirdEnemyBase::GetResources(), this, BirdEnemyBase::GetInitialScale(), Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity));

	m_bounding = std::make_unique<Bounding>();
	m_bounding->CreateBoundingBox(m_commonResources, m_position, Vector3(0.7f, 0.4f,0.5f));
	m_bounding->CreateBoundingSphere(m_commonResources, m_position, 6.0f);

	float scale = 0.5f;

	m_scale = Vector3(scale, scale, scale);


}



// キーボードイベントを処理する
void BirdEnemy::HandleKeyboardEvent()
{
	using namespace DirectX::SimpleMath;

	// キーボードステートを取得する
	DirectX::Keyboard::State keyboardState = DirectX::Keyboard::Get().GetState();







}

// 更新する
void BirdEnemy::Update(const float& elapsdTime)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(elapsdTime);

	//// キーボードイベントを処理する
	HandleKeyboardEvent();

	// キーボードステートを取得する
	DirectX::Keyboard::State keyboardState = DirectX::Keyboard::Get().GetState();


	//大きさを変えるとアニメーションの位置がずれるので直す
	//m_currentAngle *= Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0.1f), 0, DirectX::XMConvertToRadians(0.0f));
	//m_currentPosition.z += 0.01f;


	//m_currentPosition += BirdEnemyBase::GetAnimationPosition();

	if (keyboardState.IsKeyDown(DirectX::Keyboard::Keyboard::D))
	{
	}

	// 砲塔部品を更新する
	BirdEnemyBase::Update(elapsdTime);

	m_bounding->Update(m_position );

}

// 描画する
void BirdEnemy::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	m_bounding->DrawBoundingBox(view, projection);

	// 砲塔部品を描画する
	BirdEnemyBase::Render(view, projection);


}

// 後処理を行う
void BirdEnemy::Finalize()
{

}

// 砲塔境界球を作成する
DirectX::BoundingSphere BirdEnemy::CreateBoundingSphere(const float& radius)
{
	// 境界球を宣言する
	DirectX::BoundingSphere BirdEnemyBoundingSphere;
	// 境界球の半径を設定する
	BirdEnemyBoundingSphere.Radius = radius;
	// 境界球を返す
	return BirdEnemyBoundingSphere;
}

void BirdEnemy::SetAnimation(std::string name)
{
	SetRunnginAnimationName("FallDown");

}

void BirdEnemy::RegistrationInformation()
{

}

void BirdEnemy::Instances()
{
	m_bounding = std::make_unique<Bounding>();

}

void BirdEnemy::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);

	BirdEnemyBase::RegistrationCollionManager(collsionManager);

}

void BirdEnemy::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
}

