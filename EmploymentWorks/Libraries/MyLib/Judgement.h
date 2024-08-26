/*
	@file	Judgement.h
	@brief	���낢��Ȕ��������N���X
*/
#pragma once

class Bounding;

namespace mylib
{
    class Judgement
    {
    public:
        //Bounding�N���X�̒ǉ�
        void SetBounding(Bounding* bounding) { m_boundings.push_back(bounding); }

    private:
        //�I�u�W�F�N�g�̊i�[�ϐ�
        std::vector<Bounding*> m_boundings;

    public:
        Judgement();
        ~Judgement();

        int GetRandom(int min, int max);


        //��`�Ȃ����ǂ���
        bool IsWithinTheSector(DirectX::SimpleMath::Vector3 JudgmentPos,DirectX::SimpleMath::Vector3 Direction, DirectX::SimpleMath::Vector3 Center, float radius, float angle);
        //Ray��BoundingBox�s�̔���
        bool IsRayToBoundingBox(DirectX::SimpleMath::Ray ray, float distance);

        //���������߂�
        float GetRatio(float value, float maxValue);

        //���������߂�
        float GetLenght(DirectX::SimpleMath::Vector3 Pos1, DirectX::SimpleMath::Vector3 Pos2);

    };
}
