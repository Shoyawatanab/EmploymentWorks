/*
	@file	Artillery.cpp
	@brief	
*/
#include "pch.h"
#include "Artillery.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/MyLib/DebugCamera.h"
#include "Libraries/MyLib/DebugString.h"
#include "Libraries/MyLib/GridFloor.h"
#include "Libraries/MyLib/InputManager.h"
#include "Libraries/MyLib/MemoryLeakDetector.h"
#include <cassert>

#include "Game/DetectionCollision/CollisionManager.h"
#include "Libraries/MyLib/Bounding.h"

#include "Game/Object/Gimmick/Artillery/ArtilleryBase.h"
#include "Game/Object/Gimmick/Artillery/ArtilleryTurret.h"

const float SCALE(8.6f);

//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
Artillery::Artillery()
	:
	m_commonResources{}
	,m_scale{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
Artillery::~Artillery()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void Artillery::Initialize(CommonResources* resources, PlayScene* playScene, DirectX::SimpleMath::Vector3 position, DirectX::SimpleMath::Vector3 Scale, DirectX::SimpleMath::Vector3 Rotate, float BoundingSphereRadius)
{
	using namespace DirectX::SimpleMath;
	using namespace DirectX;
	assert(resources);
	m_commonResources = resources;

	auto device = m_commonResources->GetDeviceResources()->GetD3DDevice();
	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	//auto states = m_commonResources->GetCommonStates();



	m_position = position;
	m_scale = Scale;
	m_rotate = Quaternion::CreateFromYawPitchRoll(DirectX::XMConvertToRadians(Rotate.x), DirectX::XMConvertToRadians(Rotate.y), DirectX::XMConvertToRadians(Rotate.z));





	m_bounding = std::make_unique<Bounding>();
	m_bounding->CreateBoundingBox(m_commonResources, m_position, m_scale * 0.7f);
	m_bounding->CreateBoundingSphere(m_commonResources,m_position, BoundingSphereRadius );

	m_base = std::make_unique<ArtilleryBase>();
	m_base->Initialize(m_commonResources, m_position, m_scale, Quaternion::Identity);

	m_turret = std::make_unique<ArtilleryTurret>();
	m_turret->Initialize(m_commonResources,playScene, m_position, m_scale, m_rotate);


	/*
	�r���{�[�h�̕`��Ɋ֘A����I�u�W�F�N�g��ݒ肷��
*/
// �x�[�V�b�N�G�t�F�N�g���쐬����
	m_basicEffect = std::make_unique<BasicEffect>(device);
	m_basicEffect->SetTextureEnabled(true);	// �e�N�X�`�����g�p����
	/*
		�E�x�[�V�b�N�G�t�F�N�g�́uSet����Enabled�v�͕K�v�Ȃ��̂����utrue�v�ɐݒ肷��
		�E�s�v�Ȃ��͎̂w�肵�Ȃ��Ă悢�i�f�t�H���g�Łufalse�v�ɐݒ肳���j
	*/

	// ���̓��C�A�E�g���쐬����
	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect<VertexPositionTexture>(
			device,
			m_basicEffect.get(),
			m_inputLayout.ReleaseAndGetAddressOf()
		)
	);

	// �v���~�e�B�u�o�b�`���쐬����
	m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionTexture>>(context);
	/*
		�E�u�|���S���̒��_���v�u���̓��C�A�E�g�̒��_���v�u�v���~�e�B�u�o�b�`�̒��_���v�𓝈ꂷ��
	*/

	// �摜�����[�h����
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(
			device,
			L"Resources/Textures/ArtilleryIcon.png",
			nullptr,
			m_texture.ReleaseAndGetAddressOf()
		)
	);

	DirectX::SimpleMath::Vector3 scale = Vector3(2, 2, 0);


	// �r���{�[�h�̒��_����ݒ肷��F����́uVertexPositionTexture�v���g�p����
	m_vertices[0] = { Vector3(-0.5f * scale.x, 0.5f * scale.y,0.0f),Vector2(0.0f,0.0f) };	// ����
	m_vertices[1] = { Vector3(0.5f * scale.x, 0.5f * scale.y,0.0f),Vector2(1.0f,0.0f) };	// �E��
	m_vertices[2] = { Vector3(-0.5f * scale.x,-0.5f * scale.y,0.0f),Vector2(0.0f,1.0f) };	// ����
	m_vertices[3] = { Vector3(0.5f * scale.x,-0.5f * scale.y,0.0f),Vector2(1.0f,1.0f) };	// �E��





}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void Artillery::Update(float elapsedTime)
{
	UNREFERENCED_PARAMETER(elapsedTime);


	using namespace DirectX;
	using namespace DirectX::SimpleMath;

	m_base->Update(elapsedTime);

	m_turret->Update(elapsedTime);

}

