/*
	�N���X��     : ResultScene
	����         : ���U���g�V�[��
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "ResultScene.h"
#include "GameBase/Screen.h"
#include "GameBase/Common/Commons.h"
#include "Game/Component/Components.h"
#include "Game/Camera/Result/ResultCamera.h"
#include "Game/Fade/FadeManager.h"
#include "Game/Player/Model/PlayerModel.h"
#include "Game/Stage/StageFactory.h"
#include "Game/Params.h"
#include "Game/UI/ResultScene/Canvas/ResutlSceneScreenSpaceOverlayCanvas.h"


#include "Game/GlobalGameData.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
ResultScene::ResultScene()
	:
	m_isChangeScene{}
	,m_camera{}
{
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ResultScene::~ResultScene()
{
	// do nothing.
}



/// <summary>
/// ������
/// </summary>
void ResultScene::SceneInitialize()
{

	using namespace DirectX::SimpleMath;
	//�X�e�[�W�t�@�N�g���[�쐬
	AddActor<StageFactory>(this);
	
	//�J�����̍쐬
	m_camera = AddActor<ResultCamera>(this);

	AddActor<ResutlSceneScreenSpaceOverlayCanvas>(this);


	//���f���̍쐬
	auto model = AddActor<PlayerModel>(this);
	//���f���̑傫�����v���C���̐ݒ��
	model->GetTransform()->SetScale(Params::PLAYER_SCALE);
	model->GetTransform()->Translate(DirectX::SimpleMath::Vector3(-1.8f,0.5f,0));
	model->GetTransform()->SetRotate(Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(25),0,0));


	FadeManager::GetInstance()->StartFadeOut();

	GlobalGameData::GetInstance()->SetClearTime(198);

}



