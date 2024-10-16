#include "pch.h"
#include "LoadJson.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>




// コンストラクタ
mylib::LoadJson::LoadJson()
    :
    m_modelData{}
{

}


// デストラクタ
mylib::LoadJson::~LoadJson()
{
}




// JSON形式でグラフデータを読み込む
bool mylib::LoadJson::LoadModelClassDataByJSON(const std::wstring& fileName)
{

    std::stringstream ss;
    std::string ModelClassData;

    // 入力ファイルストリーム
    std::ifstream in(fileName, std::ifstream::in);
    //入力ファイルストリームをオープンする
    in.open(fileName, std::ifstream::in);
    if (!in.is_open())
        return false;

    // ストリングストリーム
    ss << in.rdbuf();
    // 配列をクリアする
    m_modelData.clear();
    // 改行までの一行分の文字列を取得する
    while (std::getline(ss, ModelClassData))
    {
        // グラフデータから不要な文字を消去する
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
            // 配列にワードを追加する
            m_modelData.push_back(ModelClassData);
        }
    }
    // 入力ファイルストリームをクローズする
    in.close();
    // 正常終了
    return true;
}


/// JSON形式のデータをパースしオブジェクトに変換する
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

        //1行目にモデルの名前　２行目にパラメータがあるので１行目を飛ばす

        std::stringstream ss(m_modelData[index].c_str());

        // ",position:x:"を検索する
        position = (int)m_modelData[index].find("position:x:");

        // 文字列が見つからない場合
        if (position == std::string::npos)
        {
            //.com:を探す
            position = (int)m_modelData[index].find(".cmo:");
            //.com:が見つかったら
            if (position != std::string::npos)
            {
                //:を探す
                position = (int)m_modelData[index].find(":");
                //：を消す
                m_modelData[index].replace(position, strlen(":"), " ");
                std::stringstream ss2(m_modelData[index].c_str());

                modelName.push_back(ss2.str());

            }


            continue;
        }

        // "position:x:"を空文字に置き換える
        m_modelData[index].replace(position, strlen("position:x:"), " ");
        // ",y:"を探索する
        position = (int)m_modelData[index].find(",y:");
        // ",y:"を空文字に置き換える
        m_modelData[index].replace(position, strlen(",y:"), " ");
        // ",z:"を探索する
        position = (int)m_modelData[index].find(",z:");
        // ",z:"を空文字に置き換える
        m_modelData[index].replace(position, strlen(",z:"), " ");

        //scaleの文字列を検索する
        position = m_modelData[index].find(",scale:");
        //scaleの文字列を削除
        m_modelData[index].replace(position, strlen(",scale:"), " ");
        //rotationの文字列を検索する
        position = m_modelData[index].find(",rotation:");
        //scaleの文字列を削除
        m_modelData[index].replace(position, strlen(",rotation:"), " ");



        ss.clear();
        ss.str(m_modelData[index]);
        // 情報を取得
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

    // 入力ファイルストリーム
    std::ifstream in(fileName, std::ifstream::in);
    //入力ファイルストリームをオープンする
    in.open(fileName, std::ifstream::in);

    if (!in.is_open())
    {

        assert("StageDataが取得できませんでした。");

    }

    // ストリングストリーム
    ss << in.rdbuf();
    // 配列をクリアする
    modelData.clear();
    // 改行までの一行分の文字列を取得する
    while (std::getline(ss, ModelClassData))
    {
        // グラフデータから不要な文字を消去する
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
        //空じゃないとき
        if (!ModelClassData.empty())
        {
            //.com:を探す
            int string = (int)ModelClassData.find(".cmo:");
            //.com:が見つかったら
            if (string != std::string::npos)
            {
                //セーブがあれば
                if (!SaveModelData.empty())
                {
                    //追加
                    modelData.push_back(SaveModelData);
                    //クリア
                    SaveModelData.clear();
                }
                // 配列にワードを追加する
                modelData.push_back(ModelClassData);

                continue;
            }


            //文字列を足していく
            SaveModelData += ModelClassData;

        }
    }

    //上の処理だと最後のモデルの情報が追加されないから
    modelData.push_back(SaveModelData);


    // 入力ファイルストリームをクローズする
   in.close();


    std::vector<std::string> modelName;
    std::vector<Parameters>  parameters;



    for (int index = 0; index < modelData.size(); index++)
    {

        //文字列
        int string;
        //バウンディングスフィアの半径
        float boundingSphereRadius;
        //座標
        DirectX::SimpleMath::Vector3 position;
        //大きさ
        DirectX::SimpleMath::Vector3 scale;
        //回転
        DirectX::SimpleMath::Vector3 rotation;

        //1行目にモデルの名前　２行目にパラメータがあるので１行目を飛ばす
        std::stringstream ss(modelData[index].c_str());



        // "BoundingSphereRadius:"を検索する
        string = (int)modelData[index].find("BoundingSphereRadius:");

        // 文字列が見つからない場合
        if (string == std::string::npos)
        {
            //.com:を探す
            string = (int)modelData[index].find(".cmo:");
            //.com:が見つかったら
            if (string != std::string::npos)
            {
                //:を探す
                string = (int)modelData[index].find(":");
                //：を消す
                modelData[index].replace(string, strlen(":"), "");
                std::stringstream ss2(modelData[index].c_str());

                modelName.push_back(ss2.str());

            }


            continue;
        }








        //BoundingSphereRadius:を置き換える
        modelData[index].replace(string, strlen("BoundingSphereRadius:"), " ");

        // ",position:x:"を検索する
        string = (int)modelData[index].find(",Position:x:");

        // "position:x:"を空文字に置き換える
        modelData[index].replace(string, strlen(",Position:x:"), " ");

        // ",y:"を探索する
        string = (int)modelData[index].find(",y:");
        // ",y:"を空文字に置き換える
        modelData[index].replace(string, strlen(",y:"), " ");
        // ",z:"を探索する
        string = (int)modelData[index].find(",z:");
        // ",z:"を空文字に置き換える
        modelData[index].replace(string, strlen(",z:"), " ");

        //scaleの文字列を検索する
        string = modelData[index].find(",Scale:x:");
        //scaleの文字列を削除
        modelData[index].replace(string, strlen(",Scale:x:"), " ");

        // ",y:"を探索する
        string = (int)modelData[index].find(",y:");
        // ",y:"を空文字に置き換える
        modelData[index].replace(string, strlen(",y:"), " ");
        // ",z:"を探索する
        string = (int)modelData[index].find(",z:");
        // ",z:"を空文字に置き換える
        modelData[index].replace(string, strlen(",z:"), " ");

        //rotationの文字列を検索する
        string = modelData[index].find(",Rotation:x:");
        //scaleの文字列を削除
        modelData[index].replace(string, strlen(",Rotation:x:"), " ");

        // ",y:"を探索する
        string = (int)modelData[index].find(",y:");
        // ",y:"を空文字に置き換える
        modelData[index].replace(string, strlen(",y:"), " ");
        // ",z:"を探索する
        string = (int)modelData[index].find(",z:");
        // ",z:"を空文字に置き換える
        modelData[index].replace(string, strlen(",z:"), " ");

        ss.clear();
        ss.str(modelData[index]);
        // 情報を取得
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




