#include "pch.h"
#include "Game/Object/Player/PlayerParts/PlayerBody.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Game/Object/Player/PlayerParts/PlayerHead.h"
#include "Game/Object/Player/PlayerParts/PlayerLeftArm.h"
#include "Game/Object/Player/PlayerParts/PlayerLeftFeet.h"
#include "Game/Object/Player/PlayerParts/PlayerRightArm.h"
#include "Game/Object/Player/PlayerParts/PlayerRightFeet.h"
#include "Libraries/MyLib/Animation.h"


void PlayerBody::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	UNREFERENCED_PARAMETER(PartnerTag);
	UNREFERENCED_PARAMETER(Pos);
}

// コンストラクタ
PlayerBody::PlayerBody(CommonResources* resources, IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	PlayerBase(resources, parent, initialScale, positonFromParent, initialAngle),
	m_currentPosition{},
	m_currentAngle{},
	m_PlayerBodyParts{},
	m_worldMatrix{},
	m_PlayerBodyCenter{}
{
}

// デストラクタ
PlayerBody::~PlayerBody()
{
	Finalize();
}

// 初期化する
void PlayerBody::Initialize()
{
	using namespace DirectX::SimpleMath;


	auto device = PlayerBase::GetResources()->GetDeviceResources()->GetD3DDevice();
	

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/PlayerBody.cmo", *fx);

	//現在の大きさを更新　このクラスの大きさと親の大きさ
	m__currentScale = PlayerBase::GetParent()->GetScale();
	//現在の回転を更新　このクラスの回転と親の回転
	m_currentAngle = PlayerBase::GetInitialAngle() * PlayerBase::GetAnimationRotation() * PlayerBase::GetParent()->GetAngle();
	//回転から座標を計算する
	Vector3 rotatedPosition = Vector3::Transform(PlayerBase::GetPositonFromParent() + PlayerBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(PlayerBase::GetParent()->GetAngle()));
	//現在の座標を更新　このクラスの座標と親の座標 大きさを変えても距離を変えないようにScaleをかける
	m_currentPosition = (rotatedPosition * PlayerBase::GetParent()->GetScale()) + PlayerBase::GetParent()->GetPosition();

	PlayerBase::Initialize(std::move(m_model));



	//「Head」を生成する
	Attach(std::make_unique<PlayerHead>(PlayerBase::GetResources(), this, PlayerBase::GetInitialScale(), Vector3(0.0f, 2.5f, 0.0f), 
		Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(0))));
	//「LeftArm」を生成する
	Attach(std::make_unique<PlayerLeftArm>(PlayerBase::GetResources(), this, PlayerBase::GetInitialScale(), Vector3(1.45f, 0.8f, 0.0f), 
		Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(3))));
	//「LeftFeet」を生成する
	Attach(std::make_unique<PlayerLeftFeet>(PlayerBase::GetResources(), this, PlayerBase::GetInitialScale(), Vector3(0.5f, -1.2f, 0.0f), 
		Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(0))));
	//「RightArm」を生成する
	Attach(std::make_unique<PlayerRightArm>(PlayerBase::GetResources(), this, PlayerBase::GetInitialScale(), Vector3(-1.45f, 0.8f, 0.0f),
		Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(180), DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(3))));
	//「RightFeet」を生成する
	Attach(std::make_unique<PlayerRightFeet>(PlayerBase::GetResources(), this, PlayerBase::GetInitialScale(), Vector3(-0.5f, -1.2f, 0.0f), 
		Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(0), DirectX::XMConvertToRadians(0))));




	

}


// 更新する
void PlayerBody::Update(const float& elapsdTime)
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
void PlayerBody::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
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
void PlayerBody::Finalize()
{
	// 削除する部品をリセットする
	m_PlayerBodyParts.clear();
}

// 砲弾をチャージする
void PlayerBody::ChargeBullets()
{
}

// 砲塔境界球を作成する
DirectX::BoundingSphere PlayerBody::CreateBoundingSphere(const float& radius)
{
	// 境界球を宣言する
	DirectX::BoundingSphere PlayerBodyBoundingSphere;
	// 境界球の半径を設定する
	PlayerBodyBoundingSphere.Radius = radius;
	// 境界球を返す
	return PlayerBodyBoundingSphere;
}


