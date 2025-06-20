#pragma once
#include "GameBase/Actor.h"

class Canvas;
class Image;


class BoomerangCount : public Actor
{

	//UI�S�̂̑傫��
	static constexpr DirectX::SimpleMath::Vector3 SCALE = { 10.0f,10.0f,0.0f };
	//UI�S�̂̍��W
	static constexpr DirectX::SimpleMath::Vector3 POSITION = { 180.0f,650.0f,0.0f };
	//�I�t�Z�b�g
	static constexpr DirectX::SimpleMath::Vector3 OFFSET_POSITION = { 120.0f,0.0f,0.0f };
	//�u�[������UI�P�̂̑傫��
	static constexpr DirectX::SimpleMath::Vector3 BOOMERANG_SCALE = { 100.0f,100.0f,100.0f };

	

public:
	//�R���X�g���N�^
	BoomerangCount(Canvas* canvas);
	//�f�X�g���N�^
	~BoomerangCount();
};
