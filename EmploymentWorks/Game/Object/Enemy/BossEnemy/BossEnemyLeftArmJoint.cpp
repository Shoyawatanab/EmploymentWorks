#include "pch.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyLeftArmJoint.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyLeftArm.h"
#include "Game/DetectionCollision/CollisionManager.h"


void BossEnemyLeftArmJoint::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
	BossEnemyBase::RegistrationCollionManager(collsionManager);

}

void BossEnemyLeftArmJoint::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	UNREFERENCED_PARAMETER(Pos);

	switch (PartnerTag)
	{
		case CollsionObjectTag::Boomerang:
			BossEnemyBase::PartsDamage(BossEnemyBase::BOOMERANGDAMEGE);
			break;
		default:
			break;
	}

}

void BossEnemyLeftArmJoint::Damage(const int damage)
{
	BossEnemyBase::Damage(damage);

}

// コンストラクタ
BossEnemyLeftArmJoint::BossEnemyLeftArmJoint(CommonResources* resources, BossEnemyBase* parent,
	const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, 
	const DirectX::SimpleMath::Quaternion& initialAngle, int partsHp)
	:
	BossEnemyBase(resources,parent,initialScale, positonFromParent, initialAngle,partsHp),
	m_currentPosition{},
	m_currentAngle{},
	m_BossEnemyLeftArmJointParts{},
	m_worldMatrix{},
	m_BossEnemyLeftArmJointCenter{}
{
}

// デストラクタ
BossEnemyLeftArmJoint::~BossEnemyLeftArmJoint()
{
	Finalize();
}

// 初期化する
void BossEnemyLeftArmJoint::Initialize()
{
	using namespace DirectX::SimpleMath;


	auto device = BossEnemyBase::GetResources()->GetDeviceResources()->GetD3DDevice();
	

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BossEnemyArmJoint.cmo", *fx);

	//現在の大きさの初期化　このクラスの大きさと親の大きさ
	m__currentScale = BossEnemyBase::GetParent()->GetScale();
	//現在の回転の初期化　このクラスの回転と親の回転
	m_currentAngle = BossEnemyBase::GetInitialAngle() * BossEnemyBase::GetAnimationRotation() * BossEnemyBase::GetParent()->GetAngle();
	//回転から座標を計算する
	Vector3 rotatedPosition = Vector3::Transform(BossEnemyBase::GetPositonFromParent() + BossEnemyBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(BossEnemyBase::GetParent()->GetAngle()));
	m_currentPosition = (rotatedPosition * BossEnemyBase::GetParent()->GetScale()) + BossEnemyBase::GetParent()->GetPosition();


	BossEnemyBase::Initialize(std::move(m_model));

	//バウンディングの生成
	BossEnemyBase::CreateBounding(m_currentPosition, m_currentAngle, Vector3(0.4f, 0.7f, 0.4f) * m__currentScale, 1.0f * m__currentScale.x);



	//「LeftArm」を生成する
	Attach(std::make_unique<BossEnemyLeftArm>(BossEnemyBase::GetResources(), this, BossEnemyBase::GetInitialScale(), Vector3(0.0, -1.3f, 0.0f), Quaternion::Identity, BossEnemyBase::ARMHP));




}


// 更新する
void BossEnemyLeftArmJoint::Update(const float& elapsdTime)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(elapsdTime);
	
	//現在の大きさを更新　このクラスの大きさと親の大きさ
	m__currentScale = BossEnemyBase::GetParent()->GetScale();
	//現在の回転を更新　このクラスの回転と親の回転
	m_currentAngle = BossEnemyBase::GetInitialAngle() * BossEnemyBase::GetAnimationRotation() * BossEnemyBase::GetParent()->GetAngle();
	//回転から座標を計算する
	Vector3 rotatedPosition = Vector3::Transform(BossEnemyBase::GetPositonFromParent() + BossEnemyBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(BossEnemyBase::GetParent()->GetAngle()));
	//現在の座標を更新　このクラスの座標と親の座標 大きさを変えても距離を変えないようにScaleをかける
	m_currentPosition = (rotatedPosition * BossEnemyBase::GetParent()->GetScale()) + BossEnemyBase::GetParent()->GetPosition();

	//バウンディングの座標の更新
	BossEnemyBase::BoundingUdate(m_currentPosition, m_currentAngle);


	// 砲塔部品を更新する
	BossEnemyBase::Update(elapsdTime);
}

// 描画する
void BossEnemyLeftArmJoint::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	using namespace ::DirectX::SimpleMath;
	//ワールド行列を生成
	m_worldMatrix = Matrix::CreateScale(m__currentScale);
	m_worldMatrix *= Matrix::CreateFromQuaternion(m_currentAngle);
	m_worldMatrix *= Matrix::CreateTranslation(m_currentPosition);

	//バウンディングの描画
	BossEnemyBase::BoundingRender(view, projection);


	//描画する
	BossEnemyBase::Render(m_worldMatrix, view,projection);

}

// 後処理を行う
void BossEnemyLeftArmJoint::Finalize()
{
	// 削除する部品をリセットする
	m_BossEnemyLeftArmJointParts.clear();
}

// 砲弾をチャージする
void BossEnemyLeftArmJoint::ChargeBullets()
{
}

// 砲塔境界球を作成する
DirectX::BoundingSphere BossEnemyLeftArmJoint::CreateBoundingSphere(const float& radius)
{
	// 境界球を宣言する
	DirectX::BoundingSphere BossEnemyLeftArmJointBoundingSphere;
	// 境界球の半径を設定する
	BossEnemyLeftArmJointBoundingSphere.Radius = radius;
	// 境界球を返す
	return BossEnemyLeftArmJointBoundingSphere;
}

