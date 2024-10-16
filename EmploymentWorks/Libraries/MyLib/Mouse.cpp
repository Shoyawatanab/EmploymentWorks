/*
	@file	Mouse.cpp
	@brief	�^�C�g���V�[���N���X
*/
#include "pch.h"
#include "Game/Screen.h"
#include "Libraries/MyLib/Mouse.h"

#include <cassert>



//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
mylib::Mouse::Mouse()
	:
	m_diffX{},
	m_diffY{}
{
	m_initialMousePos = { Screen::CENTER_X, Screen::CENTER_Y };
	m_currentMousePos = m_initialMousePos;
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
mylib::Mouse::~Mouse()
{
	// do nothing.
}

//---------------------------------------------------------
// ����������
//---------------------------------------------------------
void mylib::Mouse::Initialize()
{
	m_initialMousePos = { Screen::CENTER_X, Screen::CENTER_Y };

	//�}�E�X�̒��S���W��
	//m_initialMousePos = { (RECT::right - RECT::left) / 2, Screen::CENTER_Y };

	m_currentMousePos = m_initialMousePos;

	SetCursorPos(m_initialMousePos.x, m_initialMousePos.y);



}

//---------------------------------------------------------
// �X�V����
//---------------------------------------------------------
void mylib::Mouse::Update()
{

	//���݂̃}�E�X���W�̎擾
	GetCursorPos(&m_currentMousePos);

	//���������߂�
	m_diffX = static_cast<float>( m_currentMousePos.x - m_initialMousePos.x);
	m_diffY = static_cast<float>( m_currentMousePos.y - m_initialMousePos.y);
	//�����ɖ߂�
	//m_currentMousePos = m_initialMousePos;
	ShowCursor(FALSE);

	SetCursorPos(m_initialMousePos.x,m_initialMousePos.y);

}




