/*
	�N���X��     : ImageComponent
	����         : �摜UI�R���|�[�l���g
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Component.h"

class Canvas;


class ImageComponent : public Component
{

public:	




	//�`����
	enum class RenderKinds
	{
		NORMAL    //�ʏ�
		,CUSTOM	  //�J�X�^��
	};

public:

	//�摜�̎擾
	ID3D11ShaderResourceView* GetImage() { return m_texture.Get(); }

	//�؂���͈͂̃Z�b�g
	void SetCutRange(DirectX::SimpleMath::Vector4 range) { m_cutRange = range; }
	//�؂���͈͂̎擾
	DirectX::SimpleMath::Vector4 const GetCutRange() { return m_cutRange; }
	//�F�̃Z�b�g
	void SetColor(DirectX::SimpleMath::Vector4 color) { m_color = color; }
	//�F�̎擾
	DirectX::SimpleMath::Vector4 const GetColor() { return m_color; }

	//���̓h��Ԃ��ʁ@�O�`�P�܂ł͈̔�
	void SetHorizontalFillAmount(float fillAmount) { m_fillAmount.x = fillAmount; }
	//�h��Ԃ��ʂ̎擾
	DirectX::SimpleMath::Vector4 const GetFillAmount() { return m_fillAmount; }
	
	//�\���͈͂̃Z�b�g
	void SetViewRange(DirectX::SimpleMath::Vector2 range) { m_viewRange.x = range.x; m_viewRange.y = range.y; }
	//�\���͈͂̎擾
	DirectX::SimpleMath::Vector4 const GetViewRange() { return m_viewRange; }

	//�����̎擾
	float GetWidth() const;
	//�c���̎擾
	float GetHeight() const;
	//�J�X�^���`��֐��̓o�^
	void SetCustomRenderFunction(std::function<void()> customRender);
	//��]�̃Z�b�g
	void SetAngle(const float& angle) { m_angle = angle; }
	//��]�̎擾
	float GetAngle() const { return m_angle; }
	//�`���ނ̎擾
	RenderKinds GetRenderKinds() { return m_renderKinds; }
	//�摜�̎擾
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> GetTexture() { return m_texture; }
	//�J�X�^���`��֐��̎擾
	std::function<void()> GetCustomRenderFunction() { return m_customRender; }

	int const GetTextureWidth() { return m_textureWidth; }
	int const GetTextureHeight() { return m_textureHeight; }

public:
	//�R���X�g���N�^
	ImageComponent(Canvas* canvas,Actor* owner,std::string textureName);
	//�f�X�g���N�^
	~ImageComponent() override;


private:

	//�摜�̓ǂݍ���
	void LoadTexture(std::string textureName);

private:

	//�摜
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;




	//�摜�̑傫��
	int m_textureWidth;
	int	m_textureHeight;
	//�F
	DirectX::SimpleMath::Vector4 m_color;
	//�؂���͈�
	DirectX::SimpleMath::Vector4 m_cutRange;
	//�h��Ԃ��ʁ@x: ���@y :�c
	DirectX::SimpleMath::Vector4 m_fillAmount;
	//�\���͈�
	DirectX::SimpleMath::Vector4 m_viewRange;

	//�`��̎��
	RenderKinds m_renderKinds;

	//�ʕ`��
	std::function<void()> m_customRender;
	//��]
	float m_angle;

};