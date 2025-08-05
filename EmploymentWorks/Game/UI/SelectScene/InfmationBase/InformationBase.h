/*
	�N���X��     : InformationBase
	����         : �Z���N�g�V�[���̉E�̏��̂܂Ƃ߃N���X
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Actor.h"
#include "Game/Messenger/Messengers.h"

class Canvas;
class Button;

class InformationBase : public Actor
{
public:
	//���W
	static constexpr DirectX::SimpleMath::Vector3 POSITION = { 1000.0f, 360.0f, 0 };
	//�傫��
	static constexpr DirectX::SimpleMath::Vector3 SCALE = { 1.0f, 1.0f, 0 };

public:
	//�R���X�g���N
	InformationBase(Canvas* canvas);
	//�f�X�g���N�^
	~InformationBase() override;

	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas);


private:

	//�X�e�[�W�ԍ�UI�̐؂�ւ�
	void ChangeStageUI(int stateNumber);

private:

	//�I�𒆂̃X�e�[�W�ԍ�
	int m_selectStageNumber;
	//�`�悵�Ă���X�e�[�W�ԍ�
	int m_drawStageNumber;

	//�X�e�[�W
	std::vector<Actor*> m_stage;


};

