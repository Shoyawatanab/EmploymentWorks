#pragma once
#include <pch.h>
#include "Interface/IBoomerangState.h"
#include "Libraries/MyLib/CSV.h"

class Boomerang;
class Player;

// BoomerangThrow�N���X���`����
class BoomerangThrow : public IBoomerangState
{
public: 
	DirectX::SimpleMath::Matrix GetMatrix() { return m_worldMatrix; }

	std::vector<DirectX::SimpleMath::Vector3> GetSS() { return m_spherePos; }

public:
	// �R���X�g���N�^
	BoomerangThrow(Boomerang* boomerang, Player* player);
	// �f�X�g���N�^
	~BoomerangThrow();
	// ����������
	void Initialize();

	// �X�V����
	void Update(const float& elapsedTime);

	void Enter();
	void Exit();

	void SplineCurve(const float& elapsedTime);

private:

	Boomerang* m_boomerang;
	Player* m_player;

	DirectX::SimpleMath::Quaternion m_rotate;
	DirectX::SimpleMath::Vector3 m_position;

	std::unique_ptr<CSV> m_csv;

	std::vector<DirectX::SimpleMath::Vector3> m_spherePos;
	std::vector<DirectX::SimpleMath::Vector3> m_moveSpherePos;

	// �f�o�C�X�R���e�L�X�g
	ID3D11DeviceContext* m_context;
	// ���[���h�}�g���b�N�X
	DirectX::SimpleMath::Matrix m_worldMatrix;
	// �o�E���f�B���O�X�t�B�A
	DirectX::BoundingSphere m_boundingSphereLeftLeg;

	float m_transformRatio;
	int m_index;
	float m_totalTime;
	int m_startIndex;

	float m_moveSpeed;


};

