/*
	クラス名     : Player
	説明         : プレイヤ
	補足・注意点 :
*/
#include "pch.h"
#include "Player.h"
#include "GameBase/Managers.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Params.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Component/Components.h"
#include "Game/Player/Model/PlayerModel.h"
#include "Game/Player/Animation/PlayerAnimationController.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Player/PlayerUsually.h"
#include "Game/Fade/FadeManager.h"


/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">シーン</param>
Player::Player(Scene* scene)
	:
	Actor(scene)
	,m_playSceneCamera{}
	,m_rigidBody{}
	,m_usually{}
	,m_isGround{}
	,m_targetMarker{}
	,m_hp{Params::PLAYER_HP}
{

	m_rigidBody = AddComponent<RigidbodyComponent>(this);
	//当たり判定の作成
	AddComponent<AABB>(this,  CollisionType::COLLISION
	, Params::PLAYER_BOX_COLLIDER_SIZE
	, Params::PLAYER_SPHERE_COLLIDER_SIZE);


	AddComponent<RoundShadowComponent>(this, Params::PLAYER_SHADOW_RADIUS);

	m_picker = AddComponent<PickerComponent>(this, PickUpManager::PickUpType::PLAYER_PICKUP_WEAPON);
	m_picker->SetIsPickUp(true);
	m_picker->SetRecoverableFunction(std::bind(&Player::WeaponRecoverable, this));
	m_picker->SetUnrecoverableFunction(std::bind(&Player::WeaponUnrecoverable, this));

	//モデルの作成
	m_model =  GetScene()->AddActor<PlayerModel>(GetScene());
	//親子関係をセット
	m_model->GetTransform()->SetParent(GetTransform());


	//初期情報の適用
	GetTransform()->SetScale(Params::PLAYER_SCALE);
	GetTransform()->Translate(Params::PLAYER_POSITION);
	GetTransform()->SetRotate(Params::PLAYER_ROTATION);

	//ステートの作成
	m_stateMachine = std::make_unique<PlayerStateMachine>(this);

	//アニメーションコンポーネントの追加
	m_animation  = AddComponent<AnimatorComponent>(this, std::make_unique<PlayerAnimationController>(this));
	
	m_usually = std::make_unique<PlayerUsually>(this);
	
	//初期状態を
	m_lastPosition = GetTransform()->GetPosition();


}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="deltaTime"></param>
void Player::UpdateActor(const float& deltaTime)
{
	using namespace DirectX::SimpleMath;

	if (FadeManager::GetInstance()->GetIsFade())
	{
		return;
	}

	m_stateMachine->Update(deltaTime);
	m_usually->Update(deltaTime);
	//移動量の計算
	Vector3 movement = GetTransform()->GetPosition() - m_lastPosition;
	//移動量からスピードを求める
	float speed = movement.Length() / deltaTime;

	m_animation->SetFloat("Move", speed);


	//座標の保存
	m_lastPosition = GetTransform()->GetPosition();

	// キーボードステートトラッカーを取得する
	const auto& kbTracker = CommonResources::GetInstance()->GetInputManager()->GetKeyboardTracker();

	if (kbTracker->released.F)
	{
		m_picker->TryPickUp();
	}

}

/// <summary>
/// 当たった時に呼ばれる関数
/// </summary>
/// <param name="collider">相手のコライダー</param>
void Player::OnCollisionEnter(ColliderComponent* collider)
{
	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::STAGE:
			Landing();
			break;
		case Actor::ObjectTag::BEAM:
		case Actor::ObjectTag::BIRD_BULLET:
		case Actor::ObjectTag::BOSS_ENEMY_PARTS:
		{
			//ダメージエフェクト

			//通知
			SceneMessenger::GetInstance()->Notify(SceneMessageType::PLAYER_DAMAGE);
			SceneMessenger::GetInstance()->Notify(SceneMessageType::TPS_CAMERA_SHAKE);
			AddDamage();
		}
			break;
		default:
			break;
	}

}

/// <summary>
/// 当たっているときに呼び出される関数
/// </summary>
/// <param name="collider">相手のコライダー</param>
void Player::OnCollisionStay(ColliderComponent* collider)
{
	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::STAGE:
			Landing();
		break;
		default:
			break;
	}
}

/// <summary>
/// 離れた時に呼び出される関数
/// </summary>
/// <param name="collider"></param>
void Player::OnCollisionExit(ColliderComponent* collider)
{

	switch (collider->GetActor()->GetObjectTag())
	{
		case Actor::ObjectTag::STAGE:
			m_isGround = false;
			break;
		default:
			break;
	}
}

/// <summary>
/// 武器を回収できるようになった
/// </summary>
void Player::WeaponRecoverable()
{
	SceneMessenger::GetInstance()->Notify(SceneMessageType::PLAYER_PICKUP_POSSIBLE);
}

/// <summary>
/// 武器を回収できなくなったとき
/// </summary>
void Player::WeaponUnrecoverable()
{
	SceneMessenger::GetInstance()->Notify(SceneMessageType::PLAYER_PICKUP_IMPOSSIBLE);

}



/// <summary>
/// 着地したとき
/// </summary>
void Player::Landing()
{
	m_rigidBody->ResetGravity();
	m_isGround = true;
}

/// <summary>
/// ダメージを食らったとき
/// </summary>
void Player::AddDamage()
{
	//HPの減少
	m_hp--;
	//0以下にならないように
	m_hp = std::max(m_hp, 0);

	if (m_hp == 0)
	{
		//ゲームオーバーの通知
		SceneMessenger::GetInstance()->Notify(SceneMessageType::GAME_OVER);
	}

}

