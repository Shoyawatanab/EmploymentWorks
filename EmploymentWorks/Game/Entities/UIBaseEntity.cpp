#include "pch.h"
#include "UIBaseEntity.h"
#include "Game/Params.h"




/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="resources">共通リソース</param>
/// <param name="scale">大きさ</param>
/// <param name="position">座標</param>
/// <param name="rotation">回転</param>
UIBaseEntity::UIBaseEntity(CommonResources* resources)
	:
	m_commonResources{resources}
	,m_isEntityActive{true}
	,m_isUpdateActive{true}
	,m_isRenderActive{true}
{



}

/// <summary>
/// デストラクタ
/// </summary>
UIBaseEntity::~UIBaseEntity()
{
}

/// <summary>
/// 初期化
/// </summary>
void UIBaseEntity::Initialize()
{
}

/// <summary>
/// 更新
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void UIBaseEntity::Update(const float& elapsedTime)
{

	UNREFERENCED_PARAMETER(elapsedTime);




}

/// <summary>
/// 描画
/// </summary>
/// <param name="view">ビュー行列</param>
/// <param name="projection">射影行列</param>
void UIBaseEntity::Render()
{
	using namespace DirectX::SimpleMath;



}

