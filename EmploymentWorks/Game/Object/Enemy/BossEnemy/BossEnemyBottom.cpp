#include "pch.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyBottom.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyLeftThigh.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyRightThigh.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyPelvis .h"
#include "Game/DetectionCollision/CollisionManager.h"
#include "Libraries/MyLib/Animation.h"

void BossEnemyBottom::RegistrationCollionManager(CollisionManager* collsionManager)
{

	collsionManager->AddCollsion(this);
	BossEnemyBase::RegistrationCollionManager(collsionManager);
}

void BossEnemyBottom::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
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

void BossEnemyBottom::Damage(const int damage)
{

	BossEnemyBase::Damage(damage);

}

// コンストラクタ
BossEnemyBottom::BossEnemyBottom(CommonResources* resources, BossEnemyBase* parent,
	const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, 
	const DirectX::SimpleMath::Quaternion& initialAngle, int partsHp)
	:
	BossEnemyBase(resources,parent,initialScale, positonFromParent, initialAngle,partsHp),
	m_currentPosition{},
	m_currentAngle{},
	m_BossEnemyBottomParts{},
	m_worldMatrix{},
	m_BossEnemyBottomCenter{}
{
}

// デストラクタ
BossEnemyBottom::~BossEnemyBottom()
{
	Finalize();
}

// 初期化する
void BossEnemyBottom::Initialize()
{
	using namespace DirectX::SimpleMath;


	auto device = BossEnemyBase::GetResources()->GetDeviceResources()->GetD3DDevice();
	

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/BossEnemyBottom.cmo", *fx);

	//現在の大きさを更新　このクラスの大きさと親の大きさ
	m__currentScale = BossEnemyBase::GetParent()->GetScale();
	//現在の回転を更新　このクラスの回転と親の回転
	m_currentAngle = BossEnemyBase::GetInitialAngle() * BossEnemyBase::GetAnimationRotation() * BossEnemyBase::GetParent()->GetAngle();
	//回転から座標を計算する
	Vector3 rotatedPosition = Vector3::Transform(BossEnemyBase::GetPositonFromParent() + BossEnemyBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(BossEnemyBase::GetParent()->GetAngle()));
	//現在の座標を更新　このクラスの座標と親の座標 大きさを変えても距離を変えないようにScaleをかける
	m_currentPosition = (rotatedPosition * BossEnemyBase::GetParent()->GetScale()) + BossEnemyBase::GetParent()->GetPosition();
	//初期化
	BossEnemyBase::Initialize(std::move(m_model));

	//バウンディングの生成
	BossEnemyBase::CreateBounding(m_currentPosition, m_currentAngle,Vector3(1.65f, 0.5f, 1.1f)* m__currentScale ,2.5f * m__currentScale.x);

	//アニメーションの生成
	std::vector<Animation::AnimationKeyFrame> keyFram;
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 0.0f });            //初期値
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(0))
		, 1.0f});            //溜め時間
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(90),DirectX::XMConvertToRadians(0))
		, 2.0f });            //おろす
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(90),DirectX::XMConvertToRadians(0))
	, 0.5f });            //おろす


	//アニメーションクラスの作成
	auto animation = std::make_unique<Animation>();
	//アニメーションKeyFramの登録
	animation->SetAnimation(keyFram, Animation::AnimationPlayBackType::Once);
	//アニメーションの登録
	BossEnemyBase::SetAnimations(std::move(animation), "FallDown");


	//「Pelvis」を生成する
	Attach(std::make_unique<BossEnemyPelvis>(BossEnemyBase::GetResources(), this, BossEnemyBase::GetInitialScale(), Vector3(0.0f, 0.7f, 0.0f), Quaternion::Identity, BossEnemyBase::BODYHP));

	//「LeftThigh」を生成する
	Attach(std::make_unique<BossEnemyLeftThigh>(BossEnemyBase::GetResources(), this, BossEnemyBase::GetInitialScale(), Vector3(0.9f, -0.7f, 0.0f), Quaternion::Identity, BossEnemyBase::LEGHP));
	//「RightThigh」を生成する
	Attach(std::make_unique<BossEnemyRightThigh>(BossEnemyBase::GetResources(), this, BossEnemyBase::GetInitialScale(), Vector3(-0.9f, -0.7f, 0.0f), Quaternion::Identity, BossEnemyBase::LEGHP));

}


// 更新する
void BossEnemyBottom::Update(const float& elapsdTime)
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
	BossEnemyBase::BoundingUdate(m_currentPosition,m_currentAngle);

	// 砲塔部品を更新する
	BossEnemyBase::Update(elapsdTime);

}

// 描画する
void BossEnemyBottom::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
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
void BossEnemyBottom::Finalize()
{
	// 削除する部品をリセットする
	m_BossEnemyBottomParts.clear();
}

// 砲弾をチャージする
void BossEnemyBottom::ChargeBullets()
{
}

// 砲塔境界球を作成する
DirectX::BoundingSphere BossEnemyBottom::CreateBoundingSphere(const float& radius)
{
	// 境界球を宣言する
	DirectX::BoundingSphere BossEnemyBottomBoundingSphere;
	// 境界球の半径を設定する
	BossEnemyBottomBoundingSphere.Radius = radius;
	// 境界球を返す
	return BossEnemyBottomBoundingSphere;
}


