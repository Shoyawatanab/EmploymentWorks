/*
	�N���X��     : WeaponManager
	����         : ����̃}�l�[�W���[
	�⑫�E���ӓ_ :
*/
#pragma once
#include "GameBase/Actor.h"
#include "Game/Weapon/WeaponBase.h"
#include "Game/Weapon/Boomerang/Boomerang.h"
#include "Game/Messenger/Messengers.h"


class Boomerang;
class Player;

class WeaponManager : public Actor
{
public:
	
	//�����Ԃ̃u�[�������P���̎擾
	Boomerang* GetBoomerang(BoomerangState getState);


public:
	//�R���X�g���N�^
	WeaponManager(Scene* scene,Player* player);
	//�f�X�g���N�^
	~WeaponManager() override;


	void Notify(SceneMessageType type, void*);

private:



private:
	//�u�[������
	std::vector<Boomerang*> m_boomerangs;

	//��Ɏ����Ă���̕���
	WeaponBase<BoomerangState>* m_holdWeapon;

};

