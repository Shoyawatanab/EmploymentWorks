/*
	BehaviorTree.h
	�n��Ė�
	�r�w�C�r�A�c���[��Root�ɓ�����N���X
*/
#pragma once
#include "Interface/ICompositeNode.h"

class CommonResources;
class Root;
class Player;
class Enemy;

class ExecutionNode;
class Conditions;

class BehaviorTree
{




private:
	CommonResources* m_commonResources;

	//Root�Œ�`����ƏI�����ɃG���[���͂�
	std::unique_ptr<ICompositeNode> m_root;

	Player* m_player;
	Enemy* m_enemy;

	//���s�m�[�h�N���X
	std::unique_ptr<ExecutionNode> m_executionNode;
	//�����m�[�h�̃N���X
	std::unique_ptr<Conditions> m_conditions;


	//���݂̏��
	IBehaviorNode::State m_currentState;
public:
	BehaviorTree();
	~BehaviorTree();

	void Initialize(CommonResources* resources);
	void Update(float elapsedTime);
	void Render() ;
	void Finalize() ;

	void Create();


	//�N���X�ɕK�v�ȏ��i�|�C���^�j�̓o�^
	void RegistrationInformation(Player* player, Enemy* enemy);

};

/*����
�@���t���[�����߂���`�F�b�N����
�@���s���m�[�h������ΏI���܂ł͎��s���̂ݓ�����
 

 ���P���邩���ȓ_
 �@���̃t���[�����Ƃɂ�����H�@���t���[���ł͂Ȃ�
�@�@���̎��͎��s��������΂�����ǂ����s���Ă��������l���Ȃ���΂Ȃ�Ȃ�
  ���s���͖��t���[�����s���𓮂����ĂȂ���Έ��̃t���[���ōX�V������ł��悢

*/