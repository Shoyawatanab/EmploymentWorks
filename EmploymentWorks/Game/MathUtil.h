#pragma once
#include "pch.h"
#include "GameBase/Screen.h"
#include <random>


namespace MathUtil
{
    /// <summary>
    /// Lerp�֐�
    /// </summary>
    /// <typeparam name="T"></typeparam>
    /// <param name="a"></param>
    /// <param name="b"></param>
    /// <param name="t"></param>
    /// <returns></returns>
    template<typename T>
    inline T Lerp(const T& a, const T& b, float t)
    {
        return a + (b - a) * t;
    }



    /// <summary>
    /// Vector3��Quaternion�ɕϊ�
    /// </summary>
    /// <param name="vector3"></param>
    /// <returns></returns>
    inline DirectX::SimpleMath::Quaternion ChangeVector3ToQuaternion(
        DirectX::SimpleMath::Vector3 vector3
    )
    {
       return DirectX::SimpleMath::Quaternion::CreateFromYawPitchRoll(
            DirectX::XMConvertToRadians(vector3.y),
            DirectX::XMConvertToRadians(vector3.x),
            DirectX::XMConvertToRadians(vector3.z));

    }


    /// <summary>
    /// ���[���h���W���X�N���[�����W�ɕϊ�
    /// </summary>
    /// <param name="worldPos">���[���h���W</param>
    /// <param name="worldMatrix">���[���h�}�g���b�N�X</param>
    /// <param name="viewMatrix">�r���[�s��</param>
    /// <param name="projectionMatrix">�ˉe�s��</param>
    /// <returns>�X�N���[�����W</returns>
    inline DirectX::SimpleMath::Vector2 WorldToScreen(const DirectX::SimpleMath::Vector3& worldPos
        , const DirectX::SimpleMath::Matrix& worldMatrix, const DirectX::SimpleMath::Matrix& viewMatrix
        , const DirectX::SimpleMath::Matrix& projectionMatrix)
    {
        using namespace DirectX::SimpleMath;
        // ���[���h���W��ϊ����邽�߂̍s�������
        Matrix transformMatrix = worldMatrix * viewMatrix * projectionMatrix;

        // ���[���h���W���v���W�F�N�V������Ԃɕϊ�
        Vector3 projectedPos = Vector3::Transform(worldPos, transformMatrix);

        // �ˉe���ꂽ���W���X�N���[�����W�ɕϊ�
        float x = (projectedPos.x / projectedPos.z * 0.5f + 0.5f) * Screen::WIDTH;
        float y = (0.5f - projectedPos.y / projectedPos.z * 0.5f) * Screen::HEIGHT;

        return Vector2(x, y);
    }

    template<typename T>
    inline T GetRandom(const T minValue,const T maxValue)
    {
        //	���S�ȃ����_�����n�[�h�E�F�A�I�ɐ������邽�߂̃N���X�̕ϐ�
        std::random_device seed;
        //	��L�̊��S�ȃ����_���͓��삪�x�����߁Aseed�l�̌���݂̂Ɏg�p����
        //	���udefault_random_engine�v��using�Łumt19937�v�ƂȂ��Ă���
        std::default_random_engine engine(seed());
        //	�������ė~���������_���͈̔͂�Distribution�ɔC����B�����0�`2PI
        std::uniform_real_distribution<> dist(minValue,maxValue);

        return dist(engine);

    }


}
