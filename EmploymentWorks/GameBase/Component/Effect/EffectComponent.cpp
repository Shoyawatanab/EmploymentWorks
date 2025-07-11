/*
	�N���X��     : EffectComponent
	����         : �G�t�F�N�g�R���|�[�l���g
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "EffectComponent.h"
#include "GameBase/Actor.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Managers.h"



/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="owner">���L��</param>
/// <param name="renderFunction">�`��֐�</param>
EffectComponent::EffectComponent(Actor* owner, std::function<void(const Camera& camera)> renderFunction)
	:
	Component(owner)
	,m_renderFunction{renderFunction}
{

	using namespace DirectX;


	//�}�l�[�W���[�ɒǉ�
	GetActor()->GetScene()->GetRenderMangaer()->AddEffect(this);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
EffectComponent::~EffectComponent()
{
}

/// <summary>
/// �`��
/// </summary>
/// <param name="camera">�J����</param>
void EffectComponent::Render(const Camera& camera)
{
	//�ʕ`��
	m_renderFunction(camera);
}


