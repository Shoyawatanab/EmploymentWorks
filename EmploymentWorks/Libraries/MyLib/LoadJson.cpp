#include "pch.h"
#include "LoadJson.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>




// �R���X�g���N�^
mylib::LoadJson::LoadJson()
    :
    m_modelData{}
{

}


// �f�X�g���N�^
mylib::LoadJson::~LoadJson()
{
}




// JSON�`���ŃO���t�f�[�^��ǂݍ���
bool mylib::LoadJson::LoadModelClassDataByJSON(const std::wstring& fileName)
{

    std::stringstream ss;
    std::string ModelClassData;

    // ���̓t�@�C���X�g���[��
    std::ifstream in(fileName, std::ifstream::in);
    //���̓t�@�C���X�g���[�����I�[�v������
    in.open(fileName, std::ifstream::in);
    if (!in.is_open())
        return false;

    // �X�g�����O�X�g���[��
    ss << in.rdbuf();
    // �z����N���A����
    m_modelData.clear();
    // ���s�܂ł̈�s���̕�������擾����
    while (std::getline(ss, ModelClassData))
    {
        // �O���t�f�[�^����s�v�ȕ�������������
        ModelClassData.erase(std::remove_if(
            ModelClassData.begin(),
            ModelClassData.end(),
            [](char c) {
                return (
                    c == '\r' || c == '\t' || c == ' ' || c == '\n' || c == '\"' ||
                    c == '[' || c == ']' || c == '{' || c == '}'
                    );
            }),
            ModelClassData.end()
        );
        if (!ModelClassData.empty())
        {
            // �z��Ƀ��[�h��ǉ�����
            m_modelData.push_back(ModelClassData);
        }
    }
    // ���̓t�@�C���X�g���[�����N���[�Y����
    in.close();
    // ����I��
    return true;
}


/// JSON�`���̃f�[�^���p�[�X���I�u�W�F�N�g�ɕϊ�����
std::vector<mylib::LoadJson::Parameters> mylib::LoadJson::ParseJSON()
{

    std::vector<std::string> modelName;

    for (int index = 0; index < m_modelData.size(); index++)
    {

        int position;

        float x;
        float y;
        float z;
        float scale;
        float rotation;

        //1�s�ڂɃ��f���̖��O�@�Q�s�ڂɃp�����[�^������̂łP�s�ڂ��΂�

        std::stringstream ss(m_modelData[index].c_str());

        // ",position:x:"����������
        position = (int)m_modelData[index].find("position:x:");

        // �����񂪌�����Ȃ��ꍇ
        if (position == std::string::npos)
        {
            //.com:��T��
            position = (int)m_modelData[index].find(".cmo:");
            //.com:������������
            if (position != std::string::npos)
            {
                //:��T��
                position = (int)m_modelData[index].find(":");
                //�F������
                m_modelData[index].replace(position, strlen(":"), " ");
                std::stringstream ss2(m_modelData[index].c_str());

                modelName.push_back(ss2.str());

            }


            continue;
        }

        // "position:x:"���󕶎��ɒu��������
        m_modelData[index].replace(position, strlen("position:x:"), " ");
        // ",y:"��T������
        position = (int)m_modelData[index].find(",y:");
        // ",y:"���󕶎��ɒu��������
        m_modelData[index].replace(position, strlen(",y:"), " ");
        // ",z:"��T������
        position = (int)m_modelData[index].find(",z:");
        // ",z:"���󕶎��ɒu��������
        m_modelData[index].replace(position, strlen(",z:"), " ");

        //scale�̕��������������
        position = m_modelData[index].find(",scale:");
        //scale�̕�������폜
        m_modelData[index].replace(position, strlen(",scale:"), " ");
        //rotation�̕��������������
        position = m_modelData[index].find(",rotation:");
        //scale�̕�������폜
        m_modelData[index].replace(position, strlen(",rotation:"), " ");



        ss.clear();
        ss.str(m_modelData[index]);
        // �����擾
        ss >> x >> y >> z >> scale >> rotation;


        //Parameters parameter;
        //parameter.Position.x = x;
        //parameter.Position.y = y;
        //parameter.Position.z = z;
        //parameter.Scale = scale;
        //parameter.Rotation = rotation;
        //parameter.ModelName = modelName[modelName.size() - 1];
        //m_parameter.push_back(parameter);

    }

    return m_parameter;
}

