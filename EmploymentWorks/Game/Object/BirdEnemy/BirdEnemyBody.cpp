#include "pch.h"
#include "Game/Object/BirdEnemy/BirdEnemyBody.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Game/Object/BirdEnemy/BirdEnemyLeftFeather.h"
#include "Game/Object/BirdEnemy/BirdEnemyRightFeather.h"
#include "Game/DetectionCollision/CollisionManager.h"

void BirdEnemyBody::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
	BirdEnemyBase::RegistrationCollionManager(collsionManager);
}



void BirdEnemyBody::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
}

// コンストラクタ
BirdEnemyBody::BirdEnemyBody(CommonResources* resources, IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	BirdEnemyBase(resources,parent,initialScale, positonFromParent, initialAngle),
	m_currentPosition{},
	m_currentAngle{},
	m_BirdEnemyBodyParts{},
	m_worldMatrix{},
	m_BirdEnemyBodyCenter{}
{
}

// デストラクタ
BirdEnemyBody::~BirdEnemyBody()
{
	Finalize();
}

// 初期化する
void BirdEnemyBody::Initialize()
{
	using namespace DirectX::SimpleMath;


	auto device = BirdEnemyBase::GetResources()->GetDeviceResources()->GetD3DDevice();
	

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BirdEnemyBody.cmo", *fx);

	//現在の大きさを更新　このクラスの大きさと親の大きさ
	m__currentScale = BirdEnemyBase::GetParent()->GetScale();
	//現在の回転を更新　このクラスの回転と親の回転
	m_currentAngle = BirdEnemyBase::GetInitialAngle() * BirdEnemyBase::GetAnimationRotation() * BirdEnemyBase::GetParent()->GetAngle();
	//回転から座標を計算する
	Vector3 rotatedPosition = Vector3::Transform(BirdEnemyBase::GetPositonFromParent() + BirdEnemyBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(BirdEnemyBase::GetParent()->GetAngle()));
	//現在の座標を更新　このクラスの座標と親の座標 大きさを変えても距離を変えないようにScaleをかける
	m_currentPosition = (rotatedPosition * BirdEnemyBase::GetParent()->GetScale()) + BirdEnemyBase::GetParent()->GetPosition();

	BirdEnemyBase::Initialize(std::move(m_model));

	//バウンディングの生成
	BirdEnemyBase::CreateBounding(m_currentPosition, m_currentAngle,Vector3(0.5f, 0.6f, 1.0f)* m__currentScale ,2.5f * m__currentScale.x);



	

	//「LeftThigh」を生成する
	Attach(std::make_unique<BirdEnemyLeftFeather>(BirdEnemyBase::GetResources(), this, BirdEnemyBase::GetInitialScale(), Vector3(0.5f, 0.0f, 0.0f), 
		Quaternion::CreateFromYawPitchRoll(0.0f, 0.0f, DirectX::XMConvertToRadians(180))));
	//「RightThigh」を生成する
	Attach(std::make_unique<BirdEnemyRightFeather>(BirdEnemyBase::GetResources(), this, BirdEnemyBase::GetInitialScale(), Vector3(-0.5f,0.0f, 0.0f), 
		Quaternion::CreateFromYawPitchRoll(0.0f, 0.0f, DirectX::XMConvertToRadians(0.0f))));

}


// 更新する
void BirdEnemyBody::Update(const float& elapsdTime)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(elapsdTime);
	
	//現在の大きさを更新　このクラスの大きさと親の大きさ
	m__currentScale = BirdEnemyBase::GetParent()->GetScale();
	//現在の回転を更新　このクラスの回転と親の回転
	m_currentAngle = BirdEnemyBase::GetInitialAngle() * BirdEnemyBase::GetAnimationRotation() * BirdEnemyBase::GetParent()->GetAngle();
	//回転から座標を計算する
	Vector3 rotatedPosition = Vector3::Transform(BirdEnemyBase::GetPositonFromParent() + BirdEnemyBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(BirdEnemyBase::GetParent()->GetAngle()));
	//現在の座標を更新　このクラスの座標と親の座標 大きさを変えても距離を変えないようにScaleをかける
	m_currentPosition = (rotatedPosition * BirdEnemyBase::GetParent()->GetScale()) + BirdEnemyBase::GetParent()->GetPosition();

	//バウンディングの座標の更新
	BirdEnemyBase::BoundingUdate(m_currentPosition,m_currentAngle);

	// 砲塔部品を更新する
	BirdEnemyBase::Update(elapsdTime);

}

// 描画する
void BirdEnemyBody::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	using namespace ::DirectX::SimpleMath;
	//ワールド行列を生成
	m_worldMatrix = Matrix::CreateScale(m__currentScale);
	m_worldMatrix *= Matrix::CreateFromQuaternion(m_currentAngle);
	m_worldMatrix *= Matrix::CreateTranslation(m_currentPosition);

	//バウンディングの描画
	//BirdEnemyBase::BoundingRender(view, projection);

	//描画する
	BirdEnemyBase::Render(m_worldMatrix, view,projection);


}

// 後処理を行う
void BirdEnemyBody::Finalize()
{
	// 削除する部品をリセットする
	m_BirdEnemyBodyParts.clear();
}

// 砲弾をチャージする
void BirdEnemyBody::ChargeBullets()
{
}

// 砲塔境界球を作成する
DirectX::BoundingSphere BirdEnemyBody::CreateBoundingSphere(const float& radius)
{
	// 境界球を宣言する
	DirectX::BoundingSphere BirdEnemyBodyBoundingSphere;
	// 境界球の半径を設定する
	BirdEnemyBodyBoundingSphere.Radius = radius;
	// 境界球を返す
	return BirdEnemyBodyBoundingSphere;
}


