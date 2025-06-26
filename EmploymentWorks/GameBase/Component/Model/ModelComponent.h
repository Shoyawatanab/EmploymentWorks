#pragma once
#include "GameBase/Component/Components.h"

class CommonResources;
class Camera;

class ModelComponent : public Component
{
public:

	//�`����
	enum class RenderKinds
	{
		NORMAL    //�ʏ�
		, CUSTOM	  //�J�X�^��
	};
public:

	//�J�X�^���`��֐��̓o�^
	void SetCustomRenderFunction(std::function<void(const Camera& camera)> customRender);
	//���f���̎擾
	DirectX::Model* GetModel() { return m_model; }

public:
	//�R���X�g���N�^
	ModelComponent(Actor* owner, std::string modelMame);
	//�f�X�g���N�^
	~ModelComponent() override;
	//�`��
	void Render(const Camera& camera);

private
	:
	//�ʏ�`��
	void NormalRender(const Camera& camera);
	//�J�X�^���`��
	void CustomRender(const Camera& camera);

private:
	//���f��
	DirectX::Model* m_model;
	//���ʃ��\�[�X
	CommonResources* m_commonResources;

	//�ʕ`��
	std::function<void(const Camera& camera)> m_customRender;
	//�`��̎��
	RenderKinds m_renderKinds;


};