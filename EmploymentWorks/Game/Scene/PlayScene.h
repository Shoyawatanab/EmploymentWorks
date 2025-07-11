/*
	�N���X��     : PlayScene
	����         : �v���C�V�[��
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Scene/Scene.h"
#include "SceneManager.h"

class PickUpManager;


class PlayScene  :  public Scene
{
public:
	//�J�����̎擾
	Camera* GetCamera() const  override { return m_camera; };
	//����}�l�[�W���[�̎擾
	PickUpManager* GetPickUpManager() { return m_pickUpManager.get(); }


public:
	//�R���X�g���N�^
	PlayScene();
	//�f�X�g���N�^
	~PlayScene() override;

	void Initialize() override;

	void SceneUpdate(const float& deltaTime)override;


private:


	//�J����
	Camera* m_camera;
	//����}�l�[�W���[
	std::unique_ptr<PickUpManager> m_pickUpManager;



};
