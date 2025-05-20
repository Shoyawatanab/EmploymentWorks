#pragma once
#include "Game/Entities/ItemEntity.h"
#include "Libraries/WataLib/Singleton.h"

// �O���錾
class CommonResources;
class Player;



class ItemAcquisition : public Singleton<ItemAcquisition>
{

public:

	enum class State
	{
		RECOVERABLE     //����\
		,NOT_RECOVERABLE  //����s��
	};

	struct  ItemDatas
	{
		State State;
		int ID;
		ItemEntity* ItemEntity;
	};

	static constexpr float RECOVERBLE_RADIUS = 2.0f;

public:

	//�R���X�g���N�^
	ItemAcquisition();
	//�f�X�g���N�^
	~ItemAcquisition();

	//������
	void Initialize(CommonResources* resources);
	//�X�V
	void Update();
	//�A�C�e���̓o�^
	void AddItem(int id,ItemEntity* item);
	//�A�C�e���̍폜
	void DeleteItem(int id);

	//�v���C���̒ǉ�
	void AddPlayer(Player* player);



private:
	// ���ʃ��\�[�X
	CommonResources* m_commonResources;
	//�v���C��
	Player* m_player;
	//�A�C�e��
	std::vector<ItemDatas> m_items;




private:



};