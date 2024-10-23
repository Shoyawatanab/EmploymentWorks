#include "pch.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyTorso.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyHead.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyPelvis .h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyLeftShoulder.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyRightShoulder.h"
#include "Game/DetectionCollision/CollisionManager.h"


void BossEnemyTorso::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
	BossEnemyBase::RegistrationCollionManager(collsionManager);

}

void BossEnemyTorso::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	UNREFERENCED_PARAMETER(Pos);

	switch (PartnerTag)
	{
		case CollsionObjectTag::Boomerang:
			break;
		default:
			break;
	}

}

// コンストラクタ
BossEnemyTorso::BossEnemyTorso(CommonResources* resources, IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	BossEnemyBase(resources,parent,initialScale, positonFromParent, initialAngle),
	m_currentPosition{},
	m_currentAngle{},
	m_BossEnemyTorsoParts{},
	m_worldMatrix{},
	m_BossEnemyTorsoCenter{}
{
}

// デストラクタ
BossEnemyTorso::~BossEnemyTorso()
{
	Finalize();
}

// 初期化する
void BossEnemyTorso::Initialize()
{
	using namespace DirectX::SimpleMath;


	auto device = BossEnemyBase::GetResources()->GetDeviceResources()->GetD3DDevice();
	

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BossEnemyTorso.cmo", *fx);

	//現在の大きさを更新　このクラスの大きさと親の大きさ
	m__currentScale = BossEnemyBase::GetParent()->GetScale();
	//現在の回転を更新　このクラスの回転と親の回転
	m_currentAngle = BossEnemyBase::GetInitialAngle() * BossEnemyBase::GetAnimationRotation() * BossEnemyBase::GetParent()->GetAngle();
	//回転から座標を計算する
	Vector3 rotatedPosition = Vector3::Transform(BossEnemyBase::GetPositonFromParent() + BossEnemyBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(BossEnemyBase::GetParent()->GetAngle()));
	//現在の座標を更新　このクラスの座標と親の座標 大きさを変えても距離を変えないようにScaleをかける
	m_currentPosition = (rotatedPosition * BossEnemyBase::GetParent()->GetScale()) + BossEnemyBase::GetParent()->GetPosition();
	BossEnemyBase::Initialize(std::move(m_model));

	//バウンディングの生成
	BossEnemyBase::CreateBounding(m_currentPosition - Vector3(0, 0, 0), m_currentAngle, Vector3(1.9f, 1.6f, 1.15f) * m__currentScale, 3.0f * m__currentScale.x);




	//「Head」を生成する
	Attach(std::make_unique<BossEnemyHead>(BossEnemyBase::GetResources(), this, BossEnemyBase::GetInitialScale(), Vector3(0.0f, 2.1f, 0.0f) , Quaternion::Identity));
		
	//「LeftShouder」を生成する
	Attach(std::make_unique<BossEnemyLeftShoulder>(BossEnemyBase::GetResources(), this, BossEnemyBase::GetInitialScale(), Vector3(2.4f, 1.0f, 0.0f),
		Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(00))));
	//Attach(std::make_unique<BossEnemyLeftShoulder>(BossEnemyBase::GetResources(), this, BossEnemyBase::GetInitialScale(), Vector3(2.6f, 0.5f, 0.0f),
	//	Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(0))));

		//「RightShouder」を生成する
	Attach(std::make_unique<BossEnemyRightShoulder>(BossEnemyBase::GetResources(), this, BossEnemyBase::GetInitialScale(), Vector3(-2.4f, 1.0f, 0.0f),
		Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(00))));

}


// 更新する
void BossEnemyTorso::Update(const float& elapsdTime)
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
	BossEnemyBase::BoundingUdate(m_currentPosition - Vector3(0, 0.0f, 0), m_currentAngle);

	// 砲塔部品を更新する
	BossEnemyBase::Update(elapsdTime);
}

// 描画する
void BossEnemyTorso::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
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
void BossEnemyTorso::Finalize()
{
	// 削除する部品をリセットする
	m_BossEnemyTorsoParts.clear();
}

// 砲弾をチャージする
void BossEnemyTorso::ChargeBullets()
{
}

// 砲塔境界球を作成する
DirectX::BoundingSphere BossEnemyTorso::CreateBoundingSphere(const float& radius)
{
	// 境界球を宣言する
	DirectX::BoundingSphere BossEnemyTorsoBoundingSphere;
	// 境界球の半径を設定する
	BossEnemyTorsoBoundingSphere.Radius = radius;
	// 境界球を返す
	return BossEnemyTorsoBoundingSphere;
}

