//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto	
// <����J�n��>		2025/06/04
// <file>			ParticleSystem.h
// <�T�v>		�@�@�p�[�e�B�N���̃V�X�e���@�R���|�[�l���g 
// <Version>		Ver1.0.0	���g�ݗ��Ċ����@Main���W���[���̂�
//					Ver1.0.1	Emission�ƁASphere�̃T�u���W���[������
//					Ver1.0.2	Easing�̊T�O��ǉ��A��Ver2�\��(���t�@�N�^�����O)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include"GameBase/Component/Components.h"
#include"GameBase/Component/Particle/ParticleUtility.h"
#include"Shape/Shapes.h"
#include"Shape/ShapeBase.h"
#include "Libraries/Easing.h"
#include"Instancing/SpriteInstancing.h"
#include"ValueWrapper.h"
#include"Compute/ParticleComputeShader.h"

class ParticleSystem : public Component
{
public:
	// ���[���h���W�ł�邩�A���[�J�����W�ł�邩
	// ���[���h���ƁA�p�[�e�B�N���̒Ǐ]�͂��Ă��Ȃ��B���[�J�����ƁA�p�[�e�B�N�����Ǐ]���Ă���悤�ɂȂ�
	enum class SimulationSpaceType
	{
		Local = 0,
		World = 1
	};
	// �p�[�e�B�N���̃��C�����W���[���ݒ�
	struct MainModule
	{
		// ���[�v����̎���
		float Duration = 5.0f;
		// ���[�v�����邩�ǂ��� true == ���� : false == ���Ȃ�
		bool Looping = true;
		// �ŏ��̃f�B���C����
		float DelayTime = 0.0f;
		// �X�L�b�v���ꂽ��ԂŎn�܂� true == ���� false == ���Ȃ�
		bool Prewarm = false;
		// �������x
		ValueWrapper<float> StartSpeed = 1.0f;
		// �����c�鎞�Ԃ̍ŏ��l�A�ő�l
		ValueWrapper<float> LifeTime = { 5.0f,5.0f };
		// ���x
		DirectX::SimpleMath::Vector3 Velocity = { 0.0f,0.0f,0.0f };
		// �傫���̍ŏ��l
		ValueWrapper<DirectX::SimpleMath::Vector3> MinSize = { DirectX::SimpleMath::Vector3(1.0f,1.0f,1.0f) };
		// �傫���̍ő�l
		ValueWrapper<DirectX::SimpleMath::Vector3> MaxSize = { DirectX::SimpleMath::Vector3(1.0f,1.0f,1.0f)};
		// ������]
		ValueWrapper<DirectX::SimpleMath::Quaternion> StartRotate = { DirectX::SimpleMath::Quaternion(0.0f,0.0f,0.0f,1.0f) };
		// �ŏI��]
		ValueWrapper<DirectX::SimpleMath::Quaternion> EndRotate = { DirectX::SimpleMath::Quaternion(0.0f,0.0f,0.0f,1.0f) };
		// �d��
		ValueWrapper<DirectX::SimpleMath::Vector3> Gravity = { DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f) };
		// �����̐F
		ValueWrapper<DirectX::SimpleMath::Color> StartColor = { DirectX::SimpleMath::Quaternion(0.0f, 0.0f, 0.0f, 1.0f) };
		// �ŏI�̐F
		ValueWrapper<DirectX::SimpleMath::Color> EndColor = { DirectX::SimpleMath::Quaternion(1.0f, 1.0f, 1.0f, 0.0f) };
		// �p�[�e�B�N�����o�����̍ő�l
		int MaxParticles = 100;
		// ���������[�J���ɂ��邩���[���h�ɂ��邩
		SimulationSpaceType SimulationSpaceType = SimulationSpaceType::Local;
	};

	// �o�[�X�g������
	struct Burst
	{
		// ���������鎞��
		float Time = 0;
		// ��x�ɏo���p�[�e�B�N���̐�
		int Count = 10;
		// ���łɔ����������ǂ���
		bool IsFired = false;
		// ����J��Ԃ���( -1�Ńp�[�e�B�N����������薳��)
		int Cycles = -1;
		// ���݂̌J��Ԃ��񐔕ۑ��p
		int CycleCount = 0;
	};

	// �p�[�e�B�N���̔������@
	struct EmissionModule
	{
		// �b�Ԃ̃p�[�e�B�N��������
		int RateOverTime = 10;
		// �o�[�X�g������
		std::vector<Burst> m_bursts;
	};


	// �p�[�e�B�N���̔��ˌ`��Ȃǂ̐ݒ�
	struct ShapeModule
	{
		// �r���{�[�h�̗L�� true == ���� �Ffalse == �Ȃ�
		bool IsBillboard = true;
		// �p�[�e�B�N���̌`����
		std::shared_ptr<ShapeBase> Shape = std::make_shared<ShapeCone>(1.0f ,25.0f ,DirectX::SimpleMath::Vector3(0,1,0));
	};

	// �C�[�W���O�ő傫���A�F��ύX������
	struct EasingOverLifeTime
	{
		NakashiLib::Easing::EasingType SizeEasing = NakashiLib::Easing::EasingType::InSine;
		NakashiLib::Easing::EasingType ColorEasing = NakashiLib::Easing::EasingType::InSine;
	};

	// ���Ԃɉ����đ��x���Z
	struct ForceOverLifeTimeSpeed
	{
		ValueWrapper<DirectX::SimpleMath::Vector3> ForcePower = DirectX::SimpleMath::Vector3::Zero;
	};

	// �C���X�^���X�o�b�t�@�\�����`
	struct ParticleInstanceData
	{
		DirectX::SimpleMath::Matrix Transform;
		DirectX::SimpleMath::Color Color;
	};

