/*
	�N���X��     : Canvas
	����         : UI�L�����o�X�̊��N���X
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Actor.h"

class ImageComponent;
class Camera;

class Canvas : public Actor
{
public:

	//�`��^�C�v
	enum  class RenderType
	{
	
		SpaceOverlay  //��ɉ�ʂɈڂ葱����
		, WorldSpace  //�RD��Ԃ̃I�u�W�F�N�g�Ƃ��Ĕz�u
	};

public:

	//�`��^�C�v�̎擾
	RenderType GetRenderType() const { return m_type; };

	//ImageComponent�̎擾
	std::vector<ImageComponent*> GetImageComponent() { return m_imageComponent; }

public:

	//�R���X�g���N�^
	Canvas(Scene * scene, RenderType type);
	//�f�X�g���N�^
	~Canvas();

	//�`��
	virtual void Render(const Camera& camera) { UNREFERENCED_PARAMETER(camera); };


	//ImageComponent�̒ǉ�
	void AddImageComponent(ImageComponent* comp);

private:
	//�`��̎��
	RenderType m_type;
	//�摜�R���|�[�l���g�z��
	std::vector<ImageComponent*> m_imageComponent;

};




