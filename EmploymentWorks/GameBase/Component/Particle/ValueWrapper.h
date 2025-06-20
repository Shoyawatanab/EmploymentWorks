//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <�����>			NakashimaYuto
// <����J�n��>		2025/06/17
// <file>			ValueWrapper.cpp
// <�T�v>		�@�@�l�̃��b�p�[�N���X(�������P�Ȃ�ʏ�A�Q�Ȃ烉���_���ɂ���Ȃ�...)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include<type_traits>
#include"ParticleMath.h"

template<typename T>
class ValueWrapper
{
public:

	enum Mode
	{
		Constant = 0,
		RandBetween = 1,
	};

	// �R���X�g���N�^
	ValueWrapper(const T& value) : m_mode{ Mode::Constant } ,m_value { value }, m_min{ value }, m_max{ value } {}
	// �����_���͈�
	ValueWrapper(const T& min, const T& max) :m_mode{ Mode::RandBetween }, m_value{} ,m_min { min }, m_max{ max } {}

	// �蓮�ŃZ�b�g����ۂ̊֐�
	// �����ЂƂȂ̂ŁA���̂܂܂����
	void Set(const T& value)
	{
		m_mode = Mode::Constant;
		m_value = value;
	}
	// �����ӂ��Ȃ̂ŁA��񂾂ނɂȂ�
	void Set(const T& min, const T& max)
	{
		m_mode = Mode::RandBetween;
		m_min = min; m_max = max;
	}

	// �l���擾����
	T Get() { RandomValueSet(); return m_value; }
private:
	// �����_���̍ۂ̒l����p
	void RandomValueSet()
	{
		if (m_mode == Mode::Constant) { return; }
		m_value = ParticleMath::RandomRange(m_min, m_max);
	}

private:
	// ���[�h
	Mode m_mode;
	// ���ۂ̒l
	T m_value;

	// �����_���̏ꍇ�@�g�p����
	// �ŏ��l
	T m_min;
	// �ő�l
	T m_max;

};

// �ƂĂ��������t�@�����X�ł����B���Ђ��̃N���X�������l�́A���������݂Ăق����B�e���v���[�g���܂��܂ł���
// �ǋL:: ����Particle�p��Math��������̂ŁA����g��Ȃ�����...
// https://cpprefjp.github.io/reference/type_traits/is_same.html

