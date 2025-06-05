#include "pch.h"
#include "PlayerAnimationController.h"
#include "Game/Player/Player2.h"
#include "Game/Player/Model/PlayerModel.h"
#include "GameBase/Component/Components.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player"></param>
PlayerAnimationController::PlayerAnimationController(Player2* player)
	:
	AnimationController()
{
	//�p�[�c���̎擾
	auto partss = player->GetPlayerModel()->GetParts();


	//���O�ƃg�����X�t�H�[���̃y�A�̍쐬
	//�i�[�ϐ�
	std::vector<std::pair<std::string,Transform*>> data;

	for (auto& parts : partss)
	{
		//���O�ƃg�����X�t�H�[���̒ǉ�
		data.push_back(std::make_pair(parts.first,parts.second->GetTransform()));
	}
		
	


	//�eAnimation�̍쐬

	


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerAnimationController::~PlayerAnimationController()
{
}
