#include "pch.h"
#include "Game/Object/BirdEnemy/BirdEnemyLeftFeather.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Game/DetectionCollision/CollisionManager.h"


void BirdEnemyLeftFeather::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
	BirdEnemyBase::RegistrationCollionManager(collsionManager);

}

void BirdEnemyLeftFeather::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
}

// コンストラクタ
BirdEnemyLeftFeather::BirdEnemyLeftFeather(CommonResources* resources, IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	BirdEnemyBase(resources,parent,initialScale, positonFromParent, initialAngle),
	m_currentPosition{},
	m_currentAngle{},
	m_BirdEnemyLeftFeatherParts{},
	m_worldMatrix{},
	m_BirdEnemyLeftFeatherCenter{}
{
}

// デストラクタ
BirdEnemyLeftFeather::~BirdEnemyLeftFeather()
{
	Finalize();
}

// 初期化する
void BirdEnemyLeftFeather::Initialize()
{
	using namespace DirectX::SimpleMath;


	auto device = BirdEnemyBase::GetResources()->GetDeviceResources()->GetD3DDevice();
	

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BirdEnemyFeather.cmo", *fx);

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
	BirdEnemyBase::CreateBounding(m_currentPosition, m_currentAngle,Vector3(0.7f, 0.15f, 0.45f)* m__currentScale ,2.5f * m__currentScale.x);



	

}


// 更新する
void BirdEnemyLeftFeather::Update(const float& elapsdTime)
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
void BirdEnemyLeftFeather::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
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
void BirdEnemyLeftFeather::Finalize()
{
	// 削除する部品をリセットする
	m_BirdEnemyLeftFeatherParts.clear();
}

// 砲弾をチャージする
void BirdEnemyLeftFeather::ChargeBullets()
{
}

// 砲塔境界球を作成する
DirectX::BoundingSphere BirdEnemyLeftFeather::CreateBoundingSphere(const float& radius)
{
	// 境界球を宣言する
	DirectX::BoundingSphere BirdEnemyLeftFeatherBoundingSphere;
	// 境界球の半径を設定する
	BirdEnemyLeftFeatherBoundingSphere.Radius = radius;
	// 境界球を返す
	return BirdEnemyLeftFeatherBoundingSphere;
}


