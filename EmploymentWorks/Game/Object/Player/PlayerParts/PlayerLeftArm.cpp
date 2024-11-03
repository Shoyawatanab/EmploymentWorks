#include "pch.h"
#include "Game/Object/Player/PlayerParts/PlayerLeftArm.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Libraries/MyLib/Animation.h"




void PlayerLeftArm::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
}

// コンストラクタ
PlayerLeftArm::PlayerLeftArm(CommonResources* resources, IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	PlayerBase(resources, parent, initialScale, positonFromParent, initialAngle),
	m_currentPosition{},
	m_currentAngle{},
	m_PlayerLeftArmParts{},
	m_worldMatrix{},
	m_PlayerLeftArmCenter{}
{
}

// デストラクタ
PlayerLeftArm::~PlayerLeftArm()
{
	Finalize();
}

// 初期化する
void PlayerLeftArm::Initialize()
{
	using namespace DirectX::SimpleMath;


	auto device = PlayerBase::GetResources()->GetDeviceResources()->GetD3DDevice();
	

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/PlayerArm.cmo", *fx);

	//現在の大きさを更新　このクラスの大きさと親の大きさ
	m__currentScale = PlayerBase::GetParent()->GetScale();
	//現在の回転を更新　このクラスの回転と親の回転
	m_currentAngle = PlayerBase::GetInitialAngle() * PlayerBase::GetAnimationRotation() * PlayerBase::GetParent()->GetAngle();
	//回転から座標を計算する
	Vector3 rotatedPosition = Vector3::Transform(PlayerBase::GetPositonFromParent() + PlayerBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(PlayerBase::GetParent()->GetAngle()));
	//現在の座標を更新　このクラスの座標と親の座標 大きさを変えても距離を変えないようにScaleをかける
	m_currentPosition = (rotatedPosition * PlayerBase::GetParent()->GetScale()) + PlayerBase::GetParent()->GetPosition();
	PlayerBase::Initialize(std::move(m_model));



	////アニメーションの生成　引数　大きさ　座標　回転　時間


	//アニメーションの生成
	std::vector<Animation::AnimationKeyFrame> keyFram;
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 0.0f });            //初期値
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 0.5f });            //初期値

	//アニメーションクラスの作成
	auto animation = std::make_unique<Animation>();
	//アニメーションKeyFramの登録
	animation->SetAnimation(keyFram, Animation::AnimationPlayBackType::Loop);

	PlayerBase::SetAnimations(std::move(animation), "Idling");


	//アニメーションの生成
	keyFram.clear();
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 0.0f });            //初期値
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(90),DirectX::XMConvertToRadians(0))
		, 0.5f });            //腕の振り上げ
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 0.5f });            //初期値
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(-90),DirectX::XMConvertToRadians(0))
		, 0.5f });            //溜め時間
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 0.5f });            //初期値

	//アニメーションクラスの作成
	animation = std::make_unique<Animation>();
	//アニメーションKeyFramの登録
	animation->SetAnimation(keyFram, Animation::AnimationPlayBackType::Loop);

	PlayerBase::SetAnimations(std::move(animation), "Walk");

	keyFram.clear();
	//アニメーションの生成
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 0.0f });            //初期値
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(40),DirectX::XMConvertToRadians(0))
		, 0.5f });            //腕の振り上げ
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 0.5f });            //初期値
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(-40),DirectX::XMConvertToRadians(0))
		, 0.5f });            //溜め時間
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 0.5f });            //初期値

	//アニメーションクラスの作成
	animation = std::make_unique<Animation>();
	//アニメーションKeyFramの登録
	animation->SetAnimation(keyFram, Animation::AnimationPlayBackType::Once);

	PlayerBase::SetAnimations(std::move(animation), "Walks");



}


// 更新する
void PlayerLeftArm::Update(const float& elapsdTime)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(elapsdTime);

	//m_leftShoulderAngle *=  Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0.0f), DirectX::XMConvertToRadians(-0.1f), DirectX::XMConvertToRadians(0.0f));
	
	//現在の大きさを更新　このクラスの大きさと親の大きさ
	m__currentScale = PlayerBase::GetParent()->GetScale();
	//現在の回転を更新　このクラスの回転と親の回転
	m_currentAngle = PlayerBase::GetInitialAngle() * PlayerBase::GetAnimationRotation() * PlayerBase::GetParent()->GetAngle();
	//回転から座標を計算する
	Vector3 rotatedPosition = Vector3::Transform(PlayerBase::GetPositonFromParent() + PlayerBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(PlayerBase::GetParent()->GetAngle()));
	//現在の座標を更新　このクラスの座標と親の座標 大きさを変えても距離を変えないようにScaleをかける
	m_currentPosition = (rotatedPosition * PlayerBase::GetParent()->GetScale()) + PlayerBase::GetParent()->GetPosition();

	//回転させるとずれるから　肩のオブジェクトの中心が上に設定されているからその分のずれ
	DirectX::SimpleMath::Vector3 pos = Vector3(0, 0.45f, 0);

	pos = Vector3::Transform(pos, m_currentAngle);


	// 砲塔部品を更新する
	PlayerBase::Update(elapsdTime);


}

// 描画する
void PlayerLeftArm::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	using namespace ::DirectX::SimpleMath;
	//ワールド行列を生成
	m_worldMatrix = Matrix::CreateScale(m__currentScale);
	m_worldMatrix *= Matrix::CreateFromQuaternion(m_currentAngle);
	m_worldMatrix *= Matrix::CreateTranslation(m_currentPosition);

	//描画する
	PlayerBase::Render(m_worldMatrix, view,projection);

}

// 後処理を行う
void PlayerLeftArm::Finalize()
{
	// 削除する部品をリセットする
	m_PlayerLeftArmParts.clear();
}

// 砲弾をチャージする
void PlayerLeftArm::ChargeBullets()
{
}

// 砲塔境界球を作成する
DirectX::BoundingSphere PlayerLeftArm::CreateBoundingSphere(const float& radius)
{
	// 境界球を宣言する
	DirectX::BoundingSphere PlayerLeftArmBoundingSphere;
	// 境界球の半径を設定する
	PlayerLeftArmBoundingSphere.Radius = radius;
	// 境界球を返す
	return PlayerLeftArmBoundingSphere;
}

