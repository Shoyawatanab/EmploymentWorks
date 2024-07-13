
#include "pch.h"
#include "Game/Object/Enemy/State/EnemyMove.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player.h"

const DirectX::SimpleMath::Vector3 GENERATEDISTANCE(0.5f, 0.8f, 0.0f);

// �R���X�g���N�^
EnemyMove::EnemyMove()
	:
	m_worldMatrix{},
	m_boundingSphereLeftLeg{}
{
}

// �f�X�g���N�^
EnemyMove::~EnemyMove()
{

}

// ����������
void EnemyMove::Initialize()
{
	
	// ���r���E���𐶐�����
	m_boundingSphereLeftLeg = DirectX::BoundingSphere();
	// ���r���E���̔��a��ݒ肷��
	m_boundingSphereLeftLeg.Radius = 0.01;

}


// �X�V����
void EnemyMove::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;



}


void EnemyMove::Enter()
{

}

void EnemyMove::Exit()
{

}