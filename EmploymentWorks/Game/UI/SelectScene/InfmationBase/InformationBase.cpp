/*
	�N���X��     : InformationBase
	����         : �Z���N�g�V�[���̉E�̏��̂܂Ƃ߃N���X
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "InformationBase.h"
#include "GameBase/UI/Canvas/Canvas.h"
#include "GameBase/UI/Button.h"
#include "GameBase/Scene/Scene.h"
#include "Game/Component/Components.h"
#include "Game/Messenger/Messengers.h"
#include "Game/Fade/FadeManager.h"
#include "Game/GlobalGameData.h"
#include "Game/UI/SelectScene/InfmationBase/BackGraund/InformationBackGraund.h"
#include "Game/UI/SelectScene/InfmationBase/Stage1/StageOneInformation.h"
#include "Game/UI/SelectScene/InfmationBase/Stage2/StageTwoInformation.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="canvas">�L�����o�X</param>
InformationBase::InformationBase(Canvas* canvas)
	:
	Actor(canvas->GetScene())
	,m_selectStageNumber{1}
	,m_drawStageNumber{1}
	,m_stage{}
{

	using namespace DirectX::SimpleMath;


	//�w�i
	auto backGraund = GetScene()->AddActor<InformationBackGraund>(canvas);
	backGraund->GetTransform()->SetParent(GetTransform());

	//�X�e�[�W�P�̏��
	auto stage1 = GetScene()->AddActor<StageOneInformation>(canvas);
	stage1->GetTransform()->SetParent(GetTransform());
	stage1->SetActive(true);
	m_stage.push_back(stage1);

	//�X�e�[�W�Q�̏��
	auto stage2 = GetScene()->AddActor<StageTwoInformation>(canvas);
	stage2->GetTransform()->SetParent(GetTransform());
	stage2->SetActive(false);
	m_stage.push_back(stage2);


	GetTransform()->SetPosition(POSITION);
	GetTransform()->SetScale(SCALE);

	auto ob = AddComponent<ObserverComponent<SceneMessageType>>(this);

	ob->Rigister(
		{
			SceneMessageType::STAGE_UP
			,SceneMessageType::STAGE_DOWN
		}
		, std::bind(&InformationBase::Notify, this, std::placeholders::_1, std::placeholders::_2)
	);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
InformationBase::~InformationBase()
{
}

/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
void InformationBase::Notify(SceneMessageType type, void* datas)
{
	UNREFERENCED_PARAMETER(datas);

	switch (type)
	{
		case SceneMessageType::STAGE_UP:
			//
			m_selectStageNumber++;
			m_selectStageNumber = std::min(2, m_selectStageNumber);
			//UI�̐؂�ւ�
			ChangeStageUI(m_selectStageNumber);

			break;
		case SceneMessageType::STAGE_DOWN:
			//
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
void InformationBase::ChangeStageUI(int stageNumber)
{
	//�����Ȃ���Ȃ�
	if (m_drawStageNumber == stageNumber)
	{
		return;
	}

	m_stage[m_drawStageNumber-1]->SetActive(false);

	m_stage[stageNumber -1]->SetActive(true);

	m_drawStageNumber = stageNumber;

}

