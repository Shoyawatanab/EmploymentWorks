/*
	@file	Mouse.h
	@brief	�^�C�g���V�[���N���X
*/
#pragma once

namespace WataLib
{
    class Mouse
    {
    public:
        //X���̍����̎擾
        float GetDiffX() { return m_diffX; }
        //Y���̍����̎擾
        float GetDiffY() { return m_diffY; }

    public:
        Mouse();
        ~Mouse();

        void Initialize();
        void Update();

    private:
        //���݂̍��W
        POINT  m_currentMousePos;
        //�����̍��W(�X�N���[���̒��S)
        POINT  m_initialMousePos;

        //�ړ���
        float m_diffX;
        float m_diffY;


    };
}
