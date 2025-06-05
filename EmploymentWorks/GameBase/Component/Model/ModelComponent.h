#pragma once
#include "GameBase/Component/Components.h"

class CommonResources;
class Camera;

class ModelComponent : public Component
{

public:
	//�R���X�g���N�^
	ModelComponent(Actor* owner, std::string modelMame);
	//�f�X�g���N�^
	~ModelComponent() override ;
	//�`��
	void Render(const Camera& camera);

private:
	//���f��
	DirectX::Model* m_model;
	//���ʃ��\�[�X
	CommonResources* m_commonResources;

};