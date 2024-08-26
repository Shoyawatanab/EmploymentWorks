/*
	@file	Judgement.cpp
	@brief	���낢��Ȕ��������N���X
*/
#include "pch.h"
#include "Game/Screen.h"
#include "Libraries/MyLib/Judgement.h"

#include <cassert>
#include <random>

#include "Libraries/MyLib/Bounding.h"


//---------------------------------------------------------
// �R���X�g���N�^
//---------------------------------------------------------
mylib::Judgement::Judgement()
    :
    m_boundings{}
{
}

//---------------------------------------------------------
// �f�X�g���N�^
//---------------------------------------------------------
mylib::Judgement::~Judgement()
{
	// do nothing.
}

int mylib::Judgement::GetRandom(int min, int max)
{
    //�����_���ȃV�[�h�l���g���ė����������������
    static std::random_device seed;
    static std::mt19937 engine(seed());

    //	������͈͓��Ő���
    return engine() % (max - min) + min;
}


 
/// <summary>
/// ��`�Ȃ����ǂ���
/// </summary>
/// <param name="JudgmentPos">���肵�Ăق������W</param>
/// <param name="Direction">��`�̕���</param>
/// <param name="Center">��`�̒��S���W</param>
/// <param name="radius">��`�̔��a</param>
/// <param name="angle">��`�̊p�x</param>
/// <returns></returns>
bool mylib::Judgement::IsWithinTheSector(DirectX::SimpleMath::Vector3 JudgmentPos, DirectX::SimpleMath::Vector3 Direction, DirectX::SimpleMath::Vector3 Center, float radius, float angle)
{

	
    // 1. JudgmentPos��Center�̊Ԃ̃x�N�g�����v�Z
    DirectX::SimpleMath::Vector3 toTarget = JudgmentPos - Center;

    // 2. ���̃x�N�g���̒�����radius�ȉ������`�F�b�N
    float distance = toTarget.Length();

    if (distance > radius) {
        return false;  // ���a�O�Ȃ̂Ő�`�̊O
    }

    // 3. Direction�x�N�g���𐳋K������
    Direction.Normalize();

    // 4. toTarget�x�N�g���𐳋K������
    toTarget.Normalize();

    // 5. Direction�x�N�g����toTarget�x�N�g���̓��ς����߂�
    float dotProduct = Direction.Dot( toTarget);

    // 6. ���ς���p�x�����߂�
    float cosAngle = cosf(DirectX::XMConvertToRadians(angle / 2.0f));

    // 7. �p�x���w�肳�ꂽ��`�̊p�x���Ɏ��܂邩�ǂ����𔻒�
    return dotProduct >= cosAngle;

}

/// <summary>
/// �o�^���ꂽBounding��Ray�Ƃ̓����蔻��
/// </summary>
/// <param name="ray">Ray</param>
/// <param name="distance">Ray�̋���</param>
/// <returns>true: �������Ă���@,false�������Ă��Ȃ�</returns>
bool mylib::Judgement::IsRayToBoundingBox(DirectX::SimpleMath::Ray ray, float distance)
{

    for (auto& object : m_boundings)
    {
        //�������Ă�����
        if (object->GetBoundingBox()->Intersects(ray.position, ray.direction, distance))
        {
            return true;
        }
    }


    //�������Ă��Ȃ�
    return false;

}

/// <summary>
/// ���������߂�
/// </summary>
/// <param name="value">�l</param>
/// <param name="maxValue">�ő�l</param>
/// <returns></returns>
float mylib::Judgement::GetRatio(float value, float maxValue)
{


    if (maxValue == 0.0f)
    {
        return 0.0f;
    }

    return value / maxValue;
}

/// <summary>
/// ���������߂�
/// </summary>
/// <param name="Pos1">���W�P</param>
/// <param name="Pos2">���W�Q</param>
/// <returns>float�^�̋���</returns>
float mylib::Judgement::GetLenght(DirectX::SimpleMath::Vector3 Pos1, DirectX::SimpleMath::Vector3 Pos2)
{

    return (Pos1 - Pos2).Length();
}








