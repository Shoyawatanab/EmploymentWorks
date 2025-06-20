#include "pch.h"
#include "DamageCountFactory.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "Game/UI/PlayScene/DamageCount/DamageCount.h"
#include "GameBase/Scene/Scene.h"


DamageCountFactory::DamageCountFactory(Canvas* canvas)
	:
	Actor(canvas->GetScene())
{
	//’è”•¶–‘O‚Éì¬
	for (int i = 0; i < 5; i++)
	{
		auto a = GetScene()->AddActor<DamageCount>(canvas);
	}

}

DamageCountFactory::~DamageCountFactory()
{
}
