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

	Vector3 scale = Vector3(0.1f,0.1f,0.0f);
	Vector3 position = Vector3(100.0f, 360.0f,0.0f);





	auto image1 = GetScene()->AddActor<Image>(canvas, "BoomerangUI");
	image1->GetTransform()->SetParent(GetTransform());

	image1->GetTransform()->SetScale(Vector3(0.2f, 0.2f,0.0f));
	image1->GetTransform()->SetPosition(Vector3(0.0f, 100.0f,0.0f));


	auto image2 = GetScene()->AddActor<Image>(canvas, "BoomerangUI");
	image2->GetTransform()->SetParent(GetTransform());

	image2->GetTransform()->SetScale(Vector3(0.2f, 0.2f, 0.0f));
	image2->GetTransform()->SetPosition(Vector3(0.0f, -100.0f, 0.0f));



	GetTransform()->SetScale(scale);
	GetTransform()->SetPosition(position);

}

/// <summary>
/// デストラクタ
/// </summary>
PlayerHp::~PlayerHp()
{
}
