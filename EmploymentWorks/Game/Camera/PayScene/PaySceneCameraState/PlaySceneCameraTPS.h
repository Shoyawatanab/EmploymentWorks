#pragma once
#include "GameBase/Interface/IState.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"

class PlaySceneCamera;
class PlaySceneCameraStateMachine;

class PlaySceneCameraTPS : public IState , public IObserver<SceneMessageType>
{
public:
	//�Y�[�����
	enum class ZoomState
	{
		NONE,             //�ʏ�
		ZOOM_IN,		  //�Y�[�����
		ZOOM_OUT		  //�Y�[���A�E�g���
	};
public:
	//�}�E�X���W
	static constexpr DirectX::SimpleMath::Vector2 MOUSE_POSITION{640.0f,320.0f};

	//�}�E�X���x
	static constexpr float MOUSE_SENSITIVITY = 0.0005f;
	//�J�����̌��E�p�x
	static constexpr float ROTATE_LIMIT = 1.5f;

	// �^�[�Q�b�g����̃f�t�H���g����
	const float CAMERA_DISTANCE = 4.0f;

	//�Y�[������
	static constexpr DirectX::SimpleMath::Vector3 ZOOM_DIRECTION{0.2f, 0.0f, -1.0f};
	//�Y�[���ɂ����鎞��
	static constexpr float ZOOME_MAX_TIME = 0.2f;;

public:
	//�R���X�g���N�^
	PlaySceneCameraTPS(PlaySceneCameraStateMachine* stateMachine,PlaySceneCamera* camera);
	//�f�X�g���N�^
	~PlaySceneCameraTPS() override;

	// �X�V����
	void Update(const float& deltaTime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;

	//�ʒm���󂯎��֐�
	void Notify(SceneMessageType type, void* datas) override;


private:

	//�}�E�X����
	void MouseOperation();
	//�Y�[���̍X�V
	void ZoomUpdate(const float& deltaTime);

	//�h��
	void Shake(const float& deltaTime);

private:
	//�J����
	PlaySceneCamera* m_camera;
	//�X�e�[�g�}�V�[��
	PlaySceneCameraStateMachine* m_stateMAchine;
	//����]
	float m_rotationX;
	//�c��]
	float m_rotationY;
	//�Y�[�����
	ZoomState m_zoomState;
	//�Y�[���̈ړ���
	DirectX::SimpleMath::Vector3 m_zoomMovement;
	//�Y�[������
	float m_zoomTime;

};