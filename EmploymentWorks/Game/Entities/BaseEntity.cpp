#include "pch.h"
#include "BaseEntity.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


int BaseEntity::m_nextId = 0;

/// <summary>
/// 親の登録
/// </summary>
/// <param name="parent">親</param>
void BaseEntity::SetParent(BaseEntity* parent)
{
	m_parent = parent;

	//親子関係を結んぶ
	if (parent)
	{
		
		m_localScale = m_scale;
		m_localPosition = m_position;
		m_localRotation = m_rotation;

	}
	//親子関係を解除する
	else
	{

		m_worldMatrix.Decompose(m_scale, m_rotation, m_position);

	}

}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
BaseEntity::BaseEntity(CommonResources* resources
	, const DirectX::SimpleMath::Vector3& scale
	, const DirectX::SimpleMath::Vector3& position
	, const DirectX::SimpleMath::Quaternion& rotation)
	:
	m_commonResources{resources}
	,m_scale{scale}
	,m_position{position}
	,m_rotation{rotation}
	, m_worldMatrix{}
	,m_localMatrix{}
	,m_localScale{}
	,m_localPosition{}
	,m_localRotation{}
	,m_parent{}
	,m_isEntityActive{true}
	,m_isUpdateActive{true}
	,m_isRenderActive{true}
{

	m_id = m_nextId;

	m_nextId++;

}

/// <summary>
/// デストラクタ
/// </summary>
BaseEntity::~BaseEntity()
{
}

/// <summary>
/// 初期化
/// </summary>
void BaseEntity::Initialize()
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BaseEntity::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void BaseEntity::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);

	//親あり
	if (m_parent)
	{

		//ローカル行列の計算
		m_localMatrix = Matrix::CreateScale(m_localScale)
			* Matrix::CreateFromQuaternion(m_localRotation)
			* Matrix::CreateTranslation(m_localPosition);

		//ワールド行列の計算　親があれば親の行列も加算
		m_worldMatrix = m_localMatrix * m_parent->GetWorldMatrix() ;

		//ワールド行列から大きさ　回転　座標の取得
		m_worldMatrix.Decompose(m_scale, m_rotation, m_position);


	}
	//親なし
	else
	{

		//ローカル行列の計算
		m_localMatrix = Matrix::CreateScale(m_scale)
			* Matrix::CreateFromQuaternion(m_rotation)
			* Matrix::CreateTranslation(m_position);

		//ローカル行列をワールド行列に
		m_worldMatrix =  m_localMatrix;

	}


}

