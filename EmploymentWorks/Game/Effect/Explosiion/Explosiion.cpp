#include "pch.h"
#include "Explosiion.h"
#include "GameBase/Component/Components.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Common/Commons.h"
#include "GameBase/Camera/Camera.h"


/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
Explosiion::Explosiion(Scene* scene)
	:
	Actor(scene)
	,m_animationKey{}
	,m_basicEffect{}
	,m_billboardMat{}
	,m_frameCounter{}
	,m_inputLayout{}
{
	using namespace DirectX;
	using namespace DirectX::SimpleMath;


	AddComponent<EffectComponent>(this, std::bind(&Explosiion::Render, this, std::placeholders::_1));



	//�f�o�C�X�̎擾
	auto device = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDevice();
	//�R���e�L�X�g�̎擾
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();

	// �|���S����ݒ肷��
	// �um_vertices[i].position�v�̓R���X�g���N�^�Ń[���������ς�
	// �����ł�UV���W���w�肵�Ă���F�����l
	m_vertices[0].textureCoordinate = Vector2(0.0f, 0.0f);	// ����
	m_vertices[1].textureCoordinate = Vector2(1.0f, 0.0f);	// �E��
	m_vertices[2].textureCoordinate = Vector2(0.0f, 1.0f);	// ����
	m_vertices[3].textureCoordinate = Vector2(1.0f, 1.0f);	// �E��

	// �|���S���`��̏���----------------------------------
	// �x�[�V�b�N�G�t�F�N�g��ݒ肷��
	m_basicEffect = std::make_unique<BasicEffect>(device);
	m_basicEffect->SetTextureEnabled(true);	// �e�N�X�`����L����

	// ���̓��C�A�E�g��ݒ肷��
	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect<VertexPositionTexture>(
			device,
			m_basicEffect.get(),
			m_inputLayout.ReleaseAndGetAddressOf()
		)
	);

	// �v���~�e�B�u�o�b�`�𐶐�����
	m_primitiveBatch = std::make_unique<PrimitiveBatch<VertexPositionTexture>>(context);

	// �摜��ǂݍ���
	DX::ThrowIfFailed(
		CreateWICTextureFromFile(
			device,
			L"Resources/Textures/Explosion.png",
			nullptr,
			m_texture.ReleaseAndGetAddressOf()
		)
	);

	SetActive(false);

}

Explosiion::~Explosiion()
{
}

/// <summary>
/// �ʃA�b�v�f�[�g
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void Explosiion::UpdateActor(const float& deltaTime)
{

	// �t���[���J�E���^
	m_frameCounter++;

	// �A�j���[�V�����̐؂�ւ�����
	if (m_frameCounter > ANIMATION_INTERVAL)
	{
		m_frameCounter = 0;		// �t���[���J�E���^�����Z�b�g����
		m_animationKey++;		// �A�j���[�V�����̃L�[��i�߂�

		//�A�j���[�V�����̏I��
		if (m_animationKey >= 10)
		{
			SetActive(false);
			m_animationKey = 0;
		}

	}


}



/// <summary>
/// �`��
/// </summary>
/// <param name="camera">�J����</param>
void Explosiion::Render(const Camera& camera)
{

	using namespace DirectX::SimpleMath;

	//�R���e�L�X�g�̎擾
	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	//�R�����X�e�[�g�̎����
	auto states = CommonResources::GetInstance()->GetCommonStates();

	auto view = camera.GetViewMatrix();
	auto prijection = camera.GetProjectionMatrix();

	// �r���{�[�h�}�g���b�N�X���v�Z����
	m_billboardMat = view.Invert();
	m_billboardMat._41 = 0.0f;
	m_billboardMat._42 = 0.0f;
	m_billboardMat._43 = 0.0f;



	// �|���S����`�悷�鏀��------------------------------------
	// �f�o�C�X�R���e�L�X�g�̃p�����[�^��ύX����
	// �A���t�@�u�����h��K�p����
	context->OMSetBlendState(states->AlphaBlend(), nullptr, 0xffffffff);

	// �`��ɐ[�x�l��K�p����
	context->OMSetDepthStencilState(states->DepthDefault(), 0);

	// ���ʃJ�����O�i�����v���ʂ�`�悵�Ȃ��j��ݒ肷��
	context->RSSetState(states->CullNone());

	// �e�N�X�`���T���v���Ƀ��j�A�N�����v��K�p����
	ID3D11SamplerState* sampler = states->LinearClamp();
	context->PSSetSamplers(0, 1, &sampler);

	// ���̓��C�A�E�g��K�p����
	context->IASetInputLayout(m_inputLayout.Get());


	// �|���S����`�悷��----------------------------------
	// �|���S���̃p�����[�^��ݒ肷��
	float radius = 0.40f;


	// �|���S���̒��_����ݒ肷��F�r���{�[�h�s����g�����߁AXY���ʂɂ��Ă���
	m_vertices[0].position = Vector3(-radius, radius, 0.0f);
	m_vertices[1].position = Vector3(radius, radius, 0.0f);
	m_vertices[2].position = Vector3(-radius, -radius, 0.0f);
	m_vertices[3].position = Vector3(radius, -radius, 0.0f);

	// �|���S����UV���W��ݒ肷��F�A�j���[�V�����Ή�
	m_vertices[0].textureCoordinate = Vector2(ANIMATION_SIZE * m_animationKey, 0.0f);	// ����
	m_vertices[1].textureCoordinate = Vector2(ANIMATION_SIZE * m_animationKey + ANIMATION_SIZE, 0.0f);	// �E��
	m_vertices[2].textureCoordinate = Vector2(ANIMATION_SIZE * m_animationKey, 1.0f);	// ����
	m_vertices[3].textureCoordinate = Vector2(ANIMATION_SIZE * m_animationKey + ANIMATION_SIZE, 1.0f);	// �E��

	// �r���{�[�h�s��������������[���h�s����v�Z����
	Matrix world;
	world *= Matrix::CreateScale((SCALE * GetTransform()->GetWorldScale()));
	world *= m_billboardMat;
	world *= Matrix::CreateTranslation(GetTransform()->GetWorldPosition());

	// �x�[�V�b�N�G�t�F�N�g��ݒ肵�K�p����
	m_basicEffect->SetWorld(world);	// ���[���h�s��
	m_basicEffect->SetView(view);				// �r���[�s��
	m_basicEffect->SetProjection(prijection);	// �ˉe�s��
	m_basicEffect->SetTexture(m_texture.Get());	// �e�N�X�`��
	m_basicEffect->Apply(context);				// �ύX��K�p����

	// �|���S����`�悷��
	m_primitiveBatch->Begin();
	m_primitiveBatch->DrawQuad(m_vertices[0], m_vertices[1], m_vertices[3], m_vertices[2]);
	m_primitiveBatch->End();


}

/// <summary>
/// �A�N�e�B�u��ԂɂȂ�����
/// </summary>
void Explosiion::OnEnable()
{
	m_frameCounter = 0;
	m_animationKey = 0;
}
