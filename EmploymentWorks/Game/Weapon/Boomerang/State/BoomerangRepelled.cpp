
#include "pch.h"
#include "BoomerangRepelled.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "BoomerangRepelled.h"

const DirectX::SimpleMath::Vector3 GENERATEDISTANCE(0.5f, 0.8f, 0.0f);


/// <summary>
/// コンストラクタ
/// </summary>
BoomerangRepelled::BoomerangRepelled()
	:
	m_worldMatrix{},
	m_boomerang{ }
	,m_pwoer{}
{
}

/// <summary>
/// デストラクタ
/// </summary>
BoomerangRepelled::~BoomerangRepelled()
{

}

/// <summary>
/// 初期化
/// </summary>
/// <param name="resources">共通リソース</param>
void BoomerangRepelled::Initialize(CommonResources* resources)
{
	UNREFERENCED_PARAMETER(resources);
}


/// <summary>
/// 更新処理
/// </summary>
/// <param name="elapsedTime">経過時間</param>
void BoomerangRepelled::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	m_position = m_boomerang->GetPosition();
	m_position += m_direction * elapsedTime;

	m_position.y -= m_graivty * elapsedTime;

	m_boomerang->SetPosition(m_position);

	m_worldMatrix = Matrix::CreateScale(m_boomerang->GetScale());
	m_worldMatrix *= Matrix::CreateTranslation(m_boomerang->GetPosition());

	m_graivty += 5.5f * elapsedTime;

}

void BoomerangRepelled::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	UNREFERENCED_PARAMETER(view);
	UNREFERENCED_PARAMETER(projection);

}

/// <summary>
/// 状態に入った時
/// </summary>
void BoomerangRepelled::Enter()
{
	m_boomerang->SetIsCollisionActive(true);

	m_position = m_boomerang->GetPosition();

	m_direction = m_boomerang->GetPrevPosition();

	m_pwoer = 2.0f;

	//上か下か
	if (m_direction.y <= 0)
	{
		//下からあたった
		m_graivty = -0.02f;
	}
	else
	{
		//上からあたった
		m_graivty = 0;
	}



	//m_direction.z *= -1;

	m_direction.Normalize();
	m_position += m_direction;
}

/// <summary>
/// 状態を抜けた時
/// </summary>
void BoomerangRepelled::Exit()
{

}

void BoomerangRepelled::AddPointer(Boomerang* boomerang)
{
	m_boomerang = boomerang;

}

