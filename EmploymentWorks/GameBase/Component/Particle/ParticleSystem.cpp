//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2025/06/04
// <file>			ParticleSystem.cpp
// <�T�v>		�@�@�p�[�e�B�N���̃V�X�e���@�R���|�[�l���g
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include"pch.h"
#include"ParticleSystem.h"
#include "Libraries/MyLib/BinaryFile.h"
#include <random>
#include"GameBase/Scene/Scene.h"
#include"GameBase/Manager/RenderManager.h"
#include "GameBase/Common/Commons.h"
/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="owner"></param>
ParticleSystem::ParticleSystem(Actor* owner)
	:
	Component{owner},
	m_pDR{nullptr},
	m_timer{},
	m_oneLapTime{},
	m_emitTimer{},
	m_isStopping{false}
{
	
	GetActor()->GetScene()->GetRenderMangaer()->AddParticle(this);
	Create();
	Prewarm();
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ParticleSystem::~ParticleSystem()
{
	//GetActor()->GetScene()->GetRenderManager()->RemoveParticle(this);
}

/// <summary>
/// ��蒼���p
/// </summary>
void ParticleSystem::ReStart()
{
	m_isStopping = false;
	m_particleUtility.clear();
	m_emitTimer = 0;
	m_timer = 0;
	m_oneLapTime = 0;
	Prewarm();
}

/// <summary>
/// �����֐�
/// </summary>
/// <param name="pDR"></param>
void ParticleSystem::Create()
{
	m_pDR = CommonResources::GetInstance()->GetDeviceResources();
	ID3D11Device* device = m_pDR->GetD3DDevice();

	m_particleComputeShader = std::make_unique<ParticleComputeShader>(m_pDR);

	m_spriteInstancing.Initialize(device, m_mainModule.MaxParticles);
	m_spriteInstancing.SetTexture(m_particleComputeShader->GetSRV());
}

void ParticleSystem::InitInstancing()
{
	ID3D11Device* device = m_pDR->GetD3DDevice();
	m_spriteInstancing.Initialize(device, m_mainModule.MaxParticles);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime"></param>
void ParticleSystem::Update(const float& deltaTime)
{
	// �X�g�b�v���̏����͑������^�[������
	if (m_isStopping == true) { return; }
	// �S�̂̎��Ԃ��v������
	m_timer += deltaTime;
	// �ŏ��̃f�B���C���ԑO�Ȃ�X�V���s��Ȃ��悤�ɑ���return������
	if (m_timer <= m_mainModule.DelayTime) { return; }
	// ����̎��Ԃ��v������
	m_oneLapTime += deltaTime;
	// �p�[�e�B�N���̍X�V
	UpdateParticle(deltaTime);

	if (m_isStopParticle == true) { return; }

	// ���[�v�̗L��
	if (CheckLoop()) { return; };
	// �G�~�b�V�����Ǘ�
	EmissionControl(deltaTime);
	// �o�[�X�g�Ǘ�
	BurstControl(deltaTime);

}

/// <summary>
/// �p�[�e�B�N���̍X�V
/// </summary>
void ParticleSystem::UpdateParticle(float deltaTime)
{
	// ���܂���p�[�e�B�N������
	for (auto ite = m_particleUtility.begin(); ite != m_particleUtility.end();)
	{
		// �X�̃A�b�v�f�[�g��false���Ԃ��ꂽ�ꍇ�͒��g������
		if (!ite->Update(deltaTime)){ite = m_particleUtility.erase(ite);}
		// ����ȊO�́A���̃p�[�e�B�N���̈�֐i��
		else{	ite++;	}
	}
}

/// <summary>
/// ���[�v�̗L��
/// </summary>
/// <returns></returns>
bool ParticleSystem::CheckLoop()
{
	// Duration�𒴂����ꍇ�ɁA��~����̂��A���[�v����̂�
	if (m_oneLapTime >= m_mainModule.Duration)
	{
		// ���[�v���Ȃ��Ȃ�Ԃ�		// �`������Ȃ�
		if (!m_mainModule.Looping) { return true; }
		// ������xDuration�v�Z
		m_oneLapTime = 0.0f;
		for (auto& bursts : m_emission.m_bursts)
		{
			bursts.IsFired = false;
		}
	}
	return false;
}

/// <summary>
/// �G�~�b�V�����Ǘ�
/// </summary>
void ParticleSystem::EmissionControl(float deltaTime)
{
	// ��b�Ԃ�0��ȉ��o���΂����͂Ȃ��̂ŁA�������^�[��
	if (m_emission.RateOverTime <= 0) { return; }
	// 1�b�Ԃɉ������̂��A����Ƃ̊Ԋu
	float emissionInterval = 1.0f / m_emission.RateOverTime;
	m_emitTimer += deltaTime;
	// �G�~�b�g�̃J�E���g
	int emitCount = 0;
	// �p�[�e�B�N���̈ێ�
	while (m_emitTimer >= emissionInterval && m_particleUtility.size() < m_mainModule.MaxParticles)
	{
		// �p�[�e�B�N���̒ǉ�
		m_particleUtility.push_back(CreateNewParticle());
		m_emitTimer -= emissionInterval;
		emitCount++;
	}

}

/// <summary>
/// �o�[�X�g�Ǘ�
/// </summary>
void ParticleSystem::BurstControl(float deltaTime)
{
	// ���������o�[�X�g�̐���0�ȉ��Ȃ�Ԃ�
	if (m_emission.m_bursts.size() <= 0) { return; }
	// ��O�̃t���[�������߂�
	float prevLapTime = m_oneLapTime - deltaTime;
	// �o�[�X�g���ǉ����ꂽ��������
	for (auto& bursts : m_emission.m_bursts)
	{
		// �T�C�N����-1�łȂ����A�ݒ肵�Ă����ꍇ�̃T�C�N���J�E���g�������Ă���Ƃ��͏������Ȃ�
		if (bursts.Cycles != -1 && bursts.CycleCount >= bursts.Cycles) { continue; }
		// �o�[�X�g�����鎞�Ԃ��A�O�̃t���[���ƁA���̃t���[���̊Ԃɂ���ꍇ���A�܂��g�p���Ă��Ȃ��ꍇ
		if (prevLapTime <= bursts.Time && bursts.Time <= m_oneLapTime && bursts.IsFired == false)
		{
			// ���̃o�[�X�g�̃J�E���g����
			for (int i = 0; i < bursts.Count; i++)
			{
				m_particleUtility.push_back(CreateNewParticle());
			}
			// �o�[�X�g�̏I�������true�ɂ���
			bursts.IsFired = true;
			bursts.CycleCount += 1;
		}
	}
}

/// <summary>
/// ��������X�L�b�v�p�i�t���[����΂��j
/// </summary>
void ParticleSystem::Prewarm()
{
	if (!m_mainModule.Prewarm) return;

	const float duration = m_mainModule.Duration;
	const float step = 1.0f / 60.0f; // 60FPS �����ŃX�L�b�v���s

	m_timer = 0.0f;
	m_oneLapTime = 0.0f;
	m_emitTimer = 0.0f;
	m_particleUtility.clear();

	for (float t = 0.0f; t < duration; t += step)
	{
		Update(step);
	}

	// ���Ԃ�Duration�Ƀ��Z�b�g���Ă����i���[�v�����Ȃ����߁j
	m_oneLapTime = duration;
}

/// <summary>
/// �`�揈��
/// </summary>
void ParticleSystem::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj)
{
	m_particleComputeShader->CalculateImage();
	m_spriteInstances.clear();

	for (auto& p : m_particleUtility)
	{
		SpriteInstancing::SpriteInstanceData data{};
		data.position = p.GetPosition();
		data.size = p.GetNowScale(); 
		data.color = p.GetNowColor();
		data.texCoord = DirectX::SimpleMath::Vector4(0, 0, 1, 1); // ����g��Ȃ�
		data.rotation = p.GetNowRotate();

		if (m_mainModule.SimulationSpaceType == SimulationSpaceType::Local)
		{
			data.position += GetActor()->GetTransform()->GetWorldPosition();
		}
		m_spriteInstances.push_back(data);
	}

	if (!m_spriteInstances.empty())
	{
	
		m_spriteInstancing.Render(
			m_pDR->GetD3DDeviceContext(),
			CommonResources::GetInstance()->GetCommonStates(),
			view,
			proj,
			m_spriteInstances);
	
	}

}

/// <summary>
/// �V�K�p�[�e�B�N�����쐬����
/// </summary>
ParticleUtility ParticleSystem::CreateNewParticle()
{
	
	// �ʒu��Vector3�^�ɑ��
	// �����A�N�^�[�́ATransform�̈ʒu�ɉ������ꏊ����o���悤�ɂ���
	DirectX::SimpleMath::Vector3 position = DirectX::SimpleMath::Vector3::Zero;

	if (m_mainModule.SimulationSpaceType == SimulationSpaceType::World)
	{
		position = GetActor()->GetTransform()->GetWorldPosition();
	}
	
	auto velocity = DirectX::SimpleMath::Vector3::Zero;
	if (m_shape.Shape)
	{
		m_shape.Shape->Generate();

		position += m_shape.Shape->GetPosition();
		velocity += m_shape.Shape->GetVelocity();
	}
	// �ݒ肳�ꂽUtility�Ƃ��ĕԂ����߂ɐݒ�
	ParticleUtility particle = ParticleUtility(
		m_mainModule.LifeTime.Get(),
		position,
		velocity * m_mainModule.StartSpeed.Get(),
		m_mainModule.Gravity.Get(),
		m_mainModule.MinSize.Get(),
		m_mainModule.MaxSize.Get(),
		m_mainModule.StartRotate.Get(),
		m_mainModule.EndRotate.Get(),
		m_mainModule.StartColor.Get(),
		m_mainModule.EndColor.Get());

	particle.SetAddForce(m_addForceSpeed.ForcePower.Get());
	particle.SetEasing(m_easing.SizeEasing);
	return particle;

}
