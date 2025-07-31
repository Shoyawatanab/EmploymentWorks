/*
	�N���X��     : StageSelectBase
	����         : �Z���N�g�V�[���̃X�e�[�WUI�̂܂Ƃ߃N���X
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "StageSelectBase.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "Game/Component/Components.h"
#include "GameBase/Scene/Scene.h"
#include "Game/UI/SelectScene/StageSelect/StageBackGraund/StageBackGraund.h"
#include "Game/UI/SelectScene/StageSelect/StageOneImage/StageOneImage.h"
#include "Game/UI/SelectScene/StageSelect/StageTwoImage/StageTwoImage.h"
#include "Game/UI/SelectScene/StageSelect/ChangeStageArrow/LeftArrowButton.h"
#include "Game/UI/SelectScene/StageSelect/ChangeStageArrow/RightArrowButton.h"
#include "Game/GlobalGameData.h"
#include "Game/Messenger/Messengers.h"



/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
StageSelectBase::StageSelectBase(Canvas* canvas)
	:
	Actor(canvas->GetScene())
	,m_selectStageNumber{1}
	,m_drawStageNumber{1}
{
	using namespace DirectX::SimpleMath;


	//�X�e�[�W�̔w�i
	GetScene()->AddActor<StageBackGraund>(canvas);
	//�X�e�[�W�摜
	auto one = GetScene()->AddActor<StageOneImage>(canvas);
	m_stageUI.push_back(one);

	auto two = GetScene()->AddActor<StageTwoImage>(canvas);
	two->SetActive(false);
	m_stageUI.push_back(two);


	//�X�e�[�W�؂�ւ��{�^��
	GetScene()->AddActor<LeftArrowButton>(canvas);
	GetScene()->AddActor<RightArrowButton>(canvas);


	auto ob = AddComponent<ObserverComponent<SceneMessageType>>(this);

	ob->Rigister(
		{
			SceneMessageType::STAGE_UP
			,SceneMessageType::STAGE_DOWN
		}
		,std::bind(&StageSelectBase::Notify,this,std::placeholders::_1,std::placeholders::_2)
	);



}

/// <summary>
/// �f�X�g���N�^
/// </summary>
StageSelectBase::~StageSelectBase()
{


}

/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
void StageSelectBase::Notify(SceneMessageType type, void* datas)
{
	switch (type)
	{
		case SceneMessageType::STAGE_UP:
			//
			m_selectStageNumber++;
			m_selectStageNumber = std::min(MAX_STAGE_COUNT, m_selectStageNumber);
			//UI�̐؂�ւ�
			ChangeStageUI(m_selectStageNumber);
			break;
		case SceneMessageType::STAGE_DOWN:
			m_selectStageNumber--;
			m_selectStageNumber = std::max(1, m_selectStageNumber);
			//UI�̐؂�ւ�
			ChangeStageUI(m_selectStageNumber);
			break;
		default:
			break;
	}
}

/// <summary>
/// �X�e�[�W�ԍ�UI�̐؂�ւ�
/// </summary>
/// <param name="stateNumber"></param>
void StageSelectBase::ChangeStageUI(int stateNumber)
{
	//�����Ȃ�؂�ւ��Ȃ�
	if (m_drawStageNumber == stateNumber)
	{
		return;
	}

	//�`�悵�Ă���UI���A�N�e�B�u��
	m_stageUI[m_drawStageNumber-1]->SetActive(false);

	//UI���A�N�e�B�u��
	m_stageUI[stateNumber-1]->SetActive(true);

	//�ԍ��̐؂�ւ�
	m_drawStageNumber = stateNumber;

}
