#include "pch.h"
#include "Game/Object/BirdEnemy/BirdEnemy.h"

#include "Game/Object/BirdEnemy/BirdEnemyBody.h"
#include "Game/DetectionCollision/CollisionManager.h"
#include "Libraries/MyLib/Bounding.h"

// �R���X�g���N�^
BirdEnemy::BirdEnemy(CommonResources* resources,IComponent* parent,const DirectX::SimpleMath::Vector3 initialScale, const DirectX::SimpleMath::Vector3& initialPosition, const DirectX::SimpleMath::Quaternion& initialAngle)
	:
	BirdEnemyBase(resources,parent, initialScale,DirectX::SimpleMath::Vector3::Zero, initialAngle),
	m_commonResources{resources},
	m_position{initialPosition},

	m_worldMatrix{}
{
}

// �f�X�g���N�^
BirdEnemy::~BirdEnemy()
{
	Finalize();
}

// ����������
void BirdEnemy::Initialize()
{
	using namespace DirectX::SimpleMath;

	//�uBody�v�𐶐�����
	Attach(std::make_unique<BirdEnemyBody>(BirdEnemyBase::GetResources(), this, BirdEnemyBase::GetInitialScale(), Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity));

	m_bounding = std::make_unique<Bounding>();
	m_bounding->CreateBoundingBox(m_commonResources, m_position, Vector3(0.7f, 0.4f,0.5f));
	m_bounding->CreateBoundingSphere(m_commonResources, m_position, 6.0f);

	m_idling->Initialize();

	m_attack->Initialize();

	m_currentState = m_idling.get();
	//m_currentState = m_attack.get();



	float scale = 2.5f;

	m_scale = Vector3(scale, scale, scale);

	m_scale = BirdEnemyBase::GetInitialScale();

}



// �L�[�{�[�h�C�x���g����������
void BirdEnemy::HandleKeyboardEvent()
{
	using namespace DirectX::SimpleMath;

	// �L�[�{�[�h�X�e�[�g���擾����
	DirectX::Keyboard::State keyboardState = DirectX::Keyboard::Get().GetState();






}

// �X�V����
void BirdEnemy::Update(const float& elapsdTime)
{
	using namespace DirectX::SimpleMath;
	UNREFERENCED_PARAMETER(elapsdTime);

	//// �L�[�{�[�h�C�x���g����������
	HandleKeyboardEvent();

	// �L�[�{�[�h�X�e�[�g���擾����
	DirectX::Keyboard::State keyboardState = DirectX::Keyboard::Get().GetState();



	m_currentState->Update(elapsdTime);


	// �C�����i���X�V����
	BirdEnemyBase::Update(elapsdTime);

	m_bounding->Update(m_position );

}

// �`�悷��
void BirdEnemy::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	m_bounding->DrawBoundingBox(view, projection);

	// �C�����i��`�悷��
	BirdEnemyBase::Render(view, projection);


}

// �㏈�����s��
void BirdEnemy::Finalize()
{

}

// �C�����E�����쐬����
DirectX::BoundingSphere BirdEnemy::CreateBoundingSphere(const float& radius)
{
	// ���E����錾����
	DirectX::BoundingSphere BirdEnemyBoundingSphere;
	// ���E���̔��a��ݒ肷��
	BirdEnemyBoundingSphere.Radius = radius;
	// ���E����Ԃ�
	return BirdEnemyBoundingSphere;
}

void BirdEnemy::SetAnimation(std::string name)
{
	SetRunnginAnimationName("FallDown");

}

void BirdEnemy::RegistrationInformation(Player* player)
{
	m_player = player;

	m_idling->RegistrationInformation(m_commonResources, m_player, this);
	m_attack->RegistrationInformation(m_commonResources, m_player, this);
}


void BirdEnemy::Instances()
{
	m_bounding = std::make_unique<Bounding>();

	m_idling = std::make_unique<BirdEnemyldling>();

	m_attack = std::make_unique<BirdEnemyAttack>();

}

void BirdEnemy::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);

	BirdEnemyBase::RegistrationCollionManager(collsionManager);

}

void BirdEnemy::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
}

