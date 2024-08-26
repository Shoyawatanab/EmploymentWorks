/*
	@file	Judgement.h
	@brief	いろいろな判定をするクラス
*/
#pragma once

class Bounding;

namespace mylib
{
    class Judgement
    {
    public:
        //Boundingクラスの追加
        void SetBounding(Bounding* bounding) { m_boundings.push_back(bounding); }

    private:
        //オブジェクトの格納変数
        std::vector<Bounding*> m_boundings;

    public:
        Judgement();
        ~Judgement();

        int GetRandom(int min, int max);


        //扇形ないかどうか
        bool IsWithinTheSector(DirectX::SimpleMath::Vector3 JudgmentPos,DirectX::SimpleMath::Vector3 Direction, DirectX::SimpleMath::Vector3 Center, float radius, float angle);
        //RayとBoundingBox都の判定
        bool IsRayToBoundingBox(DirectX::SimpleMath::Ray ray, float distance);

        //割合を求める
        float GetRatio(float value, float maxValue);

        //距離を求める
        float GetLenght(DirectX::SimpleMath::Vector3 Pos1, DirectX::SimpleMath::Vector3 Pos2);

    };
}
