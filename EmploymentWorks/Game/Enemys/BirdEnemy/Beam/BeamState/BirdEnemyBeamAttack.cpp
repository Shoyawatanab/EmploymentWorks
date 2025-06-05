
#include "pch.h"
#include "BirdEnemyBeamAttack.h"

#include "Game/CommonResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Enemys/BirdEnemy/Beam/BirdEnemyBeam.h"
#include "Game/Enemys/BirdEnemy/Beam/BirdEnemyBeamEnergyBall.h"
#include "Game/Enemys/BirdEnemy/BirdEnemy.h"

#include "Game/Params.h"
#include "Game/MathUtil.h"
#include "Game/InstanceRegistry.h"
#include "Game/Observer/Messenger.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="birdEnemy">���̓G</param>
/// <param name="beam">�r�[��</param>
BirdEnemyBeamAttack::BirdEnemyBeamAttack(BirdEnemy* birdEnemy, BirdEnemyBeam* beam)
	:
	m_player{}
	,m_birdEnemy{birdEnemy}
	,m_beam{beam}
	,m_moveDirectiion{}
	,m_initialSpeed{}
	,m_finalSpeed{}
	,m_decelerationTime{}
	,m_time{}
{
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
BirdEnemyBeamAttack::~BirdEnemyBeamAttack()
{

}


/// <summary>
/// ������
/// </summary>
/// <param name="resoure">���ʃ��\�[�X</param>
void BirdEnemyBeamAttack::Initialize()
{
	m_player = InstanceRegistry::GetInstance()->GetRegistryInstance<Player>("Player");

	//������
	m_initialSpeed = Params::BIRDENEMY_BEAM_BALL_INITIAL_SPEED;
	m_finalSpeed = Params::BIRDENEMY_BEAM_BALL_FAINAL_SPEED;
	m_decelerationTime = Params::BIRDENEMY_BEAM_BALL_DECELERATION_TIME;

}



/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void BirdEnemyBeamAttack::Update(const float& elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);

	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	//�r�[���̍��W�̎擾
	Vector3 position = m_beam->GetPosition();
	//��Ԃ̂��߂̎��Ԃ����߂�@�@�o�ߎ��Ԃ��������ԂɂȂ�܂ł͂O�`�P�̊ԁ@�o�ߎ��Ԃ��������Ԃ𒴂���ƂP
	float t = std::min(m_time,m_decelerationTime) / m_decelerationTime;
	//�����ƏI���ŕ�Ԃ��Ĉړ����x�����߂�
	float moveSpeed =  MathUtil::Lerp(m_initialSpeed,m_finalSpeed,t);
	//�����x�N�g���Ɍo�ߎ��ԁ@���x�������Ĉʒu���X�V
	position += m_moveDirectiion * elapsedTime * moveSpeed;
	//�X�V�������W��ݒ�
	m_beam->SetPosition(position);
	//�o�ߎ��Ԃ̉��Z
	m_time += elapsedTime;
	
}


/// <summary>
/// ��Ԃɓ�������
/// </summary>
void BirdEnemyBeamAttack::Enter()
{
	//�r�[���̉�]���擾
	m_beam->SetRotation(m_birdEnemy->GetRotation());
	//�r�[���̍��W�̎擾
 	DirectX::SimpleMath::Vector3 position = m_beam->GetPosition();
	//��������������
	m_moveDirectiion =  m_beam->GetTarget() - m_beam->GetPosition()  ;
	//���K��
	m_moveDirectiion.Normalize();
	//���Ԃ̏�����
	m_time = 0;
	//���̓G�̃X�e�[�g���A�C�h���ɕύX

	Messenger::GetInstance()->Notify<EnemyMessageType>(m_birdEnemy->GetID(), EnemyMessageType::IDLING);

}

/// <summary>
/// ��Ԃ𔲂�����
/// </summary>
void BirdEnemyBeamAttack::Exit()
{



}