//---------------------------------------------------------
// �`�悷��
//---------------------------------------------------------
void Artillery::Render(DirectX::SimpleMath::Matrix view, DirectX::SimpleMath::Matrix projection)
{
	using namespace DirectX::SimpleMath;


	auto context = m_commonResources->GetDeviceResources()->GetD3DDeviceContext();
	auto states = m_commonResources->GetCommonStates();


	// ���[���h�s����X�V����
	Matrix world = Matrix::CreateScale(m_scale);
	world *= Matrix::CreateFromQuaternion(m_rotate);
	world *= Matrix::CreateTranslation(m_position);



	m_bounding->DrawBoundingSphere(m_position, view, projection);
	m_bounding->DrawBoundingBox(m_position, view, projection);

	m_base->Render(view, projection);
	m_turret->Render(view, projection);


	// �r���{�[�h���A�t�B���s������
	Matrix billboardMatrix = view.Invert();
	billboardMatrix._41 = 0.0f;
	billboardMatrix._42 = 0.0f;
	billboardMatrix._43 = 0.0f;
	/*
		���r���{�[�h�s��̋��ߕ�
		�E�g�p����r���[�s��̋t�s������߂�
		�E���s�ړ������L�����Z������
	*/

	// �r���{�[�h�́i���_����́j���s�ړ���
	Vector3 billboardTranslationValue{ 0.0f, 1.0f, 0.0f };

	// �r���{�[�h���A�t�B���ϊ�����
	Matrix worldBillboard{};
	worldBillboard = billboardMatrix;										// A
	worldBillboard *= Matrix::CreateTranslation(m_position + Vector3(0,4,0));	// B
	/*
		���r���{�[�h�ƃ��[���h�s��
		�E�܂��A���[���h�s��Ƀr���{�[�h�s���������::A
		�E���ɁA�r���{�[�h�̍����𒲐�����::B
		�E�c��̓T�C�R���̃A�t�B���ϊ����Q�l�ɕϊ��s����v�Z����

		���T�C�R���̉�]�ƃr���{�[�h�̉�]�̑��֊֌W
		�E�@�̉�]�͇B�C�̉�]�ɉe�����Ȃ����P�{
		�E�A�̉�]�͇B�C�̉�]�ɉe�����遨���ꂼ�ꓯ���{�ɂ���
	*/

	// �|���S����`�悷�邽�߂Ɋe��p�����[�^��ݒ肷��
	context->OMSetBlendState(states->NonPremultiplied(), nullptr, 0xFFFFFFFF);	// Trident���S�́uNonPremultiplied�v
	context->OMSetDepthStencilState(states->DepthDefault(), 0);					// �[�x����read��write
	context->RSSetState(states->CullCounterClockwise());						// �|���S���̗��ʂ͕`�悵�Ȃ�
	context->IASetInputLayout(m_inputLayout.Get());								// �K�؂ȓ��̓��C�A�E�g���w�肷��

	m_basicEffect->SetWorld(worldBillboard);	// ���[���h�s����w�肷��
	m_basicEffect->SetView(view);				// �r���[�s����w�肷��
	m_basicEffect->SetProjection(projection);	// �ˉe�s����w�肷��
	m_basicEffect->SetTexture(m_texture.Get());	// �e�N�X�`�����w�肷��
	m_basicEffect->Apply(context);				// �x�[�V�b�N�G�t�F�N�g�̕ύX��K�p����

	// �r���{�[�h��`�悷��
	m_primitiveBatch->Begin();
	m_primitiveBatch->DrawQuad(m_vertices[0], m_vertices[1], m_vertices[3], m_vertices[2]);
	m_primitiveBatch->End();

}

//---------------------------------------------------------
// ��n������
//---------------------------------------------------------
void Artillery::Finalize()
{
	// do nothing.
}


void Artillery::RegistrationCollionManager(CollisionManager* collsionManager)
{
	collsionManager->AddCollsion(this);

	//Turre�̒��ɂ���Bullet�̓����蔻��̓o�^�@Turret�ɔ���͂Ȃ�
	m_turret->RegistrationCollionManager(collsionManager);
}



void Artillery::OnCollisionEnter(CollsionObjectTag& PartnerTag, DirectX::SimpleMath::Vector3 Pos)
{
	UNREFERENCED_PARAMETER(PartnerTag);
	UNREFERENCED_PARAMETER(Pos);

	switch (PartnerTag)
	{
		case CollsionObjectTag::Boomerang:
			m_turret->Shot();
			break;
		default:
			break;
	}

}

