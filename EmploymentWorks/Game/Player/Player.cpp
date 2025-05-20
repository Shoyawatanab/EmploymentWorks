#include "pch.h"
#include "Player.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/InputManager.h"
#include "Game/Player/PlayerParts/PlayerBody.h"

#include "Libraries/WataLib/Json.h"
#include "Libraries/WataLib/Camera/TPS_Camera.h"
#include "Libraries/WataLib/Bounding.h"

#include "Game/Player/PlayerUsually.h"
#include "Game/CollisiionManager.h"
#include "Game/Player/State/PlayerStateMachine.h"
#include "Game/Observer/Messenger.h"

#include "Game/Params.h"



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="resources">���ʃ��\�[�X</param>
Player::Player(CommonResources* resources)
	:
	m_animationDatas{}
	,m_usually{}
	,m_boomerangs{}
	,m_hp{Params::PLAYER_HP}
	,CompositeEntity(resources, Params::PLAYER_SCALE,Params::PLAYER_POSITION,Params::PLAYER_ROTATION)
{
	m_usually = std::make_unique<PlayerUsually>();
	m_stateMachine = std::make_unique<PlayerStateMachine>();

	for (int i = 0; i < Params::BOOMERANG_MAX_COUNT; i++)
	{

		auto boomerang = std::make_unique<Boomerang>(resources,this,Params::BOOMERANG_SCALE,Params::BOOMERANG_POSITION,Params::BOOMERANG_ROTATION);
		m_boomerangs.push_back(std::move(boomerang));
	}
	
	m_shadow = std::make_unique<WataLib::Shadow>();

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Player::~Player()
{
}


/// <summary>
/// �K�v�ȃ|�C���^�̒ǉ�
/// </summary>
/// <param name="tpsCamera">TPS�J����</param>
/// <param name="targetMarker">�^�[�Q�b�g�}�[�J�[</param>
void Player::AddPointer(WataLib::TPS_Camera* tpsCamera, TargetMarker* targetMarker)
{

	m_targetMarker = targetMarker;

	m_usually->AddPointer(this,tpsCamera);
	m_stateMachine->AddPointer(this);

	for (auto& boomerang : m_boomerangs)
	{
		boomerang->AddPointer(this, targetMarker,tpsCamera);
	}

}



/// <summary>
/// ������
/// </summary>
void Player::Initialize()
{

	CompositeEntity::Initialize();

	//�uBody�v�𐶐�����
	AddChild(std::make_unique<PlayerBody>(
		BaseEntity::GetCommonResources(),
		this,
		Params::PLAYER_BODY_SCALE , 
		Params::PLAYER_BODY_POSITION,
		Params::PLAYER_BODY_ROTATION)
	);

	//�A�j���[�V�����f�[�^�̓ǂݍ���
	std::unique_ptr<WataLib::Json> json = std::make_unique<WataLib::Json>();

	m_animationDatas["Idle"] = json->LoadAnimationData(L"Player/Idle");
	m_animationDatas["Move"] = json->LoadAnimationData(L"Player/Move");
	m_animationDatas["GetReady"] = json->LoadAnimationData(L"Player/GetReady");
	m_animationDatas["Throw"] = json->LoadAnimationData(L"Player/Throw");


	//�e�p�[�c�ɃA�j���[�V������o�^
	SetAnimationData("Idle", m_animationDatas,"", true);
	this->SetAnimationData("Move", m_animationDatas);
	SetAnimationData("GetReady", m_animationDatas);
	SetAnimationData("Throw", m_animationDatas);

	//������
	m_usually->Initialize(BaseEntity::GetCommonResources());
	m_stateMachine->Initialize(BaseEntity::GetCommonResources(), m_stateMachine->GetPlayerIdle());

	for (auto& boomerang : m_boomerangs)
	{
		boomerang->Initialize();
	}



	//�����蔻��̍쐬
	CollisionEntity::GetBounding()->CreateBoundingSphere(BaseEntity::GetPosition(), Params::PLAYER_SPHERE_COLLIDER_SIZE);
	CollisionEntity::GetBounding()->CreateBoundingBox(BaseEntity::GetPosition(), Params::PLAYER_BOX_COLLIDER_SIZE);


	auto device = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDevice();
	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();


	m_shadow->Initialize(device, context, states);


}




/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
void Player::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection)
{
	//�I�u�W�F�N�g���`�悪�����Ȃ�
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsRenderActive())
	{
		return;
	}

	CompositeEntity::Render(view, projection);


	//�p�[�c�̕`��
	for (auto& part : CompositeEntity::GetParts())
	{
		part->Render(view,projection);
	}

	for (auto& boomerang : m_boomerangs)
	{
		boomerang->Render(view, projection);
	}


	DirectX::SimpleMath::Vector3 shadowPos = BaseEntity::GetPosition();
	shadowPos.y = Params::SHADOW_POSITION_Y;

	auto context = BaseEntity::GetCommonResources()->GetDeviceResources()->GetD3DDeviceContext();
	auto states = BaseEntity::GetCommonResources()->GetCommonStates();



	// ���@�̉e��`�悷��
	m_shadow->Render(context, states, view, projection, shadowPos, Params::PLAYER_SHADOW_RADIUS);


}

