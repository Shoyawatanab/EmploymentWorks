/*
	�N���X��     : Canvas
	����         : UI�L�����o�X�̊��N���X
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "Canvas.h"
#include "GameBase/Scene/Scene.h"
#include "GameBase/Manager/RenderManager.h"

/// <summary>
/// �R���X�g���N
/// </summary>
/// <param name="scene">�V�[��</param>
/// <param name="type">�`��̎��</param>
Canvas::Canvas(Scene* scene, RenderType type)
	:
	Actor(scene)
	,m_type{type}
{

	//�`��}�l�[�W���[�ɃL�����o�X�̓o�^
	GetScene()->GetRenderMangaer()->AddCanvas(this);

}

/// <summary>
/// �f�X�g���N�^
/// </summary>
Canvas::~Canvas()
{

	GetScene()->GetRenderMangaer()->RemoveCanvas(this);
	m_imageComponent.clear();

}

/// <summary>
/// ImageComponent�̒ǉ�
/// </summary>
/// <param name="comp">�ǉ��R���|�[�l���g</param>
void Canvas::AddImageComponent(ImageComponent* comp)
{
	//���݂��Ă��邩�T��
	auto sertchComp = std::find(m_imageComponent.begin(), m_imageComponent.end(), comp);
	//�Ȃ��Ȃ�
	if (sertchComp == m_imageComponent.end())
	{
		//�ǉ�
		m_imageComponent.push_back(comp);
	}


}


