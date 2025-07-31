/*
	�N���X��     : TitleButton
	����         : �Q�[���I�[�o�[UI
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Actor.h"
#include "Game/Messenger/Messengers.h"

class Canvas;
class Image;
class Button;
class GameOverBackGraund;


class GameOverUI : public Actor
{
public:
	//�R���X�g���N
	GameOverUI(Canvas* canvas);
	//�f�X�g���N�^
	~GameOverUI() override;

	//�A�N�e�B�u�ɂȂ������ɌĂ΂��֐�
	void OnEnable() override;

	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas);


private:
	//�w�i
	GameOverBackGraund* m_backGraund;
	//
	Button* m_retryButton;
	//
	Button* m_titleButton;
};


