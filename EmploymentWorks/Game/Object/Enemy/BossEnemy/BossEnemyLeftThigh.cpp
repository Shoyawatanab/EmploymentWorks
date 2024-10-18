#include "pch.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyLeftThigh.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyLeftLeg.h"
#include "Game/DetectionCollision/CollisionManager.h"


void BossEnemyLeftThigh::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
	BossEnemyBase::RegistrationCollionManager(collsionManager);

}

void BossEnemyLeftThigh::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{

	switch (PartnerTag)
	{
		case CollsionObjectTag::Boomerang:


			break;
		default:
			break;
	}

}

// コンストラクタ
BossEnemyLeftThigh::BossEnemyLeftThigh(CommonResources* resources, IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	BossEnemyBase(resources,parent,initialScale, positonFromParent, initialAngle),
	m_currentPosition{},
	m_currentAngle{},
	m_BossEnemyLeftThighParts{},
	m_worldMatrix{},
	m_BossEnemyLeftThighCenter{}
{
}

// デストラクタ
BossEnemyLeftThigh::~BossEnemyLeftThigh()
{
	Finalize();
}

// 初期化する
void BossEnemyLeftThigh::Initialize()
{
	using namespace DirectX::SimpleMath;


	auto device = BossEnemyBase::GetResources()->GetDeviceResources()->GetD3DDevice();
	

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BossEnemyThigh.cmo", *fx);

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
	BossEnemyBase::CreateBounding(m_currentPosition - Vector3(0, 0, 0), m_currentAngle, Vector3(0.41f, 0.55f, 0.41f) * m__currentScale, 1.0f * m__currentScale.x);


	//アニメーションの生成　引数　大きさ　座標　回転　時間
	std::vector<BossEnemyBase::AnimationKeyFrame> animation;
	////test
	//animation.push_back({ Vector3(1, 1, 1), Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity, 0.0f });            //初期値
	//animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0),
	//	DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(-90),DirectX::XMConvertToRadians(0))
	//	, 0.8f });            //足の振り上げ
	//animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0),
	//	DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(-90),DirectX::XMConvertToRadians(0))
	//	, 2.0f });            //溜め時間
	//animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0.5f),
	//	DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(-20),DirectX::XMConvertToRadians(0))
	//	, 0.5f });            //おろす


	////アニメーションを登録
	//BossEnemyBase::SetAnimations(animation, "LeftFootStep");



	animation.push_back({ Vector3(1, 1, 1), Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity, 0.0f });            //初期値
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0),
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(-70),DirectX::XMConvertToRadians(0))
		, 0.2f });            //足の振り上げ
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0),
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(-70),DirectX::XMConvertToRadians(0))
		, 0.2f });            //溜め時間
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0.0f),
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0))
		, 0.2f });            //おろす

	animation.push_back({ Vector3(1, 1, 1), Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity, 0.5f });     

	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0),
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0))
		, 0.2f });            //足の振り上げ
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0),
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0))
		, 0.2f });            //溜め時間
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0.0f),
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0))
		, 0.2f });            //おろす


	//アニメーションを登録
	BossEnemyBase::SetAnimations(animation, "Run");


	

	//「LeftLeg」を生成する
	Attach(std::make_unique<BossEnemyLeftLeg>(BossEnemyBase::GetResources(), this, BossEnemyBase::GetInitialScale(), Vector3(0.0f, -0.6f, 0.0f), Quaternion::Identity));

}


// 更新する
void BossEnemyLeftThigh::Update(const float& elapsdTime)
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
	m_currentPosition = (rotatedPosition * BossEnemyBase::GetParent()->GetScale()) + BossEnemyBase::GetParent()->GetPos();

	//バウンディングの座標の更新
	BossEnemyBase::BoundingUdate(m_currentPosition - Vector3(0, 0.0f, 0), m_currentAngle);


	// 砲塔部品を更新する
	BossEnemyBase::Update(elapsdTime);
}

// 描画する
void BossEnemyLeftThigh::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
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
void BossEnemyLeftThigh::Finalize()
{
	// 削除する部品をリセットする
	m_BossEnemyLeftThighParts.clear();
}

// 砲弾をチャージする
void BossEnemyLeftThigh::ChargeBullets()
{
}

// 砲塔境界球を作成する
DirectX::BoundingSphere BossEnemyLeftThigh::CreateBoundingSphere(const float& radius)
{
	// 境界球を宣言する
	DirectX::BoundingSphere BossEnemyLeftThighBoundingSphere;
	// 境界球の半径を設定する
	BossEnemyLeftThighBoundingSphere.Radius = radius;
	// 境界球を返す
	return BossEnemyLeftThighBoundingSphere;
}

