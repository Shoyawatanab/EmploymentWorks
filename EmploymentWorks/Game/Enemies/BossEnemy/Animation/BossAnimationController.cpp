/*
	�N���X��     : BossAnimationController
	����         : �{�X�G�̃A�j���[�V�����R���g���[���[
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "BossAnimationController.h"
#include "Game/Component/Components.h"
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
	AddAnimatoin(bossEnemy,"BeamAttack","Resources/Json/BossEnemyData/Animation/BeamAttack.json",data);
	AddAnimatoin(bossEnemy,"BeamAttackEnd","Resources/Json/BossEnemyData/Animation/BeamAttackEnd.json",data);
	


	//�J�ڃp�����[�^�[�̍쐬   ��ԑJ�ڎ��Ɏg�p���閼�O
	CrateTransitionParameter({
		{"Move",             ExecutionState::FLOAT}
		,{"SwingDown",       ExecutionState::TRIIGER}
		,{"JumpCharge",      ExecutionState::TRIIGER}
		,{"BeamEnd",      ExecutionState::TRIIGER}
		});

	//��l�X�s�[�h
	float speed = 0.01f;

	//��ԑJ�ڃt���[�̍쐬�@�@�@�@�@�@�A�j���[�V�������@�@�@�@�@�J�ږ��@�@�@�J�ږ��ɏd�����Ȃ��悤��
	CreateAnyStateToTriggerTransition("BossIdle",           "Idle");
	CreateAnyStateToTriggerTransition("BossSwingDown",       "SwingDown");
	CreateAnyStateToTriggerTransition("BossJumpCharge",	      "JumpCharge");

	CreateTriggerTransition("BeamAttack", "BeamAttackEnd", "BeamEnd");



	//                    //�J�ڌ��@�@�@�J�ڐ�@�@�@�@�J�ږ� ��l�@�@��ԁ@�傫�����@��������
	CreateFloatTransition("BossIdle", "BossMove", "Move",speed, FloatState::Greater);

	//�ʒm���󂯎��R���|�[�l���g�̒ǉ�
	auto ob = bossEnemy->AddComponent<ObserverComponent<SceneMessageType>>(bossEnemy);
	//�ǂ̒ʒm���̓o�^�ƌĂяo���֐��̓o�^
	ob->Rigister(
		{
			SceneMessageType::BOSS_IDLE_STATE
			,SceneMessageType::BOSS_BEAM_ATTACK_STATE
			,SceneMessageType::BOSS_JUMP_ANIMATION_START
			,SceneMessageType::BOSS_SWING_DOWN_STATE
			,SceneMessageType::BOSS_WAKING_STATE
			,SceneMessageType::BOSS_DEFEATED
			,SceneMessageType::BOSS_BEAM_IMPACT
		}
		, std::bind(&BossAnimationController::Notify, this, std::placeholders::_1, std::placeholders::_2)
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
	UNREFERENCED_PARAMETER(datas);

	switch (type)
	{
		case SceneMessageType::BOSS_IDLE_STATE:
			Play("BossIdle");
			break;
		case SceneMessageType::BOSS_BEAM_ATTACK_STATE:
			Play("BeamAttack");
			break;
		case SceneMessageType::BOSS_JUMP_ANIMATION_START:
			SetTrigger("JumpCharge");
			break;
		case SceneMessageType::BOSS_WAKING_STATE:
			SetTrigger("Move");
			break;
		case SceneMessageType::BOSS_SWING_DOWN_STATE:
			SetTrigger("SwingDown");
			break;
		case SceneMessageType::BOSS_DEFEATED:  // �{�X��|�����Ƃ�
			Play("BossFallDown");
			break;
		case SceneMessageType::BOSS_BEAM_IMPACT:
			SetTrigger("BeamEnd");
			break;
		default:
			break;
	}


}
