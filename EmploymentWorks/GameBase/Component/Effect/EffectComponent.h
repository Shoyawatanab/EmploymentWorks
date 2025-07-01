#pragma once
#include "GameBase/Component.h"
#include "GameBase/Component/Components.h"

class Camera;

class EffectComponent : public Component
{
public:
	//�R���X�g���N�^
	EffectComponent(Actor* owner, std::function<void(const Camera& camera)> renderFunction);
	//�f�X�g���N�^
	~EffectComponent() override;

	//�`��
	void Render(const Camera& camera);

private:
	
	//�`��
	std::function<void(const Camera& camera)> m_renderFunction;

};