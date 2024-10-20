#include "pch.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyRightLeg.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyHead.h"
#include "Game/DetectionCollision/CollisionManager.h"


void BossEnemyRightLeg::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);
	BossEnemyBase::RegistrationCollionManager(collsionManager);

}

void BossEnemyRightLeg::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
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
BossEnemyRightLeg::BossEnemyRightLeg(CommonResources* resources, IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	BossEnemyBase(resources,parent,initialScale, positonFromParent, initialAngle),
	m_currentPosition{},
	m_currentAngle{},
	m_BossEnemyRightLegParts{},
	m_worldMatrix{},
	m_BossEnemyRightLegCenter{}
{
}

// デストラクタ
BossEnemyRightLeg::~BossEnemyRightLeg()
{
	Finalize();
}

// 初期化する
void BossEnemyRightLeg::Initialize()
{
	using namespace DirectX::SimpleMath;


	auto device = BossEnemyBase::GetResources()->GetDeviceResources()->GetD3DDevice();
	

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BossEnemyLeg.cmo", *fx);

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
	BossEnemyBase::CreateBounding(m_currentPosition - Vector3(0, 0.5f, 0), m_currentAngle, Vector3(0.4f, 0.55f, 0.4f) * m__currentScale, 1.0f * m__currentScale.x);


	std::vector<BossEnemyBase::AnimationKeyFrame> animation;
	//test
	animation.push_back({ Vector3(1, 1, 1), Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity, 0.0f });            //初期値
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0),
	DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(90),DirectX::XMConvertToRadians(0))
	, 1.0f });            //溜め時間
	animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,0.0f),
		DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0))
		, 2.0f });            //おろす

	//アニメーションを登録
	BossEnemyBase::SetAnimations(animation, "FallDown");


}


// 更新する
void BossEnemyRightLeg::Update(const float& elapsdTime)
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
	//回転させるとずれるから　肩のオブジェクトの中心が上に設定されているからその分のずれ
	DirectX::SimpleMath::Vector3 pos = Vector3(0, 0.5f, 0);

	pos = Vector3::Transform(pos, m_currentAngle);

	//バウンディングの座標の更新
	BossEnemyBase::BoundingUdate(m_currentPosition - pos, m_currentAngle);


	// 砲塔部品を更新する
	BossEnemyBase::Update(elapsdTime);
}

// 描画する
void BossEnemyRightLeg::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
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
void BossEnemyRightLeg::Finalize()
{
	// 削除する部品をリセットする
	m_BossEnemyRightLegParts.clear();
}

// 砲弾をチャージする
void BossEnemyRightLeg::ChargeBullets()
{
}

// 砲塔境界球を作成する
DirectX::BoundingSphere BossEnemyRightLeg::CreateBoundingSphere(const float& radius)
{
	// 境界球を宣言する
	DirectX::BoundingSphere BossEnemyRightLegBoundingSphere;
	// 境界球の半径を設定する
	BossEnemyRightLegBoundingSphere.Radius = radius;
	// 境界球を返す
	return BossEnemyRightLegBoundingSphere;
}

