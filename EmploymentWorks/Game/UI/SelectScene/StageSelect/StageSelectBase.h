/*
	�N���X��     : StageSelectBase
	����         : �Z���N�g�V�[���̃X�e�[�WUI�̂܂Ƃ߃N���X
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Actor.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"
#include "Game/Messenger/Global/GlobalMeesageType.h"

class Image;
class Canvas;


class StageSelectBase : public Actor ,public IObserver<SceneMessageType>,public IObserver<GlobalMessageType>
{
public:

	//�ő�X�e�[�W��
	static constexpr int MAX_STAGE_COUNT = 2;

public:
	//�R���X�g���N�^
	StageSelectBase(Canvas* canvas);
	//�f�X�g���N�^
	~StageSelectBase() override;

	//�ʒm���ɌĂяo�����
	void Notify(SceneMessageType type, void* datas)  override;
	void Notify(GlobalMessageType type, void* datas)  override;

private:

	//�X�e�[�W�ԍ�UI�̐؂�ւ�
	void ChangeStageUI(int stateNumber);

private:
	//�I�𒆂̃X�e�[�W�ԍ�
	int m_selectStageNumber;
	//�`�悵�Ă���X�e�[�W�ԍ�
	int m_drawStageNumber;

	//�X�e�[�WUI�@�P���珇�Ԃɓ����悤�ɂ���
	std::vector<Image*> m_stageUI;

};

