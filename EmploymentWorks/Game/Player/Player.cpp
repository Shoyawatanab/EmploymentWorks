#include "pch.h"
#include "Player.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Player/PlayerParts/PlayerBody.h"

#include "Libraries/WataLib/Json.h"
#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Libraries/WataLib/Bounding.h"

#include "Game/Player/PlayerUsually.h"
#include "Game/CollisiionManager.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Observer/Messenger.h"

#include "Game/Params.h"



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
Player::Player(CommonResources* resources)
	:
	m_animationDatas{}
	,m_usually{}
	,m_boomerangs{}
	,m_hp{Params::PLAYER_HP}
	,CompositeEntity(resources, Params::PLAYER_SCALE,Params::PLAYER_POSITION,Params::PLAYER_ROTATION)
{
	m_usually = std::make_unique<PlayerUsually>();
	m_stateMachine = std::make_unique<PlayerStateMachine>();

	for (int i = 0; i < Params::BOOMERANG_MAX_COUNT; i++)
	{

		auto boomerang = std::make_unique<Boomerang>(resources,this,Params::BOOMERANG_SCALE,Params::BOOMERANG_POSITION,Params::BOOMERANG_ROTATION);
		m_boomerangs.push_back(std::move(boomerang));
	}
	
	m_shadow = std::make_unique<WataLib::Shadow>();

}

/// <summary>
/// デストラクタ
/// </summary>
Player::~Player()
{
}


/// <summary>
/// 必要なポインタの追加
/// </summary>
/// <param name="tpsCamera">TPSカメラ</param>
/// <param name="targetMarker">ターゲットマーカー</param>
void Player::AddPointer(WataLib::TPS_Camera* tpsCamera, TargetMarker* targetMarker)
{

	m_targetMarker = targetMarker;

	m_usually->AddPointer(this,tpsCamera);
	m_stateMachine->AddPointer(this);

	for (auto& boomerang : m_boomerangs)
	{
		boomerang->AddPointer(this, targetMarker,tpsCamera);
	}

}



/// <summary>
/// 初期化
/// </summary>
void Player::Initialize()
{

	CompositeEntity::Initialize();

	//「Body」を生成する
	AddChild(std::make_unique<PlayerBody>(
		BaseEntity::GetCommonResources(),
		this,
		Params::PLAYER_BODY_SCALE , 
		Params::PLAYER_BODY_POSITION,
		Params::PLAYER_BODY_ROTATION)
	);

	//アニメーションデータの読み込み
	std::unique_ptr<WataLib::Json> json = std::make_unique<WataLib::Json>();

	m_animationDatas["Idle"] = json->LoadAnimationData(L"Player/Idle");
	m_animationDatas["Move"] = json->LoadAnimationData(L"Player/Move");
	m_animationDatas["GetReady"] = json->LoadAnimationData(L"Player/GetReady");
	m_animationDatas["Throw"] = json->LoadAnimationData(L"Player/Throw");


	//各パーツにアニメーションを登録
	SetAnimationData("Idle", m_animationDatas,"", true);
	this->SetAnimationData("Move", m_animationDatas);
	SetAnimationData("GetReady", m_animationDatas);
	SetAnimationData("Throw", m_animationDatas);

	//初期化
	m_usually->Initialize(BaseEntity::GetCommonResources());
	m_stateMachine->Initialize(BaseEntity::GetCommonResources(), m_stateMachine->GetPlayerIdle());

	for (auto& boomerang : m_boomerangs)
	{
		boomerang->Initialize();
	}



	//当たり判定の作成
	CollisionEntity::GetBounding()->CreateBoundingSphere(BaseEntity::GetPosition(), Params::PLAYER_SPHERE_COLLIDER_SIZE);
	CollisionEntity::GetBounding()->CreateBoundingBox(BaseEntity::GetPosition(), Params::PLAYER_BOX_COLLIDER_SIZE);


	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();
	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();


	m_shadow->Initialize(device, context, states);


}




