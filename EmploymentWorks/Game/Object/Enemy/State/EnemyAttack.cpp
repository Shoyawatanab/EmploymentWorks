
#include "pch.h"
#include "Game/Object/Enemy/State/EnemyAttack.h"
#include "Game/Object/Boomerang/Boomerang.h"
#include "Game/Object/Player.h"

const DirectX::SimpleMath::Vector3 GENERATEDISTANCE(0.5f, 0.8f, 0.0f);

// �R���X�g���N�^
EnemyAttack::EnemyAttack()
	:
	m_worldMatrix{},
	m_boundingSphereLeftLeg{}
{
}

// �f�X�g���N�^
EnemyAttack::~EnemyAttack()
{

}

// ����������
void EnemyAttack::Initialize()
{
	
	// ���r���E���𐶐�����
	m_boundingSphereLeftLeg = DirectX::BoundingSphere();
	// ���r���E���̔��a��ݒ肷��
	m_boundingSphereLeftLeg.Radius = 0.01;

}


// �X�V����
void EnemyAttack::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);
	using namespace DirectX;
	using namespace DirectX::SimpleMath;



}


void EnemyAttack::Enter()
{

}

void EnemyAttack::Exit()
{

}