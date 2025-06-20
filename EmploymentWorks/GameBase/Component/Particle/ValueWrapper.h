//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// <製作者>			NakashimaYuto
// <製作開始日>		2025/06/17
// <file>			ValueWrapper.cpp
// <概要>		　　値のラッパークラス(引数が１つなら通常、２つならランダムにするなど...)
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#pragma once
#include<type_traits>
#include"ParticleMath.h"

template<typename T>
class ValueWrapper
{
public:

	enum Mode
	{
		Constant = 0,
		RandBetween = 1,
	};

	// コンストラクタ
	ValueWrapper(const T& value) : m_mode{ Mode::Constant } ,m_value { value }, m_min{ value }, m_max{ value } {}
	// ランダム範囲
	ValueWrapper(const T& min, const T& max) :m_mode{ Mode::RandBetween }, m_value{} ,m_min { min }, m_max{ max } {}

	// 手動でセットする際の関数
	// 引数ひとつなので、そのままいれる
	void Set(const T& value)
	{
		m_mode = Mode::Constant;
		m_value = value;
	}
	// 引数ふたつなので、らんだむになる
	void Set(const T& min, const T& max)
	{
		m_mode = Mode::RandBetween;
		m_min = min; m_max = max;
	}

	// 値を取得する
	T Get() { RandomValueSet(); return m_value; }
private:
	// ランダムの際の値決定用
	void RandomValueSet()
	{
		if (m_mode == Mode::Constant) { return; }
		m_value = ParticleMath::RandomRange(m_min, m_max);
	}

private:
	// モード
	Mode m_mode;
	// 実際の値
	T m_value;

	// ランダムの場合　使用する
	// 最小値
	T m_min;
	// 最大値
	T m_max;

};

// とてもいいリファレンスでした。ぜひこのクラスを見た人は、こっちをみてほしい。テンプレートさまさまですわ
// 追記:: 結局Particle用のMathを作ったので、これ使わなかった...
// https://cpprefjp.github.io/reference/type_traits/is_same.html

