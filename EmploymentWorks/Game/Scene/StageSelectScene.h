/*
	@file	StageSelectScene.h
	@brief	�^�C�g���V�[���N���X
*/
#pragma once
#include "IScene.h"
#include "Game/Scene/SceneManager.h"

// �O���錾
class CommonResources;

namespace WataLib
{
	class DrawTexture;
}



class StageSelectScene final :
    public IScene
{
public:
	static constexpr int BUTTOM_INIAL_ID{ -1000 };


public:
    StageSelectScene(SceneManager* sceneManager);
    ~StageSelectScene() override;

    void Initialize(CommonResources* resources) override;
    void Update(float elapsedTime)override;
    void Render() override;
    void Finalize() override;

    SceneID GetNextSceneID() const;

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	SceneManager* m_sceneManager;


	std::vector <std::unique_ptr<WataLib::DrawTexture>> m_textures;

	// �V�[���`�F���W�t���O
	bool m_isChangeScene;

	std::unordered_map<int, std::unique_ptr<WataLib::DrawTexture>> m_buttom;

	int m_selectButtomId;


};
