/*
	�N���X��     : BossEnemy
	����         : �{�X�G�̃p�[�c�̊��N���X
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Model/ModelPartsBase.h"

class CommonResources;

class BossEnemy;
class Camera;

class BossEnemyParts : public ModelPartsBase
{
public:


	//�I�u�W�F�N�g�^�O�̎擾
	ObjectTag GetObjectTag() override { return ObjectTag::BOSS_ENEMY_PARTS; }

	//�{�X�G�̎擾
	BossEnemy* GetBossEnemy() { return m_bossEnemy; }

public:
	//�R���X�g���N�^
	BossEnemyParts(Scene* scene, std::string partsName, std::string modelName
		,int hp ,DirectX::SimpleMath::Vector3 boxColliderExtens,float sphereRadius
		,BossEnemy* boss);
	//�f�X�g���N�^
	~BossEnemyParts() override  ;

	//�����������ɌĂяo�����
	void OnCollisionEnter(ColliderComponent* collider) override;
	//HP����
	void HpDecrease(int damage);

	//�ʂ̓����������̊֐�
	virtual void OnCollisionEnterActor(ColliderComponent* collider) { UNREFERENCED_PARAMETER(collider); }

	//���ʔj�󎞂̏���
	virtual void PartsDestruction() {}

private:

	//�`��
	void Render(const Camera& camera);

private:
	//���ʃ��\�[�X
	CommonResources* m_commonResources;

	//���̃N���X
	BossEnemy* m_bossEnemy;
	//HP
	int m_hp;

};