/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void Player::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	//オブジェクトか描画が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsRenderActive())
	{
		return;
	}

	CompositeEntity::Render(view, projection);


	//パーツの描画
	for (auto& part : CompositeEntity::GetParts())
	{
		part->Render(view,projection);
	}

	for (auto& boomerang : m_boomerangs)
	{
		boomerang->Render(view, projection);
	}


	DirectX::SimpleMath::Vector3 shadowPos = BaseEntity::GetPosition();
	shadowPos.y = Params::SHADOW_POSITION_Y;

	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();



	// 自機の影を描画する
	m_shadow->Render(context, states, view, projection, shadowPos, Params::PLAYER_SHADOW_RADIUS);


}

/// <summary>
/// 当たり判定クラスに追加
/// </summary>
/// <param name="collsionManager">当たり判定クラス</param>
void Player::AddCollision(CollisionManager* collsionManager)
{
	CollisionEntity::AddCollision(collsionManager);


	for (auto& boomerang : m_boomerangs)
	{
		boomerang->AddCollision(collsionManager);
	}

}

/// <summary>
/// 当たった時に呼び出される関数
/// </summary>
/// <param name="object">相手のオブジェクト</param>
/// <param name="tag">相手のタグ</param>
void Player::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{
	UNREFERENCED_PARAMETER(object);

	switch (tag)
	{
		case CollisionEntity::CollisionTag::BEAM:
		case CollisionEntity::CollisionTag::ENEYPARTS:
			m_hp--;
			//Subject::Notify(EventManager::EventTypeName::PlayerDamage);


			//プレイヤのダメージの通知
			Messenger::GetInstance()->Notify(::GameMessageType::PLAYER_DAMAGE);
			

			if (m_hp <= 0)
			{
				//Subject::Notify(EventManager::EventTypeName::GameOver);
				Messenger::GetInstance()->Notify(::GameMessageType::GAME_OVER);
			}
			break;
		default:
			break;
	}



}


void Player::OnCollisionStay(CollisionEntity* object, CollisionTag tag)
{
	UNREFERENCED_PARAMETER(object);

	switch (tag)
	{
		case CollisionEntity::CollisionTag::STAGE:
		{
			Vector3 velocity = BaseEntity::GetVelocity();

			velocity.y = 0.0f;

			BaseEntity::SetVelocity(velocity);
		}
		break;
		default:
			break;
	}



}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void Player::Update(const float& elapsedTime)
{

	//オブジェクトか更新が無効なら
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}

	m_stateMachine->Update(elapsedTime);

	m_usually->Update(elapsedTime);

	CompositeEntity::Update(elapsedTime);


	//パーツの更新
	for (auto& part : CompositeEntity::GetParts())
	{
		part->Update(elapsedTime);
	}

	for (auto& boomerang : m_boomerangs)
	{
		boomerang->Update(elapsedTime);
	}

}



/// <summary>
/// アニメーションの登録
/// </summary>
/// <param name="animationType">アニメーションの種類</param>
/// <param name="datas">アニメーションデータ</param>
/// <param name="isNormalAnimation">通常アニメーションかどうか</param>
void Player::SetAnimationData(std::string animationType
	, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas
	, const std::string& partsName
	, bool isNormalAnimation )
{
	CharacterEntity::SetAnimationData(animationType, datas, partsName , isNormalAnimation);

	//パーツにアニメーションを登録
	for (auto& part : CompositeEntity::GetParts())
	{
		part->SetAnimationData(animationType, datas,partsName , isNormalAnimation);
	}
}

/// <summary>
/// アニメーションの変更
/// </summary>
/// <param name="animationType">アニメーションの種類</param>
void Player::ChangeAnimation(std::string animationType)
{
	CharacterEntity::ChangeAnimation(animationType);
	//パーツのアニメーションを変更
	for (auto& part : CompositeEntity::GetParts())
	{
		part->ChangeAnimation(animationType);
	}

}




