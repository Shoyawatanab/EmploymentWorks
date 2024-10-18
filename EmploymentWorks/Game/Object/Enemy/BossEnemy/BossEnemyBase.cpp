#include "pch.h"
#include "Interface/IComponent.h"
#include "Game/Object/Enemy/BossEnemy/BossEnemyBase.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include <unordered_map>
#include "Libraries/MyLib/Bounding.h"
#include "Game/DetectionCollision/CollisionManager.h"
// �R���X�g���N�^
BossEnemyBase::BossEnemyBase(CommonResources* resources,IComponent* parent, DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	m_commonResources{resources},
	m_parent(parent),
	m_initialScale{initialScale},
	m_initialAngle(initialAngle),
	m_positonFromParent{positonFromParent},
	m_model{},
	m_parts{},
	m_worldMatrix{},
	m_runningKeyFrames{},
	m_animationPosition{},
	m_animationRotation{},
	m_animetionTime{}
{
}

// �f�X�g���N�^
BossEnemyBase::~BossEnemyBase()
{
	
}

// ����������
void BossEnemyBase::Initialize()
{
}

// ����������
void BossEnemyBase::Initialize(std::unique_ptr<DirectX::Model> model)
{
	// ���f����ݒ肷��
	m_model = std::move(model);

	m_bounding = std::make_unique<Bounding>();
}

// �X�V����
void BossEnemyBase::Update(const float& elapsdTime)
{
	UNREFERENCED_PARAMETER(elapsdTime);


	// ���i���X�V����
	for (auto& part : m_parts)
	{
		part->Update(elapsdTime);
	}
}

// �C�����i��ǉ�����
void BossEnemyBase::Attach(std::unique_ptr<IComponent> turretPart)
{
	// ����������
	turretPart->Initialize();
	// ���i��ǉ�����
	m_parts.emplace_back(std::move(turretPart));
}

// ���i���폜����
void BossEnemyBase::Detach(std::unique_ptr<IComponent> turretPart)
{
	// �폜���镔�i��������
	auto it = std::find_if(m_parts.begin(), m_parts.end(),
		[&](const std::unique_ptr<IComponent>& turret_part)
		{
			return turret_part.get() == turretPart.get();
		}
	);
	// �폜���镔�i�����������ꍇ�͕��i���폜����
	if (it != m_parts.end())
	{
		m_parts.erase(it);
	}
}

// �`�悷��(���g��`�悵�Ȃ�)
void BossEnemyBase::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{


	// ���i��`�悷��
	for (auto& turretPart : m_parts)
	{
		// �C���q���i��`�悷��
		turretPart->Render(view, projection);
	}
}

// �`�悷��(���g��`�悷��)
void BossEnemyBase::Render(const DirectX::SimpleMath::Matrix& matrix, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	using namespace DirectX::SimpleMath;



	m_worldMatrix = matrix;
	// ���f����`�悷��
	DrawModel(matrix,view,projection);

#ifdef _DEBUG
	// ���E�{�b�N�X��`�悷��
	DrawBoundingBox(matrix);
#endif

	//���i�����݂��邩
	if (m_parts.size() == 0) 
		return;
	// ���i��`�悷��
	for (auto& turretPart : m_parts)
	{
		// ���i��`�悷��
		turretPart->Render(view,projection);
	}

}

// ���f����`�悷��
void BossEnemyBase::DrawModel(const DirectX::SimpleMath::Matrix& matrix, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{

	auto context = BossEnemyBase::GetResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BossEnemyBase::GetResources()->GetCommonStates();


	// ���f���̃G�t�F�N�g���X�V����
	m_model->UpdateEffects([&](DirectX::IEffect* effect)
		{
			// �x�C�V�b�N�G�t�F�N�g���擾����
			auto basicEffect = dynamic_cast<DirectX::BasicEffect*>(effect);
				// �f�B�t���[�Y�J���[��ݒ肷��
				basicEffect->SetDiffuseColor(DirectX::Colors::LightSlateGray);
				// �X�y�L�����J���[��ݒ肷��
				basicEffect->SetSpecularColor(DirectX::Colors::LightSlateGray);
				// �X�y�L�����p���[��ݒ肷��
				basicEffect->SetSpecularPower(20.0f);
		});
	// ���i��`�悷��
	//m_graphics->DrawModel(m_model, matrix);
	m_model->Draw(context, *states, matrix, view, projection);
}

// ���E�{�b�N�X��`�悷��
void BossEnemyBase::DrawBoundingBox(const DirectX::SimpleMath::Matrix& matrix)
{
}


// �㏈�����s��
void BossEnemyBase::Finalize()
{
}

void BossEnemyBase::RegistrationCollionManager(CollisionManager* collsionManager)
{


	// ���i�𓖂��蔻��ɓo�^
	for (auto& turretPart : m_parts)
	{
		// ���i��`�悷��
		turretPart->RegistrationCollionManager(collsionManager);
	}



}


void BossEnemyBase::CreateBounding(DirectX::SimpleMath::Vector3 position,DirectX::SimpleMath::Quaternion rotate ,DirectX::SimpleMath::Vector3 boxExten, float SphereRadius)
{


	m_bounding->CreateOrientexBox(m_commonResources, position, boxExten,rotate);
	m_bounding->CreateBoundingSphere(m_commonResources, position, SphereRadius);


}

void BossEnemyBase::BoundingUdate(DirectX::SimpleMath::Vector3 position,DirectX::SimpleMath::Quaternion rotate)
{

	m_bounding->OrientexBoxUpdate(position,rotate);

}

void BossEnemyBase::BoundingRender(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	m_bounding->DrawOrientexBox(view, projection);
	//m_bounding->DrawBoundingSphere(view, projection);


}

IComponent::AnimationStage BossEnemyBase::AnimationUdate(const float& elapsdTime)
{
	using namespace DirectX::SimpleMath;
	
	//�����l�Ƃ��ăA�j���[�V�������Ƃ���
	AnimationStage state = AnimationStage::Runngin;

	//�c��A�j���[�V�������P�ȏ�  
	if (m_runningKeyFrames.size() > 1)
	{
		//���Ԃ̊��������߂�
		float ratio = m_animetionTime / m_runningKeyFrames[1].Time;
		//�������P�𒴂��Ȃ��悤�ɂ���
		ratio = std::min(ratio, 1.0f);
		//Lerp�֐��ō��W���X�V
		m_animationPosition = Vector3::Lerp(m_runningKeyFrames.begin()->Position, m_runningKeyFrames[1].Position, ratio);
		//Lerp�֐��ŉ�]���X�V
		m_animationRotation = Quaternion::Lerp(m_runningKeyFrames.begin()->Rotation, m_runningKeyFrames[1].Rotation, ratio);



		//�A�j���[�V�������Ԃ̍X�V
		m_animetionTime += elapsdTime;
		//��؂肪�I�������
		if (ratio >= 1)
		{
			//���Ԃ̏�����
			//m_animetionTime -= m_runningKeyFrames.begin()->Time;
			m_animetionTime = 0;
			//���s���A�j���[�V�����̐擪������
			m_runningKeyFrames.erase(m_runningKeyFrames.begin());
		}
	}
	else
	{
		//�A�j���[�V�����I��
		state = AnimationStage::Success;
	}


	// ���i�̃A�j���[�V�������X�V����
	for (auto& part : m_parts)
	{
		//�q�����s���Ȃ�
		if (part->AnimationUdate(elapsdTime) == AnimationStage::Runngin)
		{
			//�A�j���[�V�������s����
			state = AnimationStage::Runngin;
		}
	}


	//�e�E�q�܂߂ĂP�ł����s��������Ύ��s����Ԃ�
	return state;

}

/// <summary>
/// �A�j���[�V���������s���A�j���[�V�����ɓo�^
/// </summary>
/// <param name="name">�A�j���[�V������</param>
void BossEnemyBase::RegistrationRungingAnimation(std::string name)
{
	//name�̃A�j���[�V���������邩�ǂ���
	auto it =  m_animations.find(name);

	//�A�j���[�V���������邩�ǂ���
	if (it != m_animations.end())
	{
		//����ꍇ
		//�A�j���[�V�������R�s�[
		m_runningKeyFrames = m_animations[name];
		//���s���A�j���[�V�����̃T�C�Y�����ƂɃA�j���[�V�����̐؂�ւ��񐔂����߂�
		m_animationSwitchingCount = m_runningKeyFrames.size();
		//�A�j���[�V�������Ԃ̏�����
		m_animetionTime = 0;


	}


	// ���i�̃A�j���[�V������o�^����
	for (auto& part : m_parts)
	{
		part->RegistrationRungingAnimation(name);
	}
}



// ���͒l�𐧌�����
inline float Clamp(const float& value, const float& min, const float& max)
{
	if (value < min) 	return min;
	else if (value > max) return max;
	return value;
}