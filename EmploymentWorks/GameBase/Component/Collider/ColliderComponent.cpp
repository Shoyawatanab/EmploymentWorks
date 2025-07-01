#include "pch.h"
#include "ColliderComponent.h"
#include "GameBase/Actor.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Managers.h"
#include "GameBase/Common/Commons.h"
#include "Libraries/Microsoft/DebugDraw.h"


/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="owner">���L��</param>
/// <param name="tag">�����蔻��̎��</param>
/// <param name="type">����̎��</param>
ColliderComponent::ColliderComponent(Actor* owner, ColliderTag tag, CollisionType type)
	:
	Component(owner)
	,m_collisionTag{tag}
	,m_collisionType{type}
	, m_offsetPosition{ DirectX::SimpleMath::Vector3::Zero }
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

/// <summary>
/// �X�V����
/// </summary>
/// <param name="deltaTime">�o�ߎ���</param>
void ColliderComponent::Update(const float& deltaTime)
{

	//�h����X�V����
	UpdateCollider();

}

/// <summary>
/// �`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
/// <param name="batch">�v���~�e�B�u�o�b�`</param>
/// <param name="effect">�x�[�V�b�N�G�t�F�N�g</param>
/// <param name="inputlayout">�C���v�b�g���C�A�E�g</param>
void ColliderComponent::Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection
	,DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch, DirectX::BasicEffect* effect, ID3D11InputLayout* inputlayout)
{
	//�h����̕`�揈��
	RenderCollider(view, projection, batch, effect, inputlayout);
}

/// <summary>
/// ���������R���C�_�[�̍폜
/// </summary>
/// <param name="object">�R���|�[�l���g</param>
/// <returns>true�F�폜�ł����@false�F�ł��Ȃ�����</returns>
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
	UpdateCollider();

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
	,m_initialExtents{extents}
	,m_initialRadius{radius}
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

/// <summary>
/// �f�X�g���N�^
/// </summary>
AABB::~AABB()
{
}

/// <summary>
/// �ʍX�V����
/// </summary>
void AABB::UpdateCollider()
{

	BoxUpdate();
	
	SphereUpdate();

}



/// <summary>
/// �����蔻��̕`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
/// <param name="batch">�v���~�e�B�u�o�b�`</param>
/// <param name="effect">�x�[�V�b�N�G�t�F�N�g</param>
/// <param name="inputlayout">�C���v�b�g���C�A�E�g</param>
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

/// <summary>
/// �{�b�N�X�̍X�V
/// </summary>
void AABB::BoxUpdate()
{
	auto scale = GetActor()->GetTransform()->GetWorldScale();
	//�傫���̍X�V
	m_boundingBox->Extents = GetInitialExtents() * scale;
	//���W�̍X�V
	m_boundingBox->Center = GetActor()->GetTransform()->GetRotatePosition() + OffsetPosition();

}

/// <summary>
/// �X�t�B�A�̍X�V
/// </summary>
void AABB::SphereUpdate()
{
	//���W�̍X�V
	m_boundingSphere->Center = GetActor()->GetTransform()->GetRotatePosition() + OffsetPosition();
	auto scale = GetActor()->GetTransform()->GetWorldScale();
	//�傫���̍X�V
	m_boundingSphere->Radius = GetInitialRaduis() * std::max({ scale.x,scale.y,scale.z });

}

/// <summary>
/// �o�E���f�B���O�{�b�N�X�̎擾
/// </summary>
/// <returns></returns>
DirectX::BoundingBox* AABB::GetBoundingBox()
{
	BoxUpdate();

	return m_boundingBox.get();
}


/// <summary>
/// �o�E���f�B���O�X�t�B�A�̎擾
/// </summary>
/// <returns></returns>
DirectX::BoundingSphere* AABB::GetBoundingSphere()
{
	
	SphereUpdate();

	return m_boundingSphere.get();
}



