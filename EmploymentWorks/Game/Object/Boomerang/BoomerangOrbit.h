#pragma once
#include <pch.h>
#include "Interface/IBoomerangState.h"
#include "Libraries/MyLib/CSV.h"
class CommonResources;

class Boomerang;
class Player;
class Enemy;


// BoomerangOrbit�N���X���`����
class BoomerangOrbit 
{
public: 
	std::vector<DirectX::SimpleMath::Vector3> GetMovePos() { return m_moveSpherePos; }

public:
	// �R���X�g���N�^
	BoomerangOrbit(Boomerang* boomerang, Player* player, Enemy* enemy);
	// �f�X�g���N�^
	~BoomerangOrbit();
	// ����������
	void Initialize(CommonResources* resources);

	// �X�V����
	void Update(const float& elapsedTime);

	void Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection);

	void Finalize();

	void SplineCurve(const float& elapsedTime);

private:
	CommonResources* m_commonResources;


	Boomerang* m_boomerang;
	Player* m_player;
	Enemy* m_enemy;

	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> m_primitveBatch;

	// ���̓��C�A�E�g
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	DirectX::SimpleMath::Quaternion m_initialRotate;
	DirectX::SimpleMath::Vector3 m_position;

	std::unique_ptr<CSV> m_csv;

	std::vector<DirectX::SimpleMath::Vector3> m_spherePos;
	std::vector<DirectX::SimpleMath::Vector3> m_moveSpherePos;

	DirectX::SimpleMath::Vector3 m_direction;
	//DirectX::SimpleMath::Vector3 m_previousFrameDirection;

	// �o�E���f�B���O�X�t�B�A
	DirectX::BoundingSphere m_boundingSphereLeftLeg;

	float m_transformRatio;
	int m_index;
	float m_totalTime;
	int m_startIndex;

	float m_moveSpeed;

	//float m_rotationalMotion;
	DirectX::SimpleMath::Vector3 m_target;


	std::vector<DirectX::VertexPositionColor> m_linePos;

	std::unique_ptr<DirectX::BasicEffect> m_effect;

};

