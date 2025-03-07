#pragma once
#include "Game/Entities/ItemEntity.h"

// �O���錾
class CommonResources;
class Player;



class ItemAcquisition
{

public:

	enum class State
	{
		Recoverable     //����\
		,NotReturnable  //����s��
	};

	struct  ItemDatas
	{
		State State;
		int ID;
		ItemEntity* ItemEntity;
	};

public:

	static ItemAcquisition* GetInstance();

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

	Player* m_player;

	std::vector<ItemDatas> m_items;


private:

	//�R���X�g���N�^
	ItemAcquisition() {};

	ItemAcquisition(const ItemAcquisition&) = delete;
	ItemAcquisition& operator=(const ItemAcquisition&) = delete;


};