#include "pch.h"
#include "Interface/IComponent.h"
#include "Game/Object/BirdEnemy/BirdEnemyBase.h"
#include "DeviceResources.h"
#include "Game/CommonResources.h"
#include <unordered_map>
#include "Libraries/MyLib/Bounding.h"

void BirdEnemyBase::SetRunnginAnimationName(std::string name)
{
	//���O�������Ȃ�
	if (m_runningAnimationName == name)
	{
		return;
	}

	//�A�j���[�V���������邩�T��
	auto it = m_animations.find(m_runningAnimationName);
	//�����
	if (it != m_animations.end())
	{
		//�ύX�O�̃A�j���[�V���������Z�b�g
		m_animations[m_runningAnimationName]->ResetAnimation();
		//��]�����Z�b�g�@����͂̂��ɂ���Ȃ��Ȃ�@�O�̃A�j���[�V�����Ǝ��̃A�j���[�V�����̐؂�ւ�����a���Ȃ����邽�߂�
		m_animationRotation = DirectX::SimpleMath::Quaternion::Identity;

	}


	m_runningAnimationName = name;





	// ���i���X�V����
	for (auto& part : m_parts)
	{
		part->SetRunnginAnimationName(name);
	}

}

// �R���X�g���N�^
BirdEnemyBase::BirdEnemyBase(CommonResources* resources,IComponent* parent,  DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& positonFromParent, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	m_commonResources{resources},
	m_parent(parent),
	m_initialScale{initialScale},
	m_initialAngle(initialAngle),
	m_positonFromParent{positonFromParent},
	m_model{},
	m_parts{},
	m_worldMatrix{},
	m_animationPosition{},
	m_animationRotation{},
	m_animetionTime{}
{
}

// �f�X�g���N�^
BirdEnemyBase::~BirdEnemyBase()
{
	
}

// ����������
void BirdEnemyBase::Initialize()
{
}

// ����������
void BirdEnemyBase::Initialize(std::unique_ptr<DirectX::Model> model)
{
	// ���f����ݒ肷��
	m_model = std::move(model);

	m_bounding = std::make_unique<Bounding>();
}

// �X�V����
void BirdEnemyBase::Update(const float& elapsdTime)
{
	UNREFERENCED_PARAMETER(elapsdTime);


	// ���i���X�V����
	for (auto& part : m_parts)
	{
		part->Update(elapsdTime);
	}
}

// �C�����i��ǉ�����
void BirdEnemyBase::Attach(std::unique_ptr<IComponent> turretPart)
{
	// ����������
	turretPart->Initialize();
	// ���i��ǉ�����
	m_parts.emplace_back(std::move(turretPart));
}

// ���i���폜����
void BirdEnemyBase::Detach(std::unique_ptr<IComponent> turretPart)
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
void BirdEnemyBase::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{


	// ���i��`�悷��
	for (auto& turretPart : m_parts)
	{
		// �C���q���i��`�悷��
		turretPart->Render(view, projection);
	}
}

// �`�悷��(���g��`�悷��)
void BirdEnemyBase::Render(const DirectX::SimpleMath::Matrix& matrix, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
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
void BirdEnemyBase::DrawModel(const DirectX::SimpleMath::Matrix& matrix, DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{

	auto context = BirdEnemyBase::GetResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BirdEnemyBase::GetResources()->GetCommonStates();


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
void BirdEnemyBase::DrawBoundingBox(const DirectX::SimpleMath::Matrix& matrix)
{
}


// �㏈�����s��
void BirdEnemyBase::Finalize()
{
}

void BirdEnemyBase::RegistrationCollionManager(CollisionManager* collsionManager)
{
	// ���i�𓖂��蔻��ɓo�^
	for (auto& turretPart : m_parts)
	{
		// ���i��`�悷��
		turretPart->RegistrationCollionManager(collsionManager);
	}

}


void BirdEnemyBase::CreateBounding(DirectX::SimpleMath::Vector3 position,DirectX::SimpleMath::Quaternion rotate ,DirectX::SimpleMath::Vector3 boxExten, float SphereRadius)
{


	m_bounding->CreateOrientexBox(m_commonResources, position, boxExten,rotate);
	m_bounding->CreateBoundingSphere(m_commonResources, position, SphereRadius);


}

void BirdEnemyBase::BoundingUdate(DirectX::SimpleMath::Vector3 position,DirectX::SimpleMath::Quaternion rotate)
{

	m_bounding->OrientexBoxUpdate(position,rotate);

}

void BirdEnemyBase::BoundingRender(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	m_bounding->DrawOrientexBox(view, projection);
	//m_bounding->DrawBoundingSphere(view, projection);


}

Animation::AnimationState BirdEnemyBase::AnimationUdate(const float& elapsdTime)
{
	using namespace DirectX::SimpleMath;

	//�����l�Ƃ��ăA�j���[�V�������Ƃ���
	Animation::AnimationState state = Animation::AnimationState::End;
	//�A�j���[�V������T��
	auto it = m_animations.find(m_runningAnimationName);
	//�A�j���[�V�����������
	if (it != m_animations.end())
	{
		state = m_animations[m_runningAnimationName]->Update(elapsdTime);
		m_animationRotation = m_animations[m_runningAnimationName]->GetAnimationRotate();
	}


	// ���i�̃A�j���[�V�������X�V����
	for (auto& part : m_parts)
	{
		//�q�����s���Ȃ�
		if (part->AnimationUdate(elapsdTime) == Animation::AnimationState::Running)
		{
			//�A�j���[�V�������s����
			state = Animation::AnimationState::Running;
		}
	}

	return state;
}





// ���͒l�𐧌�����
inline float Clamp(const float& value, const float& min, const float& max)
{
	if (value < min) 	return min;
	else if (value > max) return max;
	return value;
}