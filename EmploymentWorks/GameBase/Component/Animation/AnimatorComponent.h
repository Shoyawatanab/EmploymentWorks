#pragma once
#include "GameBase/Component.h"

class AnimationController;

class AnimatorComponent : public Component
{
public:
	//コンストラクタ
	AnimatorComponent(Actor* owner, std::unique_ptr<AnimationController> controller);
	//デストラクタ
	~AnimatorComponent() override ;

	// アップデート
	void Update(const float& deltaTime)override;

private:
	//コントローラー
	std::unique_ptr<AnimationController> m_controller;


};