std::vector<mylib::LoadJson::Parameters> mylib::LoadJson::GetStageDatas(const std::wstring& fileName)
{
    std::stringstream ss;
    std::string ModelClassData;
    std::vector<std::string> modelData;
    std::string SaveModelData;

    // ���̓t�@�C���X�g���[��
    std::ifstream in(fileName, std::ifstream::in);
    //���̓t�@�C���X�g���[�����I�[�v������
    in.open(fileName, std::ifstream::in);

    if (!in.is_open())
    {

        assert("StageData���擾�ł��܂���ł����B");

    }

    // �X�g�����O�X�g���[��
    ss << in.rdbuf();
    // �z����N���A����
    modelData.clear();
    // ���s�܂ł̈�s���̕�������擾����
    while (std::getline(ss, ModelClassData))
    {
        // �O���t�f�[�^����s�v�ȕ�������������
        ModelClassData.erase(std::remove_if(
            ModelClassData.begin(),
            ModelClassData.end(),
            [](char c) {
                return (
                    c == '\r' || c == '\t' || c == ' ' || c == '\n' || c == '\"' ||
                    c == '[' || c == ']' || c == '{' || c == '}'
                    );
            }),
            ModelClassData.end()
        );
        //�󂶂�Ȃ��Ƃ�
        if (!ModelClassData.empty())
        {
            //.com:��T��
            int string = (int)ModelClassData.find(".cmo:");
            //.com:������������
            if (string != std::string::npos)
            {
                //�Z�[�u�������
                if (!SaveModelData.empty())
                {
                    //�ǉ�
                    modelData.push_back(SaveModelData);
                    //�N���A
                    SaveModelData.clear();
                }
                // �z��Ƀ��[�h��ǉ�����
                modelData.push_back(ModelClassData);

                continue;
            }


            //������𑫂��Ă���
            SaveModelData += ModelClassData;

        }
    }

    //��̏������ƍŌ�̃��f���̏�񂪒ǉ�����Ȃ�����
    modelData.push_back(SaveModelData);


    // ���̓t�@�C���X�g���[�����N���[�Y����
   in.close();


    std::vector<std::string> modelName;
    std::vector<Parameters>  parameters;



    for (int index = 0; index < modelData.size(); index++)
    {

        //������
        int string;
        //�o�E���f�B���O�X�t�B�A�̔��a
        float boundingSphereRadius;
        //���W
        DirectX::SimpleMath::Vector3 position;
        //�傫��
        DirectX::SimpleMath::Vector3 scale;
        //��]
        DirectX::SimpleMath::Vector3 rotation;

        //1�s�ڂɃ��f���̖��O�@�Q�s�ڂɃp�����[�^������̂łP�s�ڂ��΂�
        std::stringstream ss(modelData[index].c_str());



        // "BoundingSphereRadius:"����������
        string = (int)modelData[index].find("BoundingSphereRadius:");

        // �����񂪌�����Ȃ��ꍇ
        if (string == std::string::npos)
        {
            //.com:��T��
            string = (int)modelData[index].find(".cmo:");
            //.com:������������
            if (string != std::string::npos)
            {
                //:��T��
                string = (int)modelData[index].find(":");
                //�F������
                modelData[index].replace(string, strlen(":"), "");
                std::stringstream ss2(modelData[index].c_str());

                modelName.push_back(ss2.str());

            }


            continue;
        }








        //BoundingSphereRadius:��u��������
        modelData[index].replace(string, strlen("BoundingSphereRadius:"), " ");

        // ",position:x:"����������
        string = (int)modelData[index].find(",Position:x:");

        // "position:x:"���󕶎��ɒu��������
        modelData[index].replace(string, strlen(",Position:x:"), " ");

        // ",y:"��T������
        string = (int)modelData[index].find(",y:");
        // ",y:"���󕶎��ɒu��������
        modelData[index].replace(string, strlen(",y:"), " ");
        // ",z:"��T������
        string = (int)modelData[index].find(",z:");
        // ",z:"���󕶎��ɒu��������
        modelData[index].replace(string, strlen(",z:"), " ");

        //scale�̕��������������
        string = modelData[index].find(",Scale:x:");
        //scale�̕�������폜
        modelData[index].replace(string, strlen(",Scale:x:"), " ");

        // ",y:"��T������
        string = (int)modelData[index].find(",y:");
        // ",y:"���󕶎��ɒu��������
        modelData[index].replace(string, strlen(",y:"), " ");
        // ",z:"��T������
        string = (int)modelData[index].find(",z:");
        // ",z:"���󕶎��ɒu��������
        modelData[index].replace(string, strlen(",z:"), " ");

        //rotation�̕��������������
        string = modelData[index].find(",Rotation:x:");
        //scale�̕�������폜
        modelData[index].replace(string, strlen(",Rotation:x:"), " ");

        // ",y:"��T������
        string = (int)modelData[index].find(",y:");
        // ",y:"���󕶎��ɒu��������
        modelData[index].replace(string, strlen(",y:"), " ");
        // ",z:"��T������
        string = (int)modelData[index].find(",z:");
        // ",z:"���󕶎��ɒu��������
        modelData[index].replace(string, strlen(",z:"), " ");

        ss.clear();
        ss.str(modelData[index]);
        // �����擾
       ss >> boundingSphereRadius >> position.x >> position.y >> position.z >> scale.x >> scale.y >> scale.z>> rotation.x >> rotation.y >> rotation.z;

        //ss >> boundingSphereRadius >>position.x >> position.y >> position.z;

        Parameters parameter;
        parameter.BoundingSphereRadius = boundingSphereRadius;
        parameter.Position = position;
        parameter.Scale = scale;
        parameter.Rotation = rotation;
        parameter.ModelName = modelName[modelName.size() - 1];

        parameters.push_back(parameter);

    }

    return parameters;

}




