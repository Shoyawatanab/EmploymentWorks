/*
	@file	Player.cpp
	@brief	�v���C�V�[���N���X
*/
#include "pch.h"
#include "Player.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

const float MOVE_SPEED = 5.0f;                                        //�������̃X�s�[�h
const DirectX::SimpleMath::Vector3 INITIAL_DIRECTION( 0.0f,0.0f,-1.0f); //�����̌����Ă������
//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Player::Player()
	:
	m_commonResources{},
	m_model{},
	m_position{},
	m_direction{INITIAL_DIRECTION},
	m_boomerang{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Player::~Player()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Player::Initialize(CommonResources* resources, DirectX::SimpleMath::Vector3 position)
{
	using namespace DirectX::SimpleMath;


	assert(resources);
	m_commonResources = resources;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();




	// ���f����ǂݍ��ޏ���
	std::unique_ptr<DirectX::EffectFactory> fx = std::make_unique<DirectX::EffectFactory>(device);
	fx->SetDirectory(L"Resources/Models");

	// ���f����ǂݍ���
	m_model = DirectX::Model::CreateFromCMO(device, L"Resources/Models/Player.cmo", *fx);

	m_position = position;

	m_boomerang = std::make_unique<Boomerang>(this);
	m_boomerang->Initialize(m_commonResources);

}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Player::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);


	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	// �L�[�{�[�h�X�e�[�g���擾����
	DirectX::Keyboard::State key = DirectX::Keyboard::Get().GetState();

	Vector3 moveDirection = Vector3::Zero;

	if (key.IsKeyDown(Keyboard::Keyboard::Up))
	{
		moveDirection.z--;
	}
	if (key.IsKeyDown(Keyboard::Keyboard::Down))
	{
		moveDirection.z++;
	}
	if (key.IsKeyDown(Keyboard::Keyboard::Left))
	{
		moveDirection.x--;
	}
	if (key.IsKeyDown(Keyboard::Keyboard::Right))
	{
		moveDirection.x++;
	}

	
	Rotate(elapsedTime, moveDirection);

	Move(elapsedTime, moveDirection);
	Attack(elapsedTime, key);






	m_boomerang->Update(elapsedTime);

}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Player::Render(DirectX::CXMMATRIX view, DirectX::CXMMATRIX projection)
{
	using namespace DirectX::SimpleMath;

	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();


	// ���[���h�s����X�V����
	Matrix world = Matrix::CreateScale(0.3f);
	world *= Matrix::CreateFromQuaternion(m_rotate);
	world *= Matrix::CreateTranslation(m_position);


	// ���f����`�悷��
	m_model->Draw(context, *states, world, view, projection);

	m_boomerang->Render(view, projection);



}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Player::Finalize()
{
	// do nothing.
}


void Player::Move(float elapsedTime, DirectX::SimpleMath::Vector3 moveDirection)
{
	using namespace DirectX::SimpleMath;

	if (moveDirection == Vector3::Zero)
	{
		return;
	}

	moveDirection ;
	m_position += moveDirection *= MOVE_SPEED * elapsedTime;

}

void Player::Attack(float elapsedTime, DirectX::Keyboard::State key)
{
	if (key.Space)
	{
		m_boomerang->ChangeState(m_boomerang->GetBoomerangThrow());
	}

}


void Player::Rotate(float elapsedTime, DirectX::SimpleMath::Vector3 moveDirection)
{

	using namespace DirectX::SimpleMath;

	if (moveDirection == Vector3::Zero)
	{
		return;
	}

	moveDirection.Normalize();
	//���݂̌����Ɠ����������玲�����
	Vector3 axis = moveDirection.Cross(m_direction);


	if (axis == Vector3::Zero)
	{
		axis = Vector3::UnitY;
	}

	//
	axis *= -1;


	float  angle = Vector3::Distance(moveDirection, m_direction);
	angle *= elapsedTime * 10.0f ;
	Quaternion rotation = m_rotate;
	rotation *=	Quaternion::CreateFromAxisAngle(axis,angle);

	m_rotate = rotation;


	m_direction = Vector3::Transform(INITIAL_DIRECTION, rotation);
	
	m_direction.Normalize();
}