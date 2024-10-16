#pragma once
#ifndef LoadJson_DEFINED
#define LoadJson_DEFINED
#include <memory>
#include <vector>
#include <algorithm>
#include <string>
#include "SimpleMath.h"

namespace mylib
{
    // LoadJson�N���X��錾����
    class LoadJson
    {
    public:

        //�l�𔽂����߂̍\����
        struct Parameters
        {
            std::string ModelName;

            DirectX::SimpleMath::Vector3 Position;
            DirectX::SimpleMath::Vector3 Scale;
            DirectX::SimpleMath::Vector3 Rotation;
            float BoundingSphereRadius;
        };

    public:
        // �R���X�g���N�^
        LoadJson();
        // �f�X�g���N�^
        ~LoadJson();

        // JSON�`���ŃO���t�f�[�^��ǂݍ���
        bool LoadModelClassDataByJSON(const std::wstring& fileName);
        // �f�[�^��ϊ�����
        std::vector<Parameters> ParseJSON();

        std::vector<Parameters> GetStageDatas(const std::wstring& fileName);


    private:

        // ���̓O���t�f�[�^
        std::vector<std::string> m_modelData;

        std::vector<Parameters> m_parameter;
    };
}
#endif	// LoadJson_DEFINED
