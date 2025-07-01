#pragma once
#include "GameBase/Actor.h"

class ModelBase;
class EnemyManager;

class EnemyBase : public Actor
{
public:
	//�G�}�l�[�W���[�̃Z�b�g
	void SetEnemyManager(EnemyManager* manager) { m_manger = manager; }
	//�G�}�l�[�W���[�̎擾
	EnemyManager* GetEnemyManger() { return m_manger; }


	//���f���̎擾
	ModelBase* GetModel() { return m_model; }
	//���f���̃Z�b�g
	void SetModel(ModelBase* model) { m_model = model; }
	//HP�̎擾
	int GetHp() { return m_hp; }
	//HP�̃Z�b�g
	void SetHp(int hp) { m_hp = hp; }
	//�ő�Hp�̎擾
	int GetMaxHp() { return m_maxHp; }
	//HP�����̎擾
	float GetHpRatio() { return static_cast<float>(m_hp) / m_maxHp; };



public:
	//�R���X�g���N�^
	EnemyBase(Scene* scene,int hp);
	//�f�X�g���N�^
	~EnemyBase();

	//HP�̌���
	void HpDecrease(int damage);

private:
	//�G�}�l�[�W���[
	EnemyManager* m_manger;

	//HP
	int m_hp;
	//�ő�HP
	int m_maxHp;
	//���f��
	ModelBase* m_model;
};

