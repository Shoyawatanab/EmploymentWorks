/*
	�N���X��     : TitleSceneSound
	����         : �^�C�g���V�[���̉�
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Actor.h"

class SoundComponent;

class TitleSceneSound : public Actor
{
public:
	//�R���X�g���N
	TitleSceneSound(Scene* scene);
	//�f�X�g���N�^
	~TitleSceneSound() override;

private:
	//BGM
	SoundComponent* m_bgm;

};

