/*
	�N���X��     : SelectSceneSound
	����         : �v���C�V�[���̉�
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Actor.h"

class SoundComponent;

class SelectSceneSound : public Actor
{
public:
	//�R���X�g���N
	SelectSceneSound(Scene* scene);
	//�f�X�g���N�^
	~SelectSceneSound() override;

private:
	//BGM
	SoundComponent* m_bgm;

};

