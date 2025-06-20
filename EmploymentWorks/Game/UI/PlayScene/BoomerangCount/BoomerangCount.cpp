#include "pch.h"
#include "BoomerangCount.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Image.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Component/Components.h"

BoomerangCount::BoomerangCount(Canvas* canvas)
	:
	Actor(canvas->GetScene())
{
	using namespace DirectX::SimpleMath;


	//�^�񒆂�UI���[�����W�ɂȂ�悤�ɂ��Ă���

	auto image1 = GetScene()->AddActor<Image>(canvas, "BoomerangUI");
	image1->GetTransform()->SetParent(GetTransform());

	image1->GetTransform()->SetScale(BOOMERANG_SCALE);
	image1->GetTransform()->SetPosition(-OFFSET_POSITION);

	auto image2 = GetScene()->AddActor<Image>(canvas, "BoomerangUI");
	image2->GetTransform()->SetParent(GetTransform());

	image2->GetTransform()->SetScale(BOOMERANG_SCALE);
	image2->GetTransform()->SetPosition(Vector3::Zero);

	auto image3 = GetScene()->AddActor<Image>(canvas, "BoomerangUI");
	image3->GetTransform()->SetParent(GetTransform());

	image3->GetTransform()->SetScale(BOOMERANG_SCALE);
	image3->GetTransform()->SetPosition(OFFSET_POSITION);


	GetTransform()->SetScale(SCALE);
	GetTransform()->SetPosition(POSITION);


}

BoomerangCount::~BoomerangCount()
{
}
