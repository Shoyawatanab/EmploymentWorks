
#include "pch.h"
#include "Game/Object/Boomerang/State/BoomerangDrop.h"
#include "Game/Object/Boomerang/Boomerang.h"

const DirectX::SimpleMath::Vector3 GENERATEDISTANCE(0.5f, 0.8f, 0.0f);

// コンストラクタ
BoomerangDrop::BoomerangDrop(Boomerang* boomerang)
	:
	m_worldMatrix{},
	m_boomerang{boomerang}
{
}

// デストラクタ
BoomerangDrop::~BoomerangDrop()
{

}

// 初期化する
void BoomerangDrop::Initialize()
{
	

}


// 更新する
void BoomerangDrop::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;



	//マトリクス　子供の計算　親の計算の順番でやらないといけない
	m_worldMatrix = Matrix::CreateScale(m_boomerang->GetScale());
	m_worldMatrix *= Matrix::CreateFromQuaternion(m_boomerang->GetRotate());
	m_worldMatrix *= Matrix::CreateTranslation(m_boomerang->GetPosition());



}


void BoomerangDrop::Enter()
{



}

void BoomerangDrop::Exit()
{

}