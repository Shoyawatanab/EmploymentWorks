/*
	@file	Mouse.h
	@brief	タイトルシーンクラス
*/
#pragma once

namespace WataLib
{
    class Mouse
    {
    public:
        //X軸の差分の取得
        float GetDiffX() { return m_diffX; }
        //Y軸の差分の取得
        float GetDiffY() { return m_diffY; }

    public:
        Mouse();
        ~Mouse();

        void Initialize();
        void Update();

    private:
        //現在の座標
        POINT  m_currentMousePos;
        //初期の座標(スクリーンの中心)
        POINT  m_initialMousePos;

        //移動量
        float m_diffX;
        float m_diffY;


    };
}
