#include "pch.h"
#include "Boomerang.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/WataLib/GameResources.h"

#include "Libraries/WataLib/Bounding.h"
#include "Libraries/WataLib/CSV.h"
#include "GameBase/Manager/CollisiionManager.h"
#include "Game/Weapon/Boomerang/State/BoomerangStateMachine.h"
#include "Game/Player/Player.h"
#include "Game/Params.h"
#include "Game/Observer/Messenger.h"
#include "Game/InstanceRegistry.h"

using namespace DirectX::SimpleMath;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="parent">親</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
Boomerang::Boomerang(CommonResources* resources
	, BaseEntity* parent
	, const DirectX::SimpleMath::Vector3& scale
	, const DirectX::SimpleMath::Vector3& position
	, const DirectX::SimpleMath::Quaternion& rotation)
	:
	m_parent{parent}
	,m_initialScale{scale}
	,m_initialPosition{position}
	,m_initialRotation{rotation}
	,m_stateMachine{}
	,m_throwbasePosition{}
	,m_prevPosition{}
	,ItemEntity(resources,scale,position,rotation)
	,m_isCatch{}
{

	InstanceRegistry::GetInstance()->Register<Boomerang>("Boomerang",this);

	m_stateMachine = std::make_unique<BoomerangStateMachine>(this);

	m_shadow = std::make_unique<WataLib::Shadow>();

	BaseEntity::SetParent(parent);
	CollisionEntity::SetIsCollisionActive(false);
	BaseEntity::SetIsGravity(false);
}

/// <summary>
/// デストラクタ
/// </summary>
Boomerang::~Boomerang()
{
}

/// <summary>
/// 回収したとき
/// </summary>
void Boomerang::OnAcquired()
{

	m_stateMachine->ChangeState(m_stateMachine->GetBoomerangIdel());

}



/// <summary>
/// 初期化
/// </summary>
void Boomerang::Initialize()
{


	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();

	ItemEntity::Initialize();


	//// モデルを読み込む
	m_model = ItemEntity::GetCommonResources()->GetGameResources()->GetModel("Boomerang");

	//CSVから基準座標の取得
	m_throwbasePosition = WataLib::CSV::LoadCSVBoomerang();

	m_stateMachine->Initialize(BaseEntity::GetCommonResources(), m_stateMachine->GetBoomerangIdel());



	//ワールド行列の計算
	BaseEntity::SetWorldMatrix(Matrix::CreateScale(BaseEntity::GetScale()) *
		Matrix::CreateFromQuaternion(BaseEntity::GetRotation()) *
		Matrix::CreateTranslation(BaseEntity::GetPosition()));

	//親子関係があれば親の行列の計算を行う
	if (m_parent)
	{
		BaseEntity::SetWorldMatrix(BaseEntity::GetWorldMatrix() * m_parent->GetWorldMatrix());
	}

	Vector3 position;
	Vector3 scale;
	Quaternion rotation;

	Matrix matrix =  BaseEntity::GetWorldMatrix();
	matrix.Decompose(scale, rotation, position);


	//当たり判定の作成
	CollisionEntity::GetBounding()->CreateBoundingSphere(position, Params::BOOMERANG_SPHERE_COLLIDER_SIZE);
	CollisionEntity::GetBounding()->CreateBoundingBox(position, Params::BOOMERANG_BOX_COLLIDER_SIZE);

	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();

	m_shadow->Initialize(device, context, states);



}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void Boomerang::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();


	ItemEntity::Render(view, projection);

	//モデルの描画
	m_model->Draw(context, *states, BaseEntity::GetWorldMatrix(), view, projection);



	DirectX::SimpleMath::Vector3 shadowPos = BaseEntity::GetPosition();
	shadowPos.y = Params::SHADOW_POSITION_Y;


	if (m_stateMachine->GetCurrentState() != m_stateMachine->GetBoomerangIdel())
	{
		// 自機の影を描画する
		m_shadow->Render(context, states, view, projection, shadowPos, Params::BOOMERANG_SHADOW_RADIUS);

	}


}

/// <summary>
/// 当たった時に呼び出される関数
/// </summary>
/// <param name="object">相手のオブジェクト</param>
/// <param name="tag">相手のタグ</param>
void Boomerang::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{
	UNREFERENCED_PARAMETER(object);

	switch (tag)
	{
		case CollisionEntity::CollisionTag::STAGE:
			if (m_stateMachine->GetCurrentState() == m_stateMachine->GetBoomerangRepelled())
			{
				m_stateMachine->ChangeState(m_stateMachine->GetBoomerangDrop());

			}
			else if (m_stateMachine->GetCurrentState() == m_stateMachine->GetBoomerangRightThrow()
				||  m_stateMachine->GetCurrentState() == m_stateMachine->GetBoomerangLeftThrow()
				 ||  m_stateMachine->GetCurrentState() == m_stateMachine->GetBoomerangFrontThrow())
			{
				m_stateMachine->ChangeState(m_stateMachine->GetBoomerangDrop());
			}
			break;
		case CollisionEntity::CollisionTag::BARRIER:
			m_stateMachine->ChangeState(m_stateMachine->GetBoomerangRepelled());
			break;
		case CollisionEntity::CollisionTag::PLAYER:
			if (m_stateMachine->GetCurrentState() == m_stateMachine->GetBoomerangRightThrow())
			{
				Messenger::GetInstance()->Notify(GamePlayMessageType::BOOMERANG_RECOVERBLE, nullptr);
				m_isCatch = true;

			}
			break;

		default:
			break;
	}


}

void Boomerang::OnCollisionExit(CollisionEntity* object, CollisionTag tag)
{
	UNREFERENCED_PARAMETER(object);

	switch (tag)
	{
		case CollisionEntity::CollisionTag::PLAYER:			
			Messenger::GetInstance()->Notify(GamePlayMessageType::BOOMERANG_NOT_RECOVERBLE, nullptr);
			m_isCatch = false;
			break;
		default:
			break;
	}

}


/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void Boomerang::Update(const float& elapsedTime)
{

	m_prevPosition = BaseEntity::GetPosition();


	ItemEntity::Update(elapsedTime);

	m_stateMachine->Update(elapsedTime);

	if (m_isCatch)
	{
		// キーボードステートトラッカーを取得する
		const auto& kbTracker = BaseEntity::GetCommonResources()->GetInputManager()->GetKeyboardTracker();

		if (kbTracker->released.F)
		{
			m_stateMachine->ChangeState(m_stateMachine->GetBoomerangIdel());
			Messenger::GetInstance()->Notify(GamePlayMessageType::BOOMERANG_NOT_RECOVERBLE,nullptr);

		}



	}

}


