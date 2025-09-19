/*
	�N���X��     : EnemyManager
	����         : �G�̃}�l�[�W���[
	�⑫�E���ӓ_ : 
*/
#pragma once
#include "GameBase/Actor.h"

class Player;

class EnemyManager : public Actor
{
public:

	//�S�Ă̓G��Ԃ�
	std::vector<Actor*> GetAllEnemys() { return m_enemys; }
	//����̓G�̎擾
	std::vector<Actor*> GetEnemys(Actor::ObjectTag tag);

	//�^�[�Q�b�g�̓G�̎擾
	std::vector<Actor*> GetTargets() { return m_targets; }

public:
	//�R���X�g���N�^
	EnemyManager(Scene* scene, Player* player);
	//�f�X�g���N�^
	~EnemyManager() override;
	//�G�̎��S
	void DeathEnemy(Actor* enemy);
	//�^�[�Q�b�g�̒ǉ�
	void AddTargets(std::vector<Actor*> targets);

private:

	//�f�[�^�̓ǂݍ���
	void LoadData();


private:


	//�G�z��
	std::vector<Actor*> m_enemys;
	//�v���C��
	Player* m_player;
	//�^�[�Q�b�gActor�z��@�^�[�Q�b�g�}�[�J�[�Ŏg�p
	std::vector<Actor*> m_targets;

};