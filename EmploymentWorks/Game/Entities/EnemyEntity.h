/*
* �v���C���N���X�@
*/

#pragma once

#include "CompositeEntity.h"

class EnemyManager;

class EnemyEntity : public CompositeEntity
{
public:

	EnemyManager* GetEnemyManager() { return m_enemyMangaer; }
	 
public:

	EnemyEntity(CommonResources* resources
		, const DirectX::SimpleMath::Vector3& scale
		, const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Quaternion& rotation);

	~EnemyEntity() override;


	//BaseEntity
		//������
	void Initialize();
	//�X�V����
	void  Update(const float& elapsedTime)  override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection);
	//CollisionEntity
		//�����������ɌĂяo�����
	void OnCollisionEnter(CollisionEntity* object, CollisionTag tag) override;


	void SetManager(EnemyManager* enemyManager);

private:

	EnemyManager* m_enemyMangaer;

};


