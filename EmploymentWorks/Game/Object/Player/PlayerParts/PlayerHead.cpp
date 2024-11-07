#include "pch.h"
#include "Game/Object/Player/PlayerParts/PlayerHead.h"
//#include "PlayScene.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include "Libraries/MyLib/Animation.h"



void PlayerHead::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	UNREFERENCED_PARAMETER(PartnerTag);
	UNREFERENCED_PARAMETER(Pos);
}

// コンストラクタ
PlayerHead::PlayerHead(CommonResources* resources, IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	PlayerBase(resources, parent, initialScale, positonFromParent, initialAngle),
	m_currentPosition{},
	m_currentAngle{},
	m_PlayerHeadParts{},
	m_worldMatrix{},
	m_PlayerHeadCenter{}
{
}

// デストラクタ
PlayerHead::~PlayerHead()
{
	Finalize();
}

// 初期化する
void PlayerHead::Initialize()
{
	using namespace DirectX::SimpleMath;


	auto device = PlayerBase::GetResources()->GetDeviceResources()->GetD3DDevice();

	// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/PlayerHead.cmo", *fx);


	//現在の大きさを更新　このクラスの大きさと親の大きさ
	m__currentScale = PlayerBase::GetParent()->GetScale();
	//現在の回転を更新　このクラスの回転と親の回転
	m_currentAngle = PlayerBase::GetInitialAngle() * PlayerBase::GetAnimationRotation() * PlayerBase::GetParent()->GetAngle();
	//回転から座標を計算する
	Vector3 rotatedPosition = Vector3::Transform(PlayerBase::GetPositonFromParent() + PlayerBase::GetAnimationPosition(), Matrix::CreateFromQuaternion(PlayerBase::GetParent()->GetAngle()));
	//現在の座標を更新　このクラスの座標と親の座標 大きさを変えても距離を変えないようにScaleをかける
	m_currentPosition = (rotatedPosition * PlayerBase::GetParent()->GetScale()) + PlayerBase::GetParent()->GetPosition();

	PlayerBase::Initialize(std::move(m_model));






}

// 更新する
void PlayerHead::Update(const float& elapsdTime)
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
void PlayerHead::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	using namespace ::DirectX::SimpleMath;

	//ワールド行列を生成
	m_worldMatrix = Matrix::CreateScale(m__currentScale);
	m_worldMatrix *= Matrix::CreateFromQuaternion(m_currentAngle);
	m_worldMatrix *= Matrix::CreateTranslation(m_currentPosition );



	//描画する
	PlayerBase::Render(m_worldMatrix, view,projection);


}

// 後処理を行う
void PlayerHead::Finalize()
{
	// 削除する部品をリセットする
	m_PlayerHeadParts.clear();
}

// 砲弾をチャージする
void PlayerHead::ChargeBullets()
{
}

// 砲塔境界球を作成する
DirectX::BoundingSphere PlayerHead::CreateBoundingSphere(const float& radius)
{
	// 境界球を宣言する
	DirectX::BoundingSphere PlayerHeadBoundingSphere;
	// 境界球の半径を設定する
	PlayerHeadBoundingSphere.Radius = radius;
	// 境界球を返す
	return PlayerHeadBoundingSphere;
}

