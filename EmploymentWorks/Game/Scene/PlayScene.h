/*
	@file	PlayScene.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "IScene.h"

// �O���錾
class CommonResources;
class Player;
class Enemy;
class Floor;
class LockOn;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
	class TPS_Camera;
}


class PlayScene final :
    public IScene
{
private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	// �f�o�b�O�J����
	//std::unique_ptr<mylib::DebugCamera> m_debugCamera;

	std::unique_ptr<mylib::TPS_Camera> m_tpsCamera;

	// �i�q��
	std::unique_ptr<mylib::GridFloor> m_gridFloor;

	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;

	// �V�[���`�F���W�t���O
	bool m_isChangeScene;

	std::unique_ptr<Player> m_player;
	std::unique_ptr<Enemy> m_enemy ;

	std::unique_ptr<Floor> m_floor;
	std::unique_ptr<LockOn> m_lockOn;


public:
	PlayScene();
	~PlayScene() override;

	void Initialize(CommonResources* resources) override;
	void Update(float elapsedTime)override;
	void Render() override;
	void Finalize() override;

	SceneID GetNextSceneID() const;
};
