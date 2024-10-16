/*
	@file	Mouse.cpp
	@brief	タイトルシーンクラス
*/
#include "pch.h"
#include "Game/Screen.h"
#include "Libraries/MyLib/Mouse.h"

#include <cassert>



//---------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------
mylib::Mouse::Mouse()
	:
	m_diffX{},
	m_diffY{}
{
	m_initialMousePos = { Screen::CENTER_X, Screen::CENTER_Y };
	m_currentMousePos = m_initialMousePos;
}

//---------------------------------------------------------
// デストラクタ
//---------------------------------------------------------
mylib::Mouse::~Mouse()
{
	// do nothing.
}

//---------------------------------------------------------
// 初期化する
//---------------------------------------------------------
void mylib::Mouse::Initialize()
{
	m_initialMousePos = { Screen::CENTER_X, Screen::CENTER_Y };

	//マウスの中心座標を
	//m_initialMousePos = { (RECT::right - RECT::left) / 2, Screen::CENTER_Y };

	m_currentMousePos = m_initialMousePos;

	SetCursorPos(m_initialMousePos.x, m_initialMousePos.y);



}

//---------------------------------------------------------
// 更新する
//---------------------------------------------------------
void mylib::Mouse::Update()
{

	//現在のマウス座標の取得
	GetCursorPos(&m_currentMousePos);

	//差分を求める
	m_diffX = static_cast<float>( m_currentMousePos.x - m_initialMousePos.x);
	m_diffY = static_cast<float>( m_currentMousePos.y - m_initialMousePos.y);
	//初期に戻す
	//m_currentMousePos = m_initialMousePos;
	ShowCursor(FALSE);

	SetCursorPos(m_initialMousePos.x,m_initialMousePos.y);

}




