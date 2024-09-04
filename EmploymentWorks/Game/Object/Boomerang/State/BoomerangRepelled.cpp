
#include "pch.h"
#include "Game/Object/Boomerang/State/BoomerangRepelled.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player.h"

const DirectX::SimpleMath::Vector3 GENERATEDISTANCE(0.5f, 0.8f, 0.0f);

// コンストラクタ
BoomerangRepelled::BoomerangRepelled(Boomerang* boomerang)
	:
	m_worldMatrix{},
	m_boomerang{boomerang}
{
}

// デストラクタ
BoomerangRepelled::~BoomerangRepelled()
{

}

// 初期化する
void BoomerangRepelled::Initialize()
{
	


}


// 更新する
void BoomerangRepelled::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	m_position = m_boomerang->GetPos();
	m_position += m_direction ;

	m_position.y -= m_graivty;

	m_boomerang->SetPos(m_position);

	m_worldMatrix = Matrix::CreateScale(m_boomerang->GetScale());
	m_worldMatrix *= Matrix::CreateTranslation(m_boomerang->GetPos());


	m_graivty += 0.005f;

}


void BoomerangRepelled::Enter()
{

	m_position = m_boomerang->GetPos();

	//弾く方向
	m_direction = m_boomerang->GetPos() - m_boomerang->GetPreviousFramePos();

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


	m_position += m_direction;

}

void BoomerangRepelled::Exit()
{

}