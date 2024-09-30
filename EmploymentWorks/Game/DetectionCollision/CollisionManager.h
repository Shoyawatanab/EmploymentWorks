#pragma once
/*
	@file	CollisionManager.h.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "pch.h"
#include "Game/Object/Boomerang/Boomerang.h"

// �O���錾
class CommonResources;
class ICollsionObject;


namespace mylib
{
	class TPS_Camera;

}



class CollisionManager final

{
public:

	void SetTPS_Camera(mylib::TPS_Camera* camera) { m_tpsCamera = camera; }


private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	Player* m_player;
	Enemy* m_enemy;
	Boomerang* m_boomerang;

	//�����蔻��I�u�W�F�N�g�̓o�^�z�� 
	std::vector<ICollisionObject*> m_collsionObjects;

	// �|���S����Ray���Փ˂������W
	DirectX::SimpleMath::Vector3 m_hitPosition;



	//�r�[���̃o�E���f�B���O
	std::vector<Bounding> m_beamBounding;

	//�Q�[���J���� �v���C���̃J����
	mylib::TPS_Camera* m_tpsCamera;

public:
	CollisionManager();
	~CollisionManager();


	void Initialize(CommonResources* resources, Player* player, Enemy* enemy);


	void Update();

	void AddCollsion(ICollisionObject* object);

	void BoxExtrusion(ICollisionObject* Object1, ICollisionObject* Object2);

	bool CheckIsBox(ICollisionObject* Object1, ICollisionObject* Object2);

	bool CheckIsSphere(ICollisionObject* Object1, ICollisionObject* Object2);

	bool RockExtrusion(ICollisionObject* Object1, ICollisionObject* Object2);

	bool Tree1Extrusion(ICollisionObject* Object1, ICollisionObject* Object2);

	void CameraCollision(ICollisionObject* object);


private:
};
