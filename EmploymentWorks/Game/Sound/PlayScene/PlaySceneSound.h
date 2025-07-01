#pragma once
#include "GameBase/Actor.h"

class SoundComponent;

class PlaySceneSound : public Actor
{
public:
	//�R���X�g���N
	PlaySceneSound(Scene* scene);
	//�f�X�g���N�^
	~PlaySceneSound() override;

private:
	//BGM
	SoundComponent* m_bgm;

};

