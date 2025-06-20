#pragma once
#include "GameBase/Actor.h"

class Canvas;
class NumberUI;
class Image;

class DamageCount : public Actor
{
public:

	//背景の大きさ
	static constexpr DirectX::SimpleMath::Vector3 BACKGROUND_SCALE = { 100.0f,100.0f,0.0f };
	//表示間隔
	static constexpr float SPACING = 35.0f;
	//最大表示桁
	static constexpr int MAXDIGITS = 5;

	//表示時間
	static constexpr float DISPLAYTIME = 2.0f;

public:
	//コンストラクタ
	DamageCount(Canvas* canvas);
	//デストラクタ
	~DamageCount() override;
	// 単体更新
	void UpdateActor(const float& deltaTime);

	//アクティブになった時に呼ばれる関数
	void OnEnable();
	//非アクティブになった時に呼ばれる関数
	void OnDisable();

	//ダメージのセット
	void SetDamage(int damage);

private:
	//時間
	float m_time;
	//背景
	Image* m_backGraund;
	//保存配列　最大桁数だけ所持
	std::vector<NumberUI*> m_numbers;
	//使用配列
	std::vector<NumberUI*> m_usedNumbers;
};