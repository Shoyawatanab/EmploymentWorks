/*
* �v���C���̒ʏ��ԃN���X
*/
#pragma once
#include <unordered_map>
#include "Game/Interface/IUIState.h"
#include "Game/Interface/IObserver.h"

#include "Libraries/WataLib/UserInterface.h"


class Player;
class UserInterface;

class ThrowQuantity;
class BossEnemyHP;

namespace WataLib 
{
	class DamageCountUI;
}


class GamePlayUI : public IUIState,  public IObserver<GamePlayMessageType>
{

private :

	//�v���C��HP�֌W
	static constexpr int HP_COUNT{ 3 };
	static constexpr DirectX::SimpleMath::Vector2 HP_POSITION        { 50.0f,680.0f};
	static constexpr DirectX::SimpleMath::Vector2 HP_POSITION_OFFSET { 70.0f,1.0f};
	static constexpr DirectX::SimpleMath::Vector2 HP_SCALE { 1.0f,1.0f};
	//�u�[�������֌W
	static constexpr DirectX::SimpleMath::Vector2 BOOMERANG_POSITION        { 50.0f, 600.0f};
	static constexpr DirectX::SimpleMath::Vector2 BOOMERANG_POSITION_OFFSET { 70.0f, 1.0f};
	static constexpr DirectX::SimpleMath::Vector2 BOOMERANG_SCALE { 0.1f, 0.1f};

	static constexpr DirectX::SimpleMath::Vector2 MOVEPOSITION = { -50.0f,0.0f };

	static constexpr int MAXDAMAGEUICOUNT = 10;


	//�u�[�������̓�������UI
	static constexpr DirectX::SimpleMath::Vector2 RIGHT_THROW_POSITION {1220, 500};
	static constexpr DirectX::SimpleMath::Vector2 RIGHT_THROW_SCALE {0.2f, 0.2f};
	
	static constexpr DirectX::SimpleMath::Vector2 FRONT_THROW_POSITION {1220, 550};
	static constexpr DirectX::SimpleMath::Vector2 FRONT_THROW_SCALE {0.2f, 0.2f};
	
	static constexpr DirectX::SimpleMath::Vector2 LEFT_THROW_POSITION {1220, 600};
	static constexpr DirectX::SimpleMath::Vector2 LEFT_THROW_SCALE {0.2f, 0.2f};



public:
	//�R���X�g���N�^
	GamePlayUI() ;
	//�f�X�g���N�^
	~GamePlayUI() override;

	void Render(const DirectX::SimpleMath::Matrix& view, const DirectX::SimpleMath::Matrix& projection) override;
	//������
	void Initialize(CommonResources* resources) ;
	// �X�V����
	void Update(const float& elapsedTime) override;
	//��Ԃɓ�������
	void Enter() override;
	//��Ԃ𔲂�����
	void Exit() override;


	//�摜�̓ǂݍ���
	std::unique_ptr<UserInterface> AddTexture(std::string key
		, DirectX::SimpleMath::Vector2 position
		, DirectX::SimpleMath::Vector2 scale
		);

private:
	//�v���C��HP�̍쐬
	void CreatePlayerHP();
	//�u�E�[������UI�̍쐬
	void CreateBoomerang();
	//�_���[�WUI�̍쐬
	void CreateDamageUI(void* datas);


	//IObserver
//�ʒm���ɌĂ΂��֐�
	void Notify(const Telegram<GamePlayMessageType>& telegram)  override;

private:
	//�v���C�����_���[�W���󂯂���
	void PlayerDamage();

private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�v���C�Ay
	Player* m_player;
	//�v���C��HP
	std::vector<std::unique_ptr<UserInterface>> m_playerHP;
	//�u�[�������c�@			 
	std::vector<std::unique_ptr<UserInterface>> m_boomerang;

	//�A�C�e�����������Ƃ���UI
	std::unique_ptr<UserInterface> m_itemAcquisitionUI;

	//������Ԃ�UI
	std::vector<std::unique_ptr<UserInterface>> m_throwUI;


	std::unique_ptr<ThrowQuantity> m_throwQuantityUI;
	std::unique_ptr<BossEnemyHP> m_bossEnemyHP;


	//��ʃT�C�Y
	std::pair<int, int> m_windowSize;

	//���W
	DirectX::SimpleMath::Vector3 m_position;
	//�傫��
	DirectX::SimpleMath::Vector3 m_scale;
	//��]
	DirectX::SimpleMath::Quaternion m_rotation;
	//�v���C��HP
	int m_playerHPCount;
	//�u�[�������̐�
	int m_boomerangCount;
	//�_���[�WUI
	std::vector<std::unique_ptr<WataLib::DamageCountUI>> m_damageCountUI;
	


};