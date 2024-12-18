/*
	@file	StageSelectScene.h
	@brief	�^�C�g���V�[���N���X
*/
#pragma once
#include "IScene.h"
#include "Game/Scene/SceneManager.h"

// �O���錾
class CommonResources;

namespace mylib
{
	class DebugCamera;
	class GridFloor;
}


class StageSelectScene final :
    public IScene
{

public:



private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	SceneManager* m_sceneManager;

	// �X�v���C�g�o�b�`
	std::unique_ptr<DirectX::SpriteBatch> m_spriteBatch;

	// �X�v���C�g�t�H���g
	std::unique_ptr<DirectX::SpriteFont> m_spriteFont;

	// �e�N�X�`��
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_texture;

	// �e�N�X�`���̔����̑傫��
	DirectX::SimpleMath::Vector2 m_texCenter;

	// �V�[���`�F���W�t���O
	bool m_isChangeScene;



public:
    StageSelectScene(SceneManager* sceneManager);
    ~StageSelectScene() override;

    void Initialize(CommonResources* resources) override;
    void Update(float elapsedTime)override;
    void Render() override;
    void Finalize() override;

    SceneID GetNextSceneID() const;
};
