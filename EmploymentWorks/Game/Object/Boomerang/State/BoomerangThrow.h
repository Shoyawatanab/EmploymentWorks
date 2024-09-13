#pragma once
#include <pch.h>
#include "Interface/IBoomerangState.h"
#include "Libraries/MyLib/CSV.h"

class Boomerang;
class Player;
class Enemy;


// BoomerangThrow�N���X���`����
class BoomerangThrow : public IBoomerangState
{
private:
	enum class BoomerangThrowState
	{

		SplineCurve,   //�X�v���C���Ȑ�
		ChaseToPlayer  //�v���C����ǂ�������
	};


public: 
	DirectX::SimpleMath::Matrix GetMatrix() { return m_worldMatrix; }


public:
	// �R���X�g���N�^
	BoomerangThrow();
	// �f�X�g���N�^
	~BoomerangThrow();
	// ����������
	void Initialize();

	// �X�V����
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

	//�N���X�ɕK�v�ȏ��i�|�C���^�j�̓o�^
	void RegistrationInformation(Boomerang* boomerang, Player* player, Enemy* enemy);


	void SplineCurve(const float& elapsedTime);

	void ChaseToPlayer(const float& elapsedTime);


private:

	Boomerang* m_boomerang;
	Player* m_player;
	Enemy* m_enemy;


	DirectX::SimpleMath::Quaternion m_initialRotate;
	DirectX::SimpleMath::Vector3 m_position;

	std::unique_ptr<CSV> m_csv;

	std::vector<DirectX::SimpleMath::Vector3> m_spherePos;
	std::vector<DirectX::SimpleMath::Vector3> m_moveSpherePos;
	DirectX::SimpleMath::Quaternion  m_rotate;

	DirectX::SimpleMath::Vector3 m_direction;
	DirectX::SimpleMath::Vector3 m_previousFrameDirection;

	// ���[���h�}�g���b�N�X
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// �o�E���f�B���O�X�t�B�A
	DirectX::BoundingSphere m_boundingSphereLeftLeg;

	float m_transformRatio;
	int m_index;
	float m_totalTime;
	int m_startIndex;

	float m_moveSpeed;

	float m_rotationalMotion;
	float  m_rotateY;
	DirectX::SimpleMath::Vector3 m_target;

	BoomerangThrowState m_state;


};

