
#include "pch.h"
#include "BoomerangDrop.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/ItemAcquisition.h"


/// <summary>
/// コンストラクタ
/// </summary>
BoomerangDrop::BoomerangDrop(Boomerang* boomerang)
	:
	m_worldMatrix{},
	m_boomerang{boomerang}
{
}

/// <summary>
/// デストラクタ
/// </summary>
BoomerangDrop::~BoomerangDrop()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void BoomerangDrop::Initialize(CommonResources* resources)
{
	UNREFERENCED_PARAMETER(resources);

}




/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BoomerangDrop::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);


	


}

void BoomerangDrop::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);

}

/// <summary>
/// 状態に入った時
/// </summary>
void BoomerangDrop::Enter()
{
	using namespace DirectX::SimpleMath;

	ItemAcquisition::GetInstance()->AddItem(m_boomerang->GetID(), m_boomerang);


}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BoomerangDrop::Exit()
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	ItemAcquisition::GetInstance()->DeleteItem(m_boomerang->GetID());


}

