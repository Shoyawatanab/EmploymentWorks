/*
	�N���X��     : Canvas
	����         : UI�L�����o�X�̊��N���X
	�⑫�E���ӓ_ :
*/
#include "pch.h"
#include "Canvas.h"

Canvas::Canvas(Scene* scene, RenderType type)
	:
	Actor(scene)
	,m_type{type}
{
}

Canvas::~Canvas()
{
}
