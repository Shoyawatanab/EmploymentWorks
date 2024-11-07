#include "pch.h"
#include "Game/Object/Player/PlayerParts/PlayerLeftFeet.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Libraries/MyLib/Animation.h"




void PlayerLeftFeet::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	UNREFERENCED_PARAMETER(PartnerTag);
	UNREFERENCED_PARAMETER(Pos);
}

// コンストラクタ
PlayerLeftFeet::PlayerLeftFeet(CommonResources* resources, IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	PlayerBase(resources, parent, initialScale, positonFromParent, initialAngle),
	m_currentPosition{},
	m_currentAngle{},
	m_PlayerLeftFeetParts{},
	m_worldMatrix{},
	m_PlayerLeftFeetCenter{}
{
}

// デストラクタ
PlayerLeftFeet::~PlayerLeftFeet()
{
	Finalize();
}

// 初期化する
void PlayerLeftFeet::Initialize()
{
	using namespace DirectX::SimpleMath;


	auto device = PlayerBase::GetResources()->GetDeviceResources()->GetD3DDevice();
	

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/PlayerFeet.cmo", *fx);

	//現在の大きさを更新　このクラスの大きさと親の大きさ
	m__currentScale = PlayerBase::GetParent()->GetScale();
	//現在の回転を更新　このクラスの回転と親の回転
	m_currentAngle = PlayerBase::GetInitialAngle() * PlayerBase::GetAnimationRotation() * PlayerBase::GetParent()->GetAngle();
	//回転から座標を計算する
	Vector3 rotatedPosition = Vector3::Transform(PlayerBase::GetPositonFromParent() + PlayerBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(PlayerBase::GetParent()->GetAngle()));
	//現在の座標を更新　このクラスの座標と親の座標 大きさを変えても距離を変えないようにScaleをかける
	m_currentPosition = (rotatedPosition * PlayerBase::GetParent()->GetScale()) + PlayerBase::GetParent()->GetPosition();

	PlayerBase::Initialize(std::move(m_model));

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
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(-45),DirectX::XMConvertToRadians(0))
		, 0.5f });            //腕の振り上げ
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 0.5f });            //初期値
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(45),DirectX::XMConvertToRadians(0))
		, 0.5f });            //溜め時間
	keyFram.push_back({ DirectX::SimpleMath::Quaternion::Identity, 0.5f });            //初期値

	//アニメーションクラスの作成
	animation = std::make_unique<Animation>();
	//アニメーションKeyFramの登録
	animation->SetAnimation(keyFram, Animation::AnimationPlayBackType::Loop);

	PlayerBase::SetAnimations(std::move(animation), "Walk");





	

}


// 更新する
void PlayerLeftFeet::Update(const float& elapsdTime)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(elapsdTime);
	//現在の大きさを更新　このクラスの大きさと親の大きさ
	m__currentScale = PlayerBase::GetParent()->GetScale();
	//現在の回転を更新　このクラスの回転と親の回転
	m_currentAngle = PlayerBase::GetInitialAngle() * PlayerBase::GetAnimationRotation() * PlayerBase::GetParent()->GetAngle();
	//回転から座標を計算する
	Vector3 rotatedPosition = Vector3::Transform(PlayerBase::GetPositonFromParent() + PlayerBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(PlayerBase::GetParent()->GetAngle()));
	//現在の座標を更新　このクラスの座標と親の座標 大きさを変えても距離を変えないようにScaleをかける
	m_currentPosition = (rotatedPosition * PlayerBase::GetParent()->GetScale()) + PlayerBase::GetParent()->GetPosition();



	// 砲塔部品を更新する
	PlayerBase::Update(elapsdTime);
}

// 描画する
void PlayerLeftFeet::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
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
void PlayerLeftFeet::Finalize()
{
	// 削除する部品をリセットする
	m_PlayerLeftFeetParts.clear();
}

// 砲弾をチャージする
void PlayerLeftFeet::ChargeBullets()
{
}

// 砲塔境界球を作成する
DirectX::BoundingSphere PlayerLeftFeet::CreateBoundingSphere(const float& radius)
{
	// 境界球を宣言する
	DirectX::BoundingSphere PlayerLeftFeetBoundingSphere;
	// 境界球の半径を設定する
	PlayerLeftFeetBoundingSphere.Radius = radius;
	// 境界球を返す
	return PlayerLeftFeetBoundingSphere;
}

