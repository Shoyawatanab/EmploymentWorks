
#include "pch.h"
#include "BoomerangRepelled.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "BoomerangRepelled.h"

const DirectX::SimpleMath::Vector3 GENERATEDISTANCE(0.5f, 0.8f, 0.0f);

// コンストラクタ
BoomerangRepelled::BoomerangRepelled()
	:
	m_worldMatrix{},
	m_boomerang{ }
{
}

// デストラクタ
BoomerangRepelled::~BoomerangRepelled()
{

}

void BoomerangRepelled::Initialize(CommonResources* resources)
{
}


// 更新する
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



	//m_position = m_boomerang->GetPos();
	//m_position += m_direction;

	//m_position.y -= m_graivty;

	//m_boomerang->SetPos(m_position);

	//m_worldMatrix = Matrix::CreateScale(m_boomerang->GetScale());
	//m_worldMatrix *= Matrix::CreateTranslation(m_boomerang->GetPos());


	//m_graivty += 0.005f;


}

void BoomerangRepelled::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
}


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

void BoomerangRepelled::Exit()
{

}

void BoomerangRepelled::AddPointer(Boomerang* boomerang)
{
	m_boomerang = boomerang;

}

