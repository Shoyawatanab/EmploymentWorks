#pragma once
#include "Game/Entities/UIBaseEntity.h"
#include "Game/Interface/IObserver.h"

class UserInterface;

class BossEnemyHP : public UIBaseEntity , public IObserver<GamePlayMessageType>
{

private:


	//�{�XHP�֌W
	static constexpr DirectX::SimpleMath::Vector2 ENEMY_HP_BASE_POSITION{640, 50};
	static constexpr DirectX::SimpleMath::Vector2 ENEMY_HP_BASE_SCALE{0.9f, 0.5f};

	static constexpr DirectX::SimpleMath::Vector2 ENEMY_HP_POSITION     {640, 50};
	static constexpr DirectX::SimpleMath::Vector2 ENEMY_HP_SCALE        {0.9f, 0.39f};

	static constexpr DirectX::SimpleMath::Vector2 ENEMY_NAME_POSITION     {640, 25};
	static constexpr DirectX::SimpleMath::Vector2 ENEMY_NAME_SCALE        {0.3f, 0.3f};


public:
	//�R���X�g���N�^
	BossEnemyHP(CommonResources* resources);
	//�f�X�g���N�^
	~BossEnemyHP();

	//������
	void Initialize();
	//�X�V����
	void  Update(const float& elapsedTime);
	//�`��
	void Render();

private:

	//IObserver
//�ʒm���ɌĂ΂��֐�
	void Notify(const Telegram<GamePlayMessageType>& telegram)  override;


private:


	std::unique_ptr<UserInterface> m_enemyName;
	std::unique_ptr<UserInterface> m_enemyHP;
	std::unique_ptr<UserInterface> m_enemyHPBase;


};