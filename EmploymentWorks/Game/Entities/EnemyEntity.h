/*
* �v���C���N���X�@
*/

#pragma once
#include "CompositeEntity.h"

//�O���錾
class EnemyManager;

class EnemyEntity : public CompositeEntity
{
public:

	//�G�}�l�[�W���[�̎擾
	EnemyManager* GetEnemyManager() { return m_enemyMangaer; }
	 
public:
	//�R���X�g���N
	EnemyEntity(CommonResources* resources
		, const DirectX::SimpleMath::Vector3& scale
		, const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Quaternion& rotation);
	//�f�X�g���N�^
	~EnemyEntity() override;


	//BaseEntity
	//������
	void Initialize();
	//�X�V����
	void  Update(const float& elapsedTime)  override;
	//�`�揈��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
	//CollisionEntity
		//�����������ɌĂяo�����
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;
	//�G�}�l�[�W���[�̓o�^
	void SetManager(EnemyManager* enemyManager);

private:

	//�G�}�l�[�W���[
	EnemyManager* m_enemyMangaer;

};


