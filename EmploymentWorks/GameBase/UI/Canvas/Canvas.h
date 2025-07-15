/*
	�N���X��     : Canvas
	����         : UI�L�����o�X�̊��N���X
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Actor.h"

class Canvas : public Actor
{
public:

	enum  class RenderType
	{
	
		SpaceOverlay  //��ɉ�ʂɈڂ葱����
		, WorldSpace  //�RD��Ԃ̃I�u�W�F�N�g�Ƃ��Ĕz�u
	};



public:

	//�R���X�g���N�^
	Canvas(Scene * scene, RenderType type);
	//�f�X�g���N�^
	~Canvas();

private:
	//�`��̎��
	RenderType m_type;

};