public:
	// �R���X�g���N�^�A�f�X�g���N�^
	ParticleSystem(Actor* owner);
	~ParticleSystem();
	
	// �X�V����
	void Update(const float& deltaTime) override;
	// �`�揈��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& proj);

	// ��蒼���p�֐�
	void ReStart();
	// �~�߂�p�֐�
	void Stop() { m_isStopping = true; }
	// �~�߂��Ƃ��납��J�n
	void Play() { m_isStopping = false;}
	// �p�[�e�B�N���̐����݂̂Ƃ߂�
	void StopParticle() { m_isStopParticle = true; }
	// �p�[�e�B�N���̐������J�n
	void PlayParticle() { m_isStopParticle = false; }

	// ���\�b�h�`�F�[���œǂݍ��ނ悤�ɂ���+++++++++++++++++++++++++++++++
	// �e�N�X�`���ǂݍ���
	ParticleSystem* SetTexture(ID3D11ShaderResourceView* texture) { m_spriteInstancing.SetTexture(texture); return this; }
	// �ݒ�̕ύX												// ���C�����W���[���̕ύX�Ɠ����ɁA�C���X�^���V���O�̍ő�p�[�e�B�N�����ς�邽�߁A�ύX������
	ParticleSystem* SetMainModule(const MainModule& setting) { m_mainModule = setting; InitInstancing(); Prewarm(); return this; }
	// �G�~�b�^�[�̐ݒ�
	ParticleSystem* SetEmission(const EmissionModule& emission) { m_emission = emission; return this; }
	// �o�[�X�g�̐ݒ�
	ParticleSystem* AddBurst(float time, int count) { m_emission.m_bursts.push_back({ time , count , false , -1 , 0 }); return this; }
	// �ׂ����o�[�X�g�̐ݒ�������ǉ�
	ParticleSystem* AddBurst(const Burst& burst) { m_emission.m_bursts.push_back(burst); return this; }
	// �`�̐ݒ�
	ParticleSystem* SetShape(std::shared_ptr<ShapeBase> shape) { m_shape.Shape = shape; return this; }
	// �r���{�[�h�̗L��
	ParticleSystem* SetBillboardEnabled(bool enabled) { m_shape.IsBillboard = enabled; m_spriteInstancing.SetBillboard(m_shape.IsBillboard); return this; }
	// �ǉ��̑��x�̐ݒ�
	ParticleSystem* SetForce(ForceOverLifeTimeSpeed addVelocity) { m_addForceSpeed = addVelocity; return this; }
	// �C�[�W���O�ɂ��ύX�̐ݒ�
	ParticleSystem* SetEasing(const EasingOverLifeTime& easing) { m_easing = easing; return this; }
private:
	// �p�[�e�B�N���̍쐬
	ParticleUtility CreateNewParticle();
	// �쐬����
	void Create();
	// �C���X�^���V���O�p������
	void InitInstancing();

	// �p�[�e�B�N���̍X�V
	void UpdateParticle(float deltaTime);
	// ���[�v�L��
	bool CheckLoop();
	// �G�~�b�^�[�v�Z
	void EmissionControl(float deltaTime);
	// �o�[�X�g�v�Z
	void BurstControl(float deltaTime);

	// �v���E�H�[�����邩�ǂ����p
	void Prewarm();
private:// �ϐ�
	// �f�o�C�X���\�[�X
	DX::DeviceResources* m_pDR;

	std::unique_ptr<ParticleComputeShader> m_particleComputeShader;

	std::list<ParticleUtility> m_particleUtility;
	// �p�[�e�B�N���̏��
	MainModule m_mainModule;
	// �G�~�b�^�[�̏��
	EmissionModule m_emission;
	// �`�̏��
	ShapeModule m_shape;
	// �ǉ��̑��x
	ForceOverLifeTimeSpeed m_addForceSpeed;
	// �C�[�W���O
	EasingOverLifeTime m_easing;

	// ����
	float m_timer;
	// ����̎��Ԍv���p
	float m_oneLapTime;
	// �p�[�e�B�N�����o�����߂̎��Ԍv��
	float m_emitTimer;

	// �~�ߗL�� true == �~�܂��Ă��� false == �~�܂��Ă��Ȃ�
	bool m_isStopping;

	bool m_isStopParticle;

	// �C���X�^���V���O
	SpriteInstancing m_spriteInstancing;
	std::vector<SpriteInstancing::SpriteInstanceData> m_spriteInstances;
};