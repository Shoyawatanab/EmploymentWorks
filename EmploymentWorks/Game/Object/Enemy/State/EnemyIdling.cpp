
#include "pch.h"
#include "Game/Object/Enemy/State/EnemyIdling.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player.h"

const DirectX::SimpleMath::Vector3 GENERATEDISTANCE(0.5f, 0.8f, 0.0f);

// �R���X�g���N�^
EnemyIdling::EnemyIdling()
	:
	m_worldMatrix{},
	m_boundingSphereLeftLeg{}
{
}

// �f�X�g���N�^
EnemyIdling::~EnemyIdling()
{

}

// ����������
void EnemyIdling::Initialize()
{
	
	// ���r���E���𐶐�����
	m_boundingSphereLeftLeg = DirectX::BoundingSphere();
	// ���r���E���̔��a��ݒ肷��
	m_boundingSphereLeftLeg.Radius = 0.01;

}


// �X�V����
void EnemyIdling::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


}


void EnemyIdling::Enter()
{

}

void EnemyIdling::Exit()
{

}