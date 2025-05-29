/*
* �v���C���̒ʏ��ԃN���X
*/
#pragma once
#include <unordered_map>
#include "Game/Interface/IState.h"

//�O���錾
class Player;
class UserInterface;
class PlayScene;



class GameEndUI : public IState
{
private :

	//���߂̉����\�����Ȃ����ԁ@�i�G�̓|���A�j���[�V�������I���܂ł̎��ԁj
	static constexpr float ENEMYANIMATIONTIME{ 3.0f };


	//UI�̒��S���W
	static constexpr DirectX::SimpleMath::Vector2 CENTERPOSITION {640,360};
	//�A�j���[�V��������
	static constexpr float MAXANIMATIONTIME{ 1.5f };
	//�ő�̑傫��
	static constexpr DirectX::SimpleMath::Vector2 ENDSCSLE { 1.0f, 1.0f };
	//�eUI�̍ŏI���W
	static constexpr DirectX::SimpleMath::Vector2 BACKGRAUNDENDPOSITION {640, 360};
	static constexpr DirectX::SimpleMath::Vector2 TITLEUIENDPOSITION {640, 500 };
	static constexpr DirectX::SimpleMath::Vector2 RETRYUIENDPOSITION {640, 370 };
	//�g�嗦
	static constexpr float EXPANSION{ 1.5f };

	static constexpr DirectX::SimpleMath::Vector2 CHANGEUI_POSITION {200, 650};
	static constexpr DirectX::SimpleMath::Vector2 CHANGEUI_SCALE{0.4f, 0.4f};

	static constexpr DirectX::SimpleMath::Vector2 DECISIONUI_POSITION{570, 650};
	static constexpr DirectX::SimpleMath::Vector2 DECISIONUI_SCALE {0.4f, 0.4f};
	
	static constexpr DirectX::SimpleMath::Vector2 ARROW_UP_POSITION{450, 360};
	static constexpr DirectX::SimpleMath::Vector2 ARROW_DOWN_POSITION2{450, 500};
	static constexpr DirectX::SimpleMath::Vector2 ARROW_SCALE{0.2f, 0.2f};


public:

	//���
	enum  class State
	{
		TITLE
		,RETRY

	};

public:
	//�R���X�g���N�^
	GameEndUI() ;
	//�f�X�g���N�^
	~GameEndUI() override;
	//�`��
	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//������
	void Initialize(CommonResources* resources) ;
	// �X�V����
	void Update(const float& elapsedTime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;

	//�K�v�ȃ|�C���^�̓o�^
	void AddPointer(PlayScene* playScene);


	/// <summary>
	/// �w�i�̐ݒ�
	/// </summary>
	/// <param name="isClear"> ture :�N���A  false: �Q�[���I�[�o�[ </param>
	void SetBackGraund(const bool& isClear) {

		if (isClear)
		{
			m_backGraund = m_clearBackGraund.get();
		}
		else
		{
			m_backGraund = m_overBackGraund.get();
			m_enemyAnimationTime = ENEMYANIMATIONTIME;
		}

	}

private:
	//�摜�̍쐬
	void CreateTexture();

	//�A�j���[�V����
	void Animation(const float& elapsedTime);




private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�v���C�Ay
	Player* m_player;
	//�w�i
	std::unique_ptr<UserInterface> m_clearBackGraund;
	std::unique_ptr<UserInterface> m_overBackGraund;
	//�^�C�g��UI	
	std::unique_ptr<UserInterface> m_titleUI;
	//���U���gUI	
	std::unique_ptr<UserInterface> m_reTryUI;
	//���
	State m_state;
	//�g�p�w�i
	UserInterface* m_backGraund;
	//�v���C�V�[��
	PlayScene* m_playScene;
	//�摜
	std::vector < std::unique_ptr<UserInterface>> m_textures;
	
	std::unique_ptr<UserInterface> m_arrow;
	//��ʃT�C�Y
	std::pair<int, int> m_windowSize;
	//���W
	DirectX::SimpleMath::Vector3 m_position;
	//�傫��
	DirectX::SimpleMath::Vector3 m_scale;
	//��]
	DirectX::SimpleMath::Quaternion m_rotation;
	//�A�j���[�V��������
	float m_animationTime;

	float m_enemyAnimationTime;

};