/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="owner">���L��</param>
/// <param name="tag">�����蔻��̎��</param>
/// <param name="type">����̎��</param>
/// <param name="position">���S���W</param>
/// <param name="extents">�o�E���f�B���O�{�b�N�X�̑傫��</param>
/// <param name="rotation">�o�E���f�B���O�{�b�N�X�̉�]</param>
/// <param name="radius">�o�E���f�B���O�X�t�B�A�̑傫��</param>
OBB::OBB(Actor* owner, ColliderTag tag, CollisionType type
	, const DirectX::SimpleMath::Vector3& extents
	, DirectX::SimpleMath::Quaternion rotation
	, const float& radius)
	:
	ColliderComponent(owner,tag,type)
	, m_initialExtents{ extents }
	, m_initialRadius{ radius }
{

	using namespace DirectX;

	//�o�E���f�B���O�{�b�N�X��̍쐬
	m_boundingOrientedBox = std::make_unique<BoundingOrientedBox>();
	//�傫���̐ݒ�
	m_boundingOrientedBox->Extents = extents;
	//��]�̐ݒ�
	m_boundingOrientedBox->Orientation = rotation;

	//�o�E���f�B���O�X�t�B�A�̍쐬
	m_boundingSphere = std::make_unique<BoundingSphere>();
	//�傫���̐ݒ�
	m_boundingSphere->Radius = radius;


}

/// <summary>
/// �f�X�g���N�^
/// </summary>
OBB::~OBB()
{
}

/// <summary>
/// �R���C�_�[�̍X�V
/// </summary>
void OBB::UpdateCollider()
{

	BoxUpdate();

	SphereUpdate();

}

/// <summary>
/// �����蔻��̕`��
/// </summary>
/// <param name="view">�r���[�s��</param>
/// <param name="projection">�ˉe�s��</param>
/// <param name="batch">�v���~�e�B�u�o�b�`</param>
/// <param name="effect">�x�[�V�b�N�G�t�F�N�g</param>
/// <param name="inputlayout">�C���v�b�g���C�A�E�g</param>
void OBB::RenderCollider(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection, DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* batch, DirectX::BasicEffect* effect, ID3D11InputLayout* inputlayout)
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
	DX::Draw(batch, *m_boundingOrientedBox, color);
	// �v���~�e�B�u�`����I������
	batch->End();

#endif


}

/// <summary>
/// �{�b�N�X�̍X�V
/// </summary>
void OBB::BoxUpdate()
{
	//���W�̍X�V
	m_boundingOrientedBox->Center = GetActor()->GetTransform()->GetRotatePosition() + OffsetPosition();
	auto scale = GetActor()->GetTransform()->GetWorldScale();
	//�傫���̍X�V
	m_boundingOrientedBox->Extents = GetInitialExtents() * scale;
	//��]�̍X�V
	m_boundingOrientedBox->Orientation = GetActor()->GetTransform()->GetWorldRotate();

}

/// <summary>
/// �X�t�B�A�̍X�V
/// </summary>
void OBB::SphereUpdate()
{
	//���W�̍X�V
	m_boundingSphere->Center = GetActor()->GetTransform()->GetRotatePosition() + OffsetPosition();
	auto scale = GetActor()->GetTransform()->GetWorldScale();
	//�傫���̍X�V
	m_boundingSphere->Radius = GetInitialRaduis() * std::max({ scale.x,scale.y,scale.z });


}


/// <summary>
/// �o�E���f�B���O�{�b�N�X�̎擾
/// </summary>
/// <returns></returns>
DirectX::BoundingOrientedBox* OBB::GetBoundingOrientedBox()
{
	BoxUpdate();
	return m_boundingOrientedBox.get();
}

/// <summary>
/// �o�E���f�B���O�X�t�B�A�̎擾
/// </summary>
/// <returns></returns>
DirectX::BoundingSphere* OBB::GetBoundingSphere()
{
	SphereUpdate();
	return m_boundingSphere.get();
}





