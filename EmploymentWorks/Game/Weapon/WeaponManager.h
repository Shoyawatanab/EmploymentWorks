#pragma once
#include "GameBase/Actor.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"
#include "Game/Weapon/WeaponBase.h"


class Boomerang;
class Player;

class WeaponManager : public Actor,  public IObserver<SceneMessageType>
{
public:
	
	//�����Ԃ̃u�[�������P���̎擾
	Boomerang* GetBoomerang(WeaponBase::WeaponState getState);


public:
	//�R���X�g���N�^
	WeaponManager(Scene* scene,Player* player);
	//�f�X�g���N�^
	~WeaponManager() override;

	// �P�̍X�V
	void UpdateActor(const float& deltaTime) override;

	void Notify(SceneMessageType type, void*) override;

private:


private:
	//�u�[������
	std::vector<Boomerang*> m_boomerangs;

	//��Ɏ����Ă���̕���
	WeaponBase* m_holdWeapon;
};

