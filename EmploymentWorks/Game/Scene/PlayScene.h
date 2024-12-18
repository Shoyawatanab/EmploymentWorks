/*
	@file	PlayScene.h
	@brief	�v���C�V�[���N���X
*/
#pragma once
#include "IScene.h"
#include <unordered_map>
#include "Game/Scene/SceneManager.h"
// �O���錾
class CommonResources;
class Player;
class Enemy;
class Floor;
class LockOn;
class CollisionManager;
class Wall;
class Rock;
class Sky;
class UI;
class Ceiling;
class Pillar;
class Artillery;
class Particle;
class BirdEnemy;
class HitEffects;


namespace mylib
{
	class DebugCamera;
	class GridFloor;
	class GameCameraManager;
	class Texture;

}


class PlayScene final :
	public IScene
{
public:

	enum class GameState
	{
		None,    //�ʏ�
		Clear,
		GameOver

	};

public:

	void SetNextSceneID(SceneID ID) { m_nextScene = ID; }

	//�X���[���o�̐i�s�������擾
	float GetSlowMotionProgressRate() { return m_progressRate; }

private:

	SceneID m_nextScene;

	// ���ʃ��\�[�X
	CommonResources* m_commonResources;

	// �f�o�b�O�J����
	//std::unique_ptr<mylib::DebugCamera> m_debugCamera;

	std::unique_ptr<mylib::GameCameraManager> m_cameraManager;

	// �i�q��
	std::unique_ptr<mylib::GridFloor> m_gridFloor;

	// �ˉe�s��
	DirectX::SimpleMath::Matrix m_projection;

	std::unique_ptr<Player> m_player;
	std::unique_ptr<Enemy> m_enemy;
	std::unique_ptr<BirdEnemy> m_birdEnemy;

	//��
	std::unique_ptr<Floor> m_floor;
	std::unique_ptr<LockOn> m_lockOn;

	//��
	std::vector<std::unique_ptr<Wall>> m_wall;
	//�V��
	std::unique_ptr<Ceiling> m_ceiling;
	//��
	std::vector<std::unique_ptr<Pillar>> m_pillar;
	//�C��
	std::vector<std::unique_ptr<Artillery>> m_artillery;

	std::unique_ptr<CollisionManager> m_collisionManager;

	std::unique_ptr<UI> m_ui;


	std::vector< std::unique_ptr<Rock>> m_rock;


	std::unique_ptr<Sky> m_sky;

	GameState m_state;


	//�p�[�e�B�N���N���X �����G�t�F�N�g
	std::vector<std::unique_ptr<Particle>> m_particle;

	// �I�[�f�B�I�֘A
	std::unique_ptr<DirectX::AudioEngine> m_audioEngine;
	std::unique_ptr<DirectX::SoundEffect> m_soundEffectBGM;
	std::unique_ptr<DirectX::SoundEffectInstance> m_soundEffectInstanceBGM;


	//���߂̃J�E���g�_�E��
	float m_startCountDown;


	//�C�x���g�̍X�V�֐��̊i�[�ϐ�
	std::unordered_map<std::string, std::function<void(float)>> m_eventUpdate;
	//�폜�������C�x���g���̓o�^�ϐ�
	std::vector<std::string> m_deleteEventName;

	//�X���[���o���̑��x
	float m_slowMotionSpeed;
	//�X���[���o�̎���
	float m_slowMotionTime;
	//�X���[���o�̍ő厞��
	float m_slowMotionMaxTime;
	//�X���[���o�̕\���摜
	std::unique_ptr<mylib::Texture> m_slowTexture;
	//�X���[���o�����ǂ���
	bool m_isSlowMotion;
	//�X���[���o�̐i�s����
	float m_progressRate;


	//�q�b�g�G�t�F�N�g
	std::vector<std::unique_ptr<HitEffects>> m_hitEffects;
	
	SceneManager::StageID m_stageID;

public:
	PlayScene(SceneManager::StageID stageID);
	~PlayScene() override;

	void Initialize(CommonResources* resources) override;
	void Update(float elapsedTime)override;
	void Render() override;
	void Finalize() override;

	SceneID GetNextSceneID() const override;


	void CreateStage();

	void CreateObject();

	//�����G�t�F�N�g�𐶐�
	void CreateParticle(DirectX::SimpleMath::Vector3 Pos);

	void CreateHitEffects(DirectX::SimpleMath::Vector3 Pos);


	//�u�[�������𓊂���Ƃ��̃X���[���o���ɌĂ΂��֐�
	void BoomerangSlowMotion();
	//�u�[�������̓����I���
	void BoomerangSlowMotionEnd();

	//�X���[���o��Update
	void SlowMotion(float elapsdTime);

};
