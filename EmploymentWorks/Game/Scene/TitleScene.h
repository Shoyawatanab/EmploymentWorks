/*
	@file	TitleScene.h
	@brief	�^�C�g���V�[���N���X
*/
#pragma once
#include "IScene.h"

// �O���錾
class CommonResources;



namespace mylib
{
	class TitleCamera;
	class GridFloor;
	class Texture;
	class Model3D;
}


class TitleScene final :
    public IScene
{
public:
	enum class NextState
	{
		PLAY,
		EXIT

	};
private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;

	std::unique_ptr<mylib::TitleCamera> m_camera;

	// �V�[���`�F���W�t���O
	bool m_isChangeScene;
	//���S
	std::unique_ptr<mylib::Texture> m_logo;
	//PLAY�摜
	std::unique_ptr<mylib::Texture> m_playTexture;
	//EXIT�摜
	std::unique_ptr<mylib::Texture> m_exitTexture;
	//Boomerang�摜
	std::unique_ptr<mylib::Texture> m_boomerangTexture;

	//���̏��
	NextState m_state;


	std::vector<std::unique_ptr<mylib::Model3D>> m_models;


public:
    TitleScene();
    ~TitleScene() override;

    void Initialize(CommonResources* resources) override;
    void Update(float elapsedTime)override;
    void Render() override;
    void Finalize() override;

    SceneID GetNextSceneID() const;



};
