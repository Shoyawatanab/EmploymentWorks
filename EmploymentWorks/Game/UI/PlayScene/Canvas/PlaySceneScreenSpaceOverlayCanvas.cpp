#include "pch.h"
#include "PlaySceneScreenSpaceOverlayCanvas.h"
#include "GameBase/Scene/Scene.h"
#include "Game/UI/PlayScene/PlaySceneUIs.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="scene">�V�[��</param>
PlaySceneScreenSpaceOverlayCanvas::PlaySceneScreenSpaceOverlayCanvas(Scene* scene, std::vector<Actor*> targets)
	:
	ScreenSpaceOverlayCanvas(scene)
	,m_targetMarker{}
{

	//PlyerHp�̍쐬
	auto playerHp = GetScene()->AddActor<PlayerHp>(this);

	m_targetMarker = GetScene()->AddActor<TargetMarker>(this,targets);

	GetScene()->AddActor<BoomerangCount>(this);

	GetScene()->AddActor<DamageCountFactory>(this);

	GetScene()->AddActor<BossHp>(this);

	GetScene()->AddActor<PlayerDamageEffect>(this);

	GetScene()->AddActor<GameOverUI>(this);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlaySceneScreenSpaceOverlayCanvas::~PlaySceneScreenSpaceOverlayCanvas()
{
}



