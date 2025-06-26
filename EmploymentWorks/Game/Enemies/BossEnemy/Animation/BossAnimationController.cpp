#include "pch.h"
#include "BossAnimationController.h"
#include "GameBase/Component/Components.h"
#include "Game/Messenger/Scene/SceneMessages.h"
#include "Game/Enemies/BossEnemy/BossEnemy.h"
#include "Game/Enemies/BossEnemy/Model/BossEnemyModel.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="player"></param>
BossAnimationController::BossAnimationController(BossEnemy* bossEnemy)
	:
	AnimationController()
{

	//�p�[�c���̎擾
	auto partss = bossEnemy->GetModel()->GetParts();


	//���O�ƃg�����X�t�H�[���̃y�A�̍쐬
	//�i�[�ϐ�
	std::vector<std::pair<std::string,Actor*>> data;

	for (auto& parts : partss)
	{
		//���O�ƃg�����X�t�H�[���̒ǉ�
		data.push_back(std::make_pair(parts.first,parts.second));
	}
		
	
	
	//�eAnimation�̍쐬
	AddAnimatoin(bossEnemy,"BossIdle","Resources/Json/BossEnemyData/Animation/Idle.json",data,true);
	AddAnimatoin(bossEnemy,"BossMove","Resources/Json/BossEnemyData/Animation/Move.json",data);
	AddAnimatoin(bossEnemy,"BossSwingDown","Resources/Json/BossEnemyData/Animation/SwingDown.json",data);
	AddAnimatoin(bossEnemy,"BossJumpCharge","Resources/Json/BossEnemyData/Animation/JumpCharge.json",data);
	AddAnimatoin(bossEnemy,"BossFallDown","Resources/Json/BossEnemyData/Animation/FallDown.json",data);
	
	//�J�ڃp�����[�^�[�̍쐬   ��ԑJ�ڎ��Ɏg�p���閼�O
	CrateTransitionParameter({
		{"Move",             ExecutionState::FLOAT}
		,{"SwingDown",       ExecutionState::TRIIGER}
		,{"JumpCharge",      ExecutionState::TRIIGER}
		});

	//��l�X�s�[�h
	float speed = 0.01f;

	//��ԑJ�ڃt���[�̍쐬�@�@�@�@�@�@�A�j���[�V�������@�@�@�@�@�J�ږ��@�@�@�J�ږ��ɏd�����Ȃ��悤��
	CreateAnyStateToTriggerTransition("BossIdle",           "Idle");
	CreateAnyStateToTriggerTransition("BossSwingDown",       "SwingDown");
	CreateAnyStateToTriggerTransition("BossJumpCharge",	      "JumpCharge");
	//                    //�J�ڌ��@�@�@�J�ڐ�@�@�@�@�J�ږ� ��l�@�@��ԁ@�傫�����@��������
	CreateFloatTransition("BossIdle", "BossMove", "Move",speed, FloatState::Greater);

	//���b�Z�[�W�̓o�^
	SceneMessenger::GetInstance()->Rigister(
		{ 
			SceneMessageType::BOSS_IDLE_STATE
			,SceneMessageType::BOSS_BEAM_ATTACK_STATE
			,SceneMessageType::BOSS_JUMP_ATTACK_STATE
			,SceneMessageType::BOSS_SWING_DOWN_STATE
			,SceneMessageType::BOSS_WAKING_STATE
			,SceneMessageType::BOSS_DEFEATED
		}
		, this
	);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
BossAnimationController::~BossAnimationController()
{
}

/// <summary>
/// �ʒm���󂯎��֐�
/// </summary>
/// <param name="type">�ʒm�̎��</param>
/// <param name="datas">�ǉ��f�[�^</param>
void BossAnimationController::Notify(SceneMessageType type, void* datas)
{

	switch (type)
	{
		case SceneMessageType::BOSS_IDLE_STATE:
			Play("BossIdle");
			break;
		case SceneMessageType::BOSS_BEAM_ATTACK_STATE:
			break;
		case SceneMessageType::BOSS_JUMP_ATTACK_STATE:
			SetTrigger("JumpCharge");
			break;
		case SceneMessageType::BOSS_WAKING_STATE:
			break;
		case SceneMessageType::BOSS_SWING_DOWN_STATE:
			SetTrigger("SwingDown");
			break;
		case SceneMessageType::BOSS_DEFEATED:  // �{�X��|�����Ƃ�
			Play("BossFallDown");
			break;
		default:
			break;
	}


}
