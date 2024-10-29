#include "pch.h"
#include "Game/Player/Player.h"
//#include "PlayScene.h"
#include "Game/Player/PlayerBody.h"

// コンストラクタ
Player::Player(CommonResources* resources,IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	PlayerBase(resources,parent, this, initialScale,DirectX::SimpleMath::Vector3::Zero, initialAngle),
	m__currentScale{initialScale},
	m_currentPosition{initialPosition},
	m_currentAngle{initialAngle},
	m_PlayerParts{},
	m_worldMatrix{},
	m_PlayerCenter{}
{
}

// デストラクタ
Player::~Player()
{
	Finalize();
}

// 初期化する
void Player::Initialize()
{
	using namespace DirectX::SimpleMath;

	//「Body」を生成する
	Attach(std::make_unique<PlayerBody>(PlayerBase::GetResources(), this, PlayerBase::GetInitialScale(), Vector3(0.0f, -0.6f, 0.0f), Quaternion::Identity));

	//std::vector<PlayerBase::AnimationKeyFrame> animation;

	//animation.push_back({ Vector3(1, 1, 1), Vector3::Zero, DirectX::SimpleMath::Quaternion::Identity, 0.0f });            //初期値
	//animation.push_back({ Vector3(1, 1, 1), Vector3(0,0,5),
	//	DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(15),DirectX::XMConvertToRadians(0),DirectX::XMConvertToRadians(0))
	//	, 2.8f });            //腕の振り上げ

	////アニメーションを登録
	//PlayerBase::SetAnimations(animation, "FallDown");



}



// キーボードイベントを処理する
void Player::HandleKeyboardEvent()
{
	using namespace DirectX::SimpleMath;

	// キーボードステートを取得する
	DirectX::Keyboard::State keyboardState = DirectX::Keyboard::Get().GetState();




	// [C] キーで「砲弾」をチャージする
	if (keyboardState.IsKeyDown(DirectX::Keyboard::Keyboard::C))
	{
		RegistrationRungingAnimation("FallDown");

	}



}

// 更新する
void Player::Update(const float& elapsdTime)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(elapsdTime);

	//// キーボードイベントを処理する
	HandleKeyboardEvent();

	// キーボードステートを取得する
	DirectX::Keyboard::State keyboardState = DirectX::Keyboard::Get().GetState();


	//大きさを変えるとアニメーションの位置がずれるので直す
	//m_currentAngle *= Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(0.1f), 0, DirectX::XMConvertToRadians(0.0f));
	//m_currentPosition.z += 0.01f;

	if (PlayerBase::AnimationUdate(elapsdTime) == AnimationStage::Runngin)
	{
		m_currentPosition.y -= 0.45f * elapsdTime;
		m_currentPosition.z += 0.5f * elapsdTime;
	}

	//m_currentPosition += PlayerBase::GetAnimationPosition();

	if (keyboardState.IsKeyDown(DirectX::Keyboard::Keyboard::D))
	{
	}

	// 砲塔部品を更新する
	PlayerBase::Update(elapsdTime);
}

// 描画する
void Player::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	// 砲塔部品を描画する
	PlayerBase::Render(view, projection);
}

// 後処理を行う
void Player::Finalize()
{
	// 削除する部品をリセットする
	m_PlayerParts.clear();
}

// 砲塔境界球を作成する
DirectX::BoundingSphere Player::CreateBoundingSphere(const float& radius)
{
	// 境界球を宣言する
	DirectX::BoundingSphere PlayerBoundingSphere;
	// 境界球の半径を設定する
	PlayerBoundingSphere.Radius = radius;
	// 境界球を返す
	return PlayerBoundingSphere;
}

