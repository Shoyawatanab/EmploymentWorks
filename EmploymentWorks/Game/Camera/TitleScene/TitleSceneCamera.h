#pragma once
#include "GameBase/Camera/Camera.h"

class TitleSceneCamera : public Camera
{
public:

	//�^�[�Q�b�g�܂ł̋���
	static constexpr DirectX::SimpleMath::Vector3 DISTANCE_TO_TARGET{6.0f, 4.0f, 6.0f};

	static constexpr float ROTATION_SPEED = 0.25f;

public:
	//
	TitleSceneCamera(Scene* scene);
	//
	~TitleSceneCamera();

	void UpdateCamera(const float& deltaTime) override;

private:
	//�p�x
	float m_angle;

};