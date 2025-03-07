/*
* �v���C���̒ʏ��ԃN���X
*/
#pragma once
#include <unordered_map>
#include "Game/Interface/IState.h"
#include "Game/Interface/IObserver.h"

#include "Libraries/WataLib/UserInterface.h"


class Player;
class UserInterface;

namespace WataLib
{
	class DrawTexture;
}

class GameOverUI : public IState ,  public IObserver
{

private :

	static constexpr int HP_COUNT{ 3 };
	static constexpr DirectX::SimpleMath::Vector2 HP_POSITION        { 50.0f,680.0f};
	static constexpr DirectX::SimpleMath::Vector2 HP_POSITION_OFFSET { 70.0f,1.0f};
	static constexpr DirectX::SimpleMath::Vector2 HP_SCALE { 1.0f,1.0f};

	static constexpr int BOOMERANG_COUNT{ 3 };
	static constexpr DirectX::SimpleMath::Vector2 BOOMERANG_POSITION        { 50.0f, 600.0f};
	static constexpr DirectX::SimpleMath::Vector2 BOOMERANG_POSITION_OFFSET { 70.0f, 1.0f};
	static constexpr DirectX::SimpleMath::Vector2 BOOMERANG_SCALE { 0.1f, 0.1f};

public:
	//�R���X�g���N�^
	GameOverUI() ;
	//�f�X�g���N�^
	~GameOverUI() override;

	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;

	//�K�v�ȃ|�C���^�̓o�^
	void AddPointer(Player* player);

private:

	//�摜�̓ǂݍ���
	std::unique_ptr<UserInterface> AddTexture(const wchar_t* path
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		, ANCHOR anchor
		, UserInterface::Kinds kind);



	void CreateEnemyHP();

	void CreatePlayerHP();

	void CreateBoomerang();



//�p���֐�
public:
//IState
	//������
	void Initialize(CommonResources* resources) override;
	// �X�V����
	void Update(const float& elapsedTime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;


	//IObserver
//�ʒm���ɌĂ΂��֐�
	void Notify(EventManager::EventTypeName type) override;

public:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�v���C�Ay
	Player* m_player;
	//�v���C��HP
	std::vector<std::unique_ptr<WataLib::DrawTexture>> m_playerHP;
	//�u�[�������c�@
	std::vector<std::unique_ptr<WataLib::DrawTexture>> m_boomerang;

	std::unique_ptr<UserInterface> m_enemyHP;
	std::vector<std::unique_ptr<UserInterface>> m_enemyHPBase;



private :

	std::pair<int, int> m_windowSize;

	//���W
	DirectX::SimpleMath::Vector3 m_position;
	//�傫��
	DirectX::SimpleMath::Vector3 m_scale;
	//��]
	DirectX::SimpleMath::Quaternion m_rotation;
	
	int m_playerHPCount;

	int m_boomerangCount;
	

};