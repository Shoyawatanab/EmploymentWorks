#include "pch.h"
#include "ColliderComponent.h"
#include "GameBase/Actor.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Managers.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/Microsoft/DebugDraw.h"



ColliderComponent::ColliderComponent(Actor* owner, ColliderTag tag, CollisionType type)
	:
	Component(owner)
	,m_collisionTag{tag}
	,m_collisionType{type}
{
	//マネージャーの取得
	auto collisitionManager = GetActor()->GetScene()->GetCollisionManager();
	//マネージャーに追加
	collisitionManager->AddCollider(this);
	//マネージャーの取得
	auto renderManager = GetActor()->GetScene()->GetRenderMangaer();
	//マネージャーに追加
	renderManager->AddCollider(this);

}


/// <summary>
/// デストラクタ
/// </summary>
ColliderComponent::~ColliderComponent()
{
	//削除
	auto collisionManager = GetActor()->GetScene()->GetCollisionManager();
	collisionManager->RemoveCollider(this);


}

void ColliderComponent::Update(const float& deltaTime)
{

	//派生先更新処理
	UpdateCollider();

}

void ColliderComponent::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection
	,DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch, DirectX::BasicEffect* effect, ID3D11InputLayout* inputlayout)
{
	//派生先の描画処理
	RenderCollider(view, projection, batch, effect, inputlayout);
}


bool ColliderComponent::DleteHitObject(ColliderComponent* object)
{
	size_t initialSize = m_hitCollider.size();
	//オブジェクトがあれば削除
	m_hitCollider.erase(std::remove(m_hitCollider.begin(), m_hitCollider.end(), object), m_hitCollider.end());
	//削除できたかどうか
	if (m_hitCollider.size() < initialSize)
	{
		//削除できたら
		return true;
	}
	return false;
};


/// <summary>
/// 押し出し処理
/// </summary>
/// <param name="pushBack">押し出しベクトル</param>
void ColliderComponent::SetPushBack(DirectX::SimpleMath::Vector3 pushBackVector)
{
	//オブジェクトの押し出し
	GetActor()->GetTransform()->Translate(pushBackVector);
	//派生先のバウンディングの更新
	PositionUpdate();

}



/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="owner">所有者</param>
/// <param name="tag">当たり判定の種類</param>
/// <param name="type">判定の種類</param>
/// <param name="position">中心座標</param>
/// <param name="extents">バウンディングボックスの大きさ</param>
/// <param name="radius">バウンディングスフィアの大きさ</param>
AABB::AABB(Actor* owner, ColliderTag tag, CollisionType type
	, const DirectX::SimpleMath::Vector3& extents
	, const float& radius)
	:
	ColliderComponent(owner,tag,type)
{
	
	using namespace DirectX;

	//バウンディングボックスるの作成
	m_boundingBox = std::make_unique<BoundingBox>();
	//大きさの設定
	m_boundingBox->Extents = extents;

	//バウンディングスフィアの作成
	m_boundingSphere = std::make_unique<BoundingSphere>();
	//大きさの設定
	m_boundingSphere->Radius = radius;


}

AABB::~AABB()
{
}

/// <summary>
/// 個別更新処理
/// </summary>
void AABB::UpdateCollider()
{
	//座標の更新
	m_boundingBox->Center = GetActor()->GetTransform()->GetPosition();
	m_boundingSphere->Center = GetActor()->GetTransform()->GetPosition();
}


void AABB::RenderCollider(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection
	,DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch, DirectX::BasicEffect* effect, ID3D11InputLayout* inputlayout)
{

	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	effect->SetView(view);
	effect->SetProjection(projection);
	effect->Apply(context);

	auto states = CommonResources::GetInstance()->GetCommonStates();
	context->OMSetBlendState(states->Opaque(), nullptr, 0xFFFFFFFF);	// 透過しない
	context->OMSetDepthStencilState(states->DepthDefault(), 0);			// Ｚバッファを使用する
	context->RSSetState(states->CullNone());							// ポリゴンの両面を描画する
	context->IASetInputLayout(inputlayout);							// 入力レイアウトを設定する

	DirectX::XMVECTOR color = DirectX::Colors::Yellow;


#ifdef _DEBUG
	// プリミティブ描画を開始する
	batch->Begin();

	// 境界スフィアを描画する
	DX::Draw(batch, *m_boundingSphere, color);
	DX::Draw(batch, *m_boundingBox, color);
	// プリミティブ描画を終了する
	batch->End();

#endif

}

void AABB::PositionUpdate()
{
	//座標の更新
	m_boundingBox->Center = GetActor()->GetTransform()->GetPosition();
	m_boundingSphere->Center = GetActor()->GetTransform()->GetPosition();

}






