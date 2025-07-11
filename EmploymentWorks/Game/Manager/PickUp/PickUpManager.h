/*
	�N���X��     : PickUpManager
	����         : �E������}�l�[�W���[
	�⑫�E���ӓ_ :
*/
#pragma once
#include <unordered_map>
#include "GameBase/WataLib/Singleton.h"

class PickerComponent;
class PickableComponent;

class PickUpManager
{
public:
	//�E�����
	enum  class PickUpType
	{
		PLAYER_PICKUP_WEAPON            //�v���C����������E��
	};


public:
	//�R���X�g���N
	PickUpManager();
	//�f�X�g���N�^
	~PickUpManager();
	//�X�V����
	void Update(const float& deltaTime);

	//����̎��s
	void TryPickUp(PickerComponent* comp);


	//����҂̒ǉ�
	void AddPicker(PickUpType type, PickerComponent* comp);
	//�E���镨�̒ǉ�
	void AddPickable(PickUpType type, PickableComponent* comp);

private:

	//����\��
	PickableComponent* CheckPickUp(PickerComponent* picker , std::vector<PickableComponent*> picktables);

private:

	//�i�[�z��@�@
	std::unordered_map<PickUpType, std::pair<PickerComponent*, std::vector<PickableComponent*>>> m_list;


};