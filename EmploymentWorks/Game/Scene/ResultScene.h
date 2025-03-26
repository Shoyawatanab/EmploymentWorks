/*
	@file	ResultScene.h
	@brief	�^�C�g���V�[���N���X
*/
#pragma once
#include "IScene.h"
#include "Game/Scene/SceneManager.h"

// �O���錾
class CommonResources;





class ResultScene final :
    public IScene
{

public:
    ResultScene();
    ~ResultScene() override;

    void Initialize(CommonResources* resources) override;
    void Update(float elapsedTime)override;
    void Render() override;
    void Finalize() override;

    SceneID GetNextSceneID() const;

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;


	// �V�[���`�F���W�t���O
	bool m_isChangeScene;

};
