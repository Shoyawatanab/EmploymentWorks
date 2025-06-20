#include "pch.h"
#include "PlayerHp.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/UI/Image.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/Component/Components.h"

/// <summary>
/// コンストラクタ
/// </summary>
/// <param name="scene">シーン</param>
PlayerHp::PlayerHp(Canvas* canvas)
	:
	Actor(canvas->GetScene())
{

	using namespace DirectX::SimpleMath;


	auto image1 = GetScene()->AddActor<Image>(canvas, "HP");
	image1->GetTransform()->SetParent(GetTransform());

	image1->GetTransform()->SetScale(HEART_SCALE);
	image1->GetTransform()->SetPosition(-OFFSET_POSITION);

	auto image2 = GetScene()->AddActor<Image>(canvas, "HP");
	image2->GetTransform()->SetParent(GetTransform());

	image2->GetTransform()->SetScale(HEART_SCALE);
	image2->GetTransform()->SetPosition(Vector3::Zero);

	auto image3 = GetScene()->AddActor<Image>(canvas, "HP");
	image3->GetTransform()->SetParent(GetTransform());

	image3->GetTransform()->SetScale(HEART_SCALE);
	image3->GetTransform()->SetPosition(OFFSET_POSITION);


	m_heart.push_back(image1);
	m_heart.push_back(image2);
	m_heart.push_back(image3);

	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITION);


}

/// <summary>
/// デストラクタ
/// </summary>
PlayerHp::~PlayerHp()
{
}

