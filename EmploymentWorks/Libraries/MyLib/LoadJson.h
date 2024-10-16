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
    // LoadJsonクラスを宣言する
    class LoadJson
    {
    public:

        //値を反すための構造体
        struct Parameters
        {
            std::string ModelName;

            DirectX::SimpleMath::Vector3 Position;
            DirectX::SimpleMath::Vector3 Scale;
            DirectX::SimpleMath::Vector3 Rotation;
            float BoundingSphereRadius;
        };

    public:
        // コンストラクタ
        LoadJson();
        // デストラクタ
        ~LoadJson();

        // JSON形式でグラフデータを読み込む
        bool LoadModelClassDataByJSON(const std::wstring& fileName);
        // データを変換する
        std::vector<Parameters> ParseJSON();

        std::vector<Parameters> GetStageDatas(const std::wstring& fileName);


    private:

        // 入力グラフデータ
        std::vector<std::string> m_modelData;

        std::vector<Parameters> m_parameter;
    };
}
#endif	// LoadJson_DEFINED
