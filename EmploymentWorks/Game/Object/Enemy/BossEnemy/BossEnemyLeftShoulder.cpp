#include "pch.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyLeftShoulder.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyLeftArmJoint.h"


void BossEnemyLeftShoulder::RegistrationCollionManager(CollisionManager* collsionManager)
{
}

void BossEnemyLeftShoulder::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
}

// コンストラクタ
BossEnemyLeftShoulder::BossEnemyLeftShoulder(CommonResources* resources, IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	BossEnemyBase(resources,parent,initialScale, positonFromParent, initialAngle),
	m_currentPosition{},
	m_currentAngle{},
	m_BossEnemyLeftShoulderParts{},
	m_worldMatrix{},
	m_BossEnemyLeftShoulderCenter{}
{
}

// デストラクタ
BossEnemyLeftShoulder::~BossEnemyLeftShoulder()
{
	Finalize();
}

// 初期化する
void BossEnemyLeftShoulder::Initialize()
{
	using namespace DirectX::SimpleMath;


	auto device = BossEnemyBase::GetResources()->GetDeviceResources()->GetD3DDevice();
	

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BossEnemyShoulder.cmo", *fx);

	//現在の大きさを更新　このクラスの大きさと親の大きさ
	m__currentScale = BossEnemyBase::GetParent()->GetScale();
	//現在の回転を更新　このクラスの回転と親の回転
	m_currentAngle = BossEnemyBase::GetInitialAngle() * BossEnemyBase::GetAnimationRotation() * BossEnemyBase::GetParent()->GetAngle();
	//回転から座標を計算する
	Vector3 rotatedPosition = Vector3::Transform(BossEnemyBase::GetPositonFromParent() + BossEnemyBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(BossEnemyBase::GetParent()->GetAngle()));
	//現在の座標を更新　このクラスの座標と親の座標 大きさを変えても距離を変えないようにScaleをかける
	m_currentPosition = (rotatedPosition * BossEnemyBase::GetParent()->GetScale()) + BossEnemyBase::GetParent()->GetPos();

	BossEnemyBase::Initialize(std::move(m_model));

	//バウンディングの生成
	BossEnemyBase::CreateBounding(m_currentPosition - Vector3(0, 0.45f, 0), m_currentAngle, Vector3(0.67f, 1.0f, 0.67f) * m__currentScale, 1.6f * m__currentScale.x);


	//アニメーションの生成　引数　大きさ　座標　回転　時間
	std::vector<BossEnemyBase::AnimationKeyFrame> animation;
	//test
	animation.push_back({ Vector3(1, 1, 1), Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity, 0.0f });            //初期値
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0), 
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(-15),DirectX::XMConvertToRadians(-130),DirectX::XMConvertToRadians(0))
		, 0.8f });            //腕の振り上げ
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0),
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(-15),DirectX::XMConvertToRadians(-130),DirectX::XMConvertToRadians(0))
		, 2.0f });            //溜め時間
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0),
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(-15),DirectX::XMConvertToRadians(-20),DirectX::XMConvertToRadians(0))
		, 0.5f });            //おろす


	//アニメーションを登録
	BossEnemyBase::SetAnimations(animation, "SwingingDownBothArms");


	//「LeftArmJoint」を生成する
	Attach(std::make_unique<BossEnemyLeftArmJoint>(BossEnemyBase::GetResources(), this, BossEnemyBase::GetInitialScale(), Vector3(0.0, -1.7f, 0.0f), Quaternion::Identity));

}


// 更新する
void BossEnemyLeftShoulder::Update(const float& elapsdTime)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(elapsdTime);

	//m_leftShoulderAngle *=  Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(-0.1f), DirectX::XMConvertToRadians(0.0f));
	
	//現在の大きさを更新　このクラスの大きさと親の大きさ
	m__currentScale = BossEnemyBase::GetParent()->GetScale();
	//現在の回転を更新　このクラスの回転と親の回転
	m_currentAngle = BossEnemyBase::GetInitialAngle() * BossEnemyBase::GetAnimationRotation() * BossEnemyBase::GetParent()->GetAngle();
	//回転から座標を計算する
	Vector3 rotatedPosition = Vector3::Transform(BossEnemyBase::GetPositonFromParent() + BossEnemyBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(BossEnemyBase::GetParent()->GetAngle()));
	//現在の座標を更新　このクラスの座標と親の座標 大きさを変えても距離を変えないようにScaleをかける
	m_currentPosition = (rotatedPosition * BossEnemyBase::GetParent()->GetScale()) + BossEnemyBase::GetParent()->GetPos();

	//バウンディングの座標の更新
	BossEnemyBase::BoundingUdate(m_currentPosition - Vector3(0, 0.45f, 0), m_currentAngle);


	// 砲塔部品を更新する
	BossEnemyBase::Update(elapsdTime);


}

// 描画する
void BossEnemyLeftShoulder::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
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
void BossEnemyLeftShoulder::Finalize()
{
	// 削除する部品をリセットする
	m_BossEnemyLeftShoulderParts.clear();
}

// 砲弾をチャージする
void BossEnemyLeftShoulder::ChargeBullets()
{
}

// 砲塔境界球を作成する
DirectX::BoundingSphere BossEnemyLeftShoulder::CreateBoundingSphere(const float& radius)
{
	// 境界球を宣言する
	DirectX::BoundingSphere BossEnemyLeftShoulderBoundingSphere;
	// 境界球の半径を設定する
	BossEnemyLeftShoulderBoundingSphere.Radius = radius;
	// 境界球を返す
	return BossEnemyLeftShoulderBoundingSphere;
}

