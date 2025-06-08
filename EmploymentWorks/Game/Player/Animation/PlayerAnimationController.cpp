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
	std::vector<std::pair<std::string,Actor*>> data;

	for (auto& parts : partss)
	{
		//���O�ƃg�����X�t�H�[���̒ǉ�
		data.push_back(std::make_pair(parts.first,parts.second));
	}
		
	
	
	//�eAnimation�̍쐬
	AddAnimatoin(player,"PlayerIdle","Resources/Json/PlayerData/Animation/PlayerIdle.json",data,true);
	AddAnimatoin(player,"PlayerMove","Resources/Json/PlayerData/Animation/PlayerMove.json",data);
	AddAnimatoin(player,"PlayerGetReady","Resources/Json/PlayerData/Animation/PlayerBoomerangGetReady.json",data);
	AddAnimatoin(player,"PlayerThrow","Resources/Json/PlayerData/Animation/PlayerBoomerangThrow.json",data);
	
	//�J�ڃp�����[�^�[�̍쐬   ��ԑJ�ڎ��Ɏg�p���閼�O
	CrateTransitionParameter({
		{"Idle",        ExecutionState::TRIIGER}
		,{"Move",      ExecutionState::FLOAT}
		,{"GetReady",   ExecutionState::TRIIGER}
		,{"Throw",      ExecutionState::TRIIGER}
		});

	//��l�X�s�[�h
	float speed = 0.1f;

	//��ԑJ�ڃt���[�̍쐬�@�@�@�@�@�@�A�j���[�V�������@�@�@�@�@�J�ږ��@�@�@�J�ږ��ɏd�����Ȃ��悤��
	CreateAnyStateToTriggerTransition("PlayerIdle",           "Idle");
	CreateAnyStateToTriggerTransition("PlayerGetReady",       "GetReady");
	CreateAnyStateToTriggerTransition("PlayerThrow",	      "Throw");
	//                    //�J�ڌ��@�@�@�J�ڐ�@�@�@�@�J�ږ� ��l�@�@��ԁ@�傫�����@��������
	CreateFloatTransition("PlayerIdle", "PlayerMove", "Move",speed, FloatState::Greater);

	//Move����Idle����̃A���[���쐬�@���̂ق���Anystate�̃t���[�̍쐬


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
PlayerAnimationController::~PlayerAnimationController()
{
}
