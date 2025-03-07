#include "pch.h"
#include "Boomerang.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"

#include "Libraries/WataLib/Bounding.h"
#include "Libraries/WataLib/CSV.h"
#include "Game/CollisiionManager.h"
#include "Game/Weapon/Boomerang/State/BoomerangStateMachine.h"
#include "Game/Player/Player.h"
#include "Game/Params.h"

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
	, BaseEntity* parent,
	DirectX::SimpleMath::Vector3 scale,
	DirectX::SimpleMath::Vector3 position,
	DirectX::SimpleMath::Quaternion rotation)
	:
	m_parent{parent}
	,m_initialScale{scale}
	,m_initialPosition{position}
	,m_initialRotation{rotation}
	,m_stateMachine{}
	,m_throwbasePosition{}
	,m_prevPosition{}
	,ItemEntity(resources,scale,position,rotation)
{

	m_stateMachine = std::make_unique<BoomerangStateMachine>();

	m_shadow = std::make_unique<WataLib::Shadow>();

	BaseEntity::SetParent(parent);
}

/// <summary>
/// デストラクタ
/// </summary>
Boomerang::~Boomerang()
{
}

void Boomerang::OnAcquired()
{

	m_stateMachine->ChangeState(m_stateMachine->GetBoomerangIdel());

}

/// <summary>
/// 必要なポインタの追加
/// </summary>
/// <param name="player">プレイヤ</param>
/// <param name="targetMarker">ターゲットマーカー</param>
/// <param name="tpsCamera">TPSカメラ</param>
void Boomerang::AddPointer(Player* player, TargetMarker* targetMarker, WataLib::TPS_Camera* tpsCamera)
{

	m_stateMachine->AddPointer(this,player,targetMarker,tpsCamera);

}

/// <summary>
/// 初期化
/// </summary>
void Boomerang::Initialize()
{
	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();

	ItemEntity::Initialize();

	//// モデルを読み込む準備
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	//// モデルを読み込む
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Boomerang.cmo", *fx);

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


	m_stateMachine->Render(view, projection);


	DirectX::SimpleMath::Vector3 shadowPos = BaseEntity::GetPosition();
	shadowPos.y = 0.1f;


	if (m_stateMachine->GetCurrentState() != m_stateMachine->GetBoomerangIdel())
	{
		// 自機の影を描画する
		m_shadow->Render(context, states, view, projection, shadowPos, 0.5f);

	}

	m_prevPosition = BaseEntity::GetPosition();

}

/// <summary>
/// 当たった時に呼び出される関数
/// </summary>
/// <param name="object">相手のオブジェクト</param>
/// <param name="tag">相手のタグ</param>
void Boomerang::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{

	switch (tag)
	{
		case CollisionEntity::CollisionTag::Stage:
			if (m_stateMachine->GetCurrentState() == m_stateMachine->GetBoomerangRepelled())
			{
				m_stateMachine->ChangeState(m_stateMachine->GetBoomerangDrop());

			}
			break;
		case CollisionEntity::CollisionTag::Enemy:
			break;
		case CollisionEntity::CollisionTag::EnemyParts:
			break;
		case CollisionEntity::CollisionTag::Barrier:
			m_stateMachine->ChangeState(m_stateMachine->GetBoomerangRepelled());
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
	ItemEntity::Update(elapsedTime);

	m_stateMachine->Update(elapsedTime);


}


