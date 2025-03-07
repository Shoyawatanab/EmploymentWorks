/*
	@file	Beam.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "Beam.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/Enemys/BossEnemy/Beam/BeamRays.h"
#include "Game/Enemys/BossEnemy/Beam/BeamEnergyBall.h"
#include "Game/Enemys/BossEnemy/Beam/BeamChargeEffect.h"
#include "Game/CollisiionManager.h"
#include "Game/Params.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;




/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
Beam::Beam(CommonResources* resources)
	:
	BaseEntity(resources,Params::BOSSENEMY_BEAM_SCALE,Params::BOSSENEMY_BEAM_POSITION,Params::BOSSENEMY_BEAM_ROTATION)
	,m_initialScale{}
	,m_energyBall{}
	,m_preliminaryActitonTime{}
	,m_chargeEffect{}
	,m_deleteChargeEffect{}
	,m_rays{}
	
{
	m_energyBall = std::make_unique<BeamEnergyBall>(resources,this);
	m_rays = std::make_unique<BeamRays>(resources,this);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Beam::~Beam()
{
	// do nothing.
}

/// <summary>
/// ������
/// </summary>
void Beam::Initialize()
{


	m_energyBall->Initialize();
	m_rays->Initialize();




	
}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void Beam::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{

	BaseEntity::Render(view, projection);


	m_energyBall->Render(view, projection);
	for (auto& partcle : m_chargeEffect)
	{
		partcle->Render(view, projection);
	}
	m_rays->Render(view, projection);




}

/// <summary>
/// �X�V
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void Beam::Update(const float& elapsedTime)
{




	for (auto& effect : m_deleteChargeEffect)
	{
		m_chargeEffect.erase(
			std::remove_if(
				m_chargeEffect.begin(), m_chargeEffect.end(),
				[&effect](const std::unique_ptr<BeamChargeEffect>& particle) {
					return particle.get() == effect; // ��v���邩�𔻒�
				}
			),
			m_chargeEffect.end()
		);
	}

	m_deleteChargeEffect.clear();


}


/// <summary>
/// �K�v�ȃ|�C���^�̒ǉ�
/// </summary>
/// <param name="bossEnemy">�{�X�G</param>
/// <param name="player">�v���C��</param>
void Beam::AddPointer(BossEnemy* bossEnemy, Player* player)

{
	m_energyBall->AddPointer(this);
	m_rays->AddPointer(this);

}

/// <summary>
/// �����蔻��ɒǉ�
/// </summary>
/// <param name="collsionManager">�����蔻��N���X</param>
void Beam::AddCollionManager(CollisionManager* collsionManager)
{
	m_energyBall->AddCollision(collsionManager);
}

/// <summary>
/// �p�[�e�B�N���𐶐�
/// </summary>
void Beam::CreateParticle()
{

	std::vector<Vector3> position;
	std::vector<Quaternion> rotate;


	float radius = 0.9f;

	for (int angle = 0; angle < 360; angle += 45)
	{
		// �p�x�����W�A���ɕϊ�   �X�^�[�g���ォ��n�߂邽�߂ɂX�O�x�v���X����@�X�O�����Ȃ��ƉE����n�܂�
		float radian = DirectX::XMConvertToRadians(angle) + DirectX::XMConvertToRadians(90);

		// ���W���v�Z�i�ォ�甽���v���ɂ���j
		float x = radius * cos(radian); // X���W
		float y = radius * sin(radian); // Y���W

		// ���W��ǉ�
		position.push_back(Vector3(x, y, 0.0f));

		// ��]��ǉ��i���W�Ɠ�����ŉ�]���쐬�j
		rotate.push_back(Quaternion::CreateFromAxisAngle(Vector3::UnitZ, DirectX::XMConvertToRadians(angle)));

	}


	for (int i = 0; i < position.size(); i++)
	{
		auto particle = std::make_unique<BeamChargeEffect>();
		particle->AddPointer(this);
		particle->Initialize(BaseEntity::GetCommonResources(), position[i], rotate[i]);

		m_chargeEffect.push_back(std::move(particle));

	}
}

/// <summary>
/// �폜�p�[�e�B�N���̒ǉ�
/// </summary>
/// <param name="effect">�폜����p�[�e�B�N��</param>
void Beam::RegistrationDeleteParticle(BeamChargeEffect* effect)
{
	m_deleteChargeEffect.push_back(effect);

}

/// <summary>
/// �p�[�e�B�N���̃N���A
/// </summary>
void Beam::DeleteParticle()
{

	m_chargeEffect.clear();

}


