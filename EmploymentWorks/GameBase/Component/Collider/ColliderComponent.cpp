#include "pch.h"
#include "ColliderComponent.h"
#include "GameBase/Actor.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Managers.h"
#include "Game/CommonResources.h"
#include "DeviceResources.h"
#include "Libraries/Microsoft/DebugDraw.h"



ColliderComponent::ColliderComponent(Actor* owner, ColliderTag tag, CollisionType type)
	:
	Component(owner)
	,m_collisionTag{tag}
	,m_collisionType{type}
{
	//�}�l�[�W���[�̎擾
	auto collisitionManager = GetActor()->GetScene()->GetCollisionManager();
	//�}�l�[�W���[�ɒǉ�
	collisitionManager->AddCollider(this);
	//�}�l�[�W���[�̎擾
	auto renderManager = GetActor()->GetScene()->GetRenderMangaer();
	//�}�l�[�W���[�ɒǉ�
	renderManager->AddCollider(this);

}


/// <summary>
/// �f�X�g���N�^
/// </summary>
ColliderComponent::~ColliderComponent()
{
	//�폜
	auto collisionManager = GetActor()->GetScene()->GetCollisionManager();
	collisionManager->RemoveCollider(this);


}

void ColliderComponent::Update(const float& deltaTime)
{

	//�h����X�V����
	UpdateCollider();

}

void ColliderComponent::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection
	,DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch, DirectX::BasicEffect* effect, ID3D11InputLayout* inputlayout)
{
	//�h����̕`�揈��
	RenderCollider(view, projection, batch, effect, inputlayout);
}


bool ColliderComponent::DleteHitObject(ColliderComponent* object)
{
	size_t initialSize = m_hitCollider.size();
	//�I�u�W�F�N�g������΍폜
	m_hitCollider.erase(std::remove(m_hitCollider.begin(), m_hitCollider.end(), object), m_hitCollider.end());
	//�폜�ł������ǂ���
	if (m_hitCollider.size() < initialSize)
	{
		//�폜�ł�����
		return true;
	}
	return false;
};


/// <summary>
/// �����o������
/// </summary>
/// <param name="pushBack">�����o���x�N�g��</param>
void ColliderComponent::SetPushBack(DirectX::SimpleMath::Vector3 pushBackVector)
{
	//�I�u�W�F�N�g�̉����o��
	GetActor()->GetTransform()->Translate(pushBackVector);
	//�h����̃o�E���f�B���O�̍X�V
	PositionUpdate();

}



/// <summary>
/// �R���X�g���N�^
/// </summary>
/// <param name="owner">���L��</param>
/// <param name="tag">�����蔻��̎��</param>
/// <param name="type">����̎��</param>
/// <param name="position">���S���W</param>
/// <param name="extents">�o�E���f�B���O�{�b�N�X�̑傫��</param>
/// <param name="radius">�o�E���f�B���O�X�t�B�A�̑傫��</param>
AABB::AABB(Actor* owner, ColliderTag tag, CollisionType type
	, const DirectX::SimpleMath::Vector3& extents
	, const float& radius)
	:
	ColliderComponent(owner,tag,type)
{
	
	using namespace DirectX;

	//�o�E���f�B���O�{�b�N�X��̍쐬
	m_boundingBox = std::make_unique<BoundingBox>();
	//�傫���̐ݒ�
	m_boundingBox->Extents = extents;

	//�o�E���f�B���O�X�t�B�A�̍쐬
	m_boundingSphere = std::make_unique<BoundingSphere>();
	//�傫���̐ݒ�
	m_boundingSphere->Radius = radius;


}

AABB::~AABB()
{
}

/// <summary>
/// �ʍX�V����
/// </summary>
void AABB::UpdateCollider()
{
	//���W�̍X�V
	m_boundingBox->Center = GetActor()->GetTransform()->GetPosition();
	m_boundingSphere->Center = GetActor()->GetTransform()->GetPosition();
}


void AABB::RenderCollider(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection
	,DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch, DirectX::BasicEffect* effect, ID3D11InputLayout* inputlayout)
{

	auto context = CommonResources::GetInstance()->GetDeviceResources()->GetD3DDeviceContext();
	effect->SetView(view);
	effect->SetProjection(projection);
	effect->Apply(context);

	auto states = CommonResources::GetInstance()->GetCommonStates();
	context->OMSetBlendState(states->Opaque(), nullptr, 0xFFFFFFFF);	// ���߂��Ȃ�
	context->OMSetDepthStencilState(states->DepthDefault(), 0);			// �y�o�b�t�@���g�p����
	context->RSSetState(states->CullNone());							// �|���S���̗��ʂ�`�悷��
	context->IASetInputLayout(inputlayout);							// ���̓��C�A�E�g��ݒ肷��

	DirectX::XMVECTOR color = DirectX::Colors::Yellow;


#ifdef _DEBUG
	// �v���~�e�B�u�`����J�n����
	batch->Begin();

	// ���E�X�t�B�A��`�悷��
	DX::Draw(batch, *m_boundingSphere, color);
	DX::Draw(batch, *m_boundingBox, color);
	// �v���~�e�B�u�`����I������
	batch->End();

#endif

}

void AABB::PositionUpdate()
{
	//���W�̍X�V
	m_boundingBox->Center = GetActor()->GetTransform()->GetPosition();
	m_boundingSphere->Center = GetActor()->GetTransform()->GetPosition();

}