/// <summary>
/// �����蔻��N���X�ɒǉ�
/// </summary>
/// <param name="collsionManager">�����蔻��N���X</param>
void Player::AddCollision(CollisionManager* collsionManager)
{
	CollisionEntity::AddCollision(collsionManager);


	for (auto& boomerang : m_boomerangs)
	{
		boomerang->AddCollision(collsionManager);
	}

}

/// <summary>
/// �����������ɌĂяo�����֐�
/// </summary>
/// <param name="object">����̃I�u�W�F�N�g</param>
/// <param name="tag">����̃^�O</param>
void Player::OnCollisionEnter(CollisionEntity* object, CollisionTag tag)
{
	UNREFERENCED_PARAMETER(object);

	switch (tag)
	{
		case CollisionEntity::CollisionTag::BEAM:
		case CollisionEntity::CollisionTag::ENEYPARTS:
			m_hp--;
			//Subject::Notify(EventManager::EventTypeName::PlayerDamage);


			//�v���C���̃_���[�W�̒ʒm
			Messenger::GetInstance()->Notify(::GameMessageType::PLAYER_DAMAGE);
			

			if (m_hp <= 0)
			{
				//Subject::Notify(EventManager::EventTypeName::GameOver);
				Messenger::GetInstance()->Notify(::GameMessageType::GAME_OVER);
			}
			break;
		default:
			break;
	}



}


void Player::OnCollisionStay(CollisionEntity* object, CollisionTag tag)
{
	UNREFERENCED_PARAMETER(object);

	switch (tag)
	{
		case CollisionEntity::CollisionTag::STAGE:
		{
			Vector3 velocity = BaseEntity::GetVelocity();

			velocity.y = 0.0f;

			BaseEntity::SetVelocity(velocity);
		}
		break;
		default:
			break;
	}



}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="elapsedTime">�o�ߎ���</param>
void Player::Update(const float& elapsedTime)
{

	//�I�u�W�F�N�g���X�V�������Ȃ�
	if (!BaseEntity::GetIsEntityActive() || !BaseEntity::GetIsUpdateActive())
	{
		return;
	}

	m_stateMachine->Update(elapsedTime);

	m_usually->Update(elapsedTime);

	CompositeEntity::Update(elapsedTime);


	//�p�[�c�̍X�V
	for (auto& part : CompositeEntity::GetParts())
	{
		part->Update(elapsedTime);
	}

	for (auto& boomerang : m_boomerangs)
	{
		boomerang->Update(elapsedTime);
	}

}



/// <summary>
/// �A�j���[�V�����̓o�^
/// </summary>
/// <param name="animationType">�A�j���[�V�����̎��</param>
/// <param name="datas">�A�j���[�V�����f�[�^</param>
/// <param name="isNormalAnimation">�ʏ�A�j���[�V�������ǂ���</param>
void Player::SetAnimationData(std::string animationType
	, std::unordered_map<std::string, std::unordered_map<std::string, WataLib::Json::AnimationData>> datas
	, const std::string& partsName
	, bool isNormalAnimation )
{
	CharacterEntity::SetAnimationData(animationType, datas, partsName , isNormalAnimation);

	//�p�[�c�ɃA�j���[�V������o�^
	for (auto& part : CompositeEntity::GetParts())
	{
		part->SetAnimationData(animationType, datas,partsName , isNormalAnimation);
	}
}

/// <summary>
/// �A�j���[�V�����̕ύX
/// </summary>
/// <param name="animationType">�A�j���[�V�����̎��</param>
void Player::ChangeAnimation(std::string animationType)
{
	CharacterEntity::ChangeAnimation(animationType);
	//�p�[�c�̃A�j���[�V������ύX
	for (auto& part : CompositeEntity::GetParts())
	{
		part->ChangeAnimation(animationType);
	}

}




