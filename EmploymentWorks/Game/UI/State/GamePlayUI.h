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

class EnemyManager;
namespace WataLib 
{
	class DamageCountUI;
}


class GamePlayUI : public IState ,  public IObserver
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

	static constexpr DirectX::SimpleMath::Vector2 MOVEPOSITION = { -50.0f,0.0f };

	static constexpr int MAXDAMAGEUICOUNT = 10;

public:
	//�R���X�g���N�^
	GamePlayUI() ;
	//�f�X�g���N�^
	~GamePlayUI() override;

	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//������
	void Initialize(CommonResources* resources) override;
	// �X�V����
	void Update(const float& elapsedTime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;

	//�K�v�ȃ|�C���^�̓o�^
	void AddPointer(Player* player, EnemyManager* enemyManager);

	//�摜�̓ǂݍ���
	std::unique_ptr<UserInterface> AddTexture(const wchar_t* path
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		);



	void CreateEnemyHP();

	void CreatePlayerHP();

	void CreateBoomerang();

	void CreateDamageUI(void* datas);

	//IObserver
//�ʒm���ɌĂ΂��֐�
	void Notify(EventParams::EventType type, void* datas)  override;


private:

	


private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�v���C�Ay
	Player* m_player;
	//�v���C��HP
	std::vector<std::unique_ptr<UserInterface>> m_playerHP;
	//�u�[�������c�@			 
	std::vector<std::unique_ptr<UserInterface>> m_boomerang;

	std::unique_ptr<UserInterface> m_enemyHP;
	std::vector<std::unique_ptr<UserInterface>> m_enemyHPBase;
	//�A�C�e�����������Ƃ���UI
	std::unique_ptr<UserInterface> m_itemAcquisitionUI;

	//������Ԃ�UI
	std::vector<std::unique_ptr<UserInterface>> m_throwUI;

	EnemyManager* m_enemyManager;

	std::pair<int, int> m_windowSize;

	//���W
	DirectX::SimpleMath::Vector3 m_position;
	//�傫��
	DirectX::SimpleMath::Vector3 m_scale;
	//��]
	DirectX::SimpleMath::Quaternion m_rotation;
	
	int m_playerHPCount;

	int m_boomerangCount;

	std::vector<std::unique_ptr<WataLib::DamageCountUI>> m_damageCountUI;
	


};