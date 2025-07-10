#pragma once
#include "GameBase/Actor.h"
#include "GameBase/Messenger/IObserver.h"
#include "Game/Messenger/Scene/SceneMessageType.h"
#include "Game/Weapon/WeaponBase.h"
#include "Game/Weapon/Boomerang/Boomerang.h"


class Boomerang;
class Player;

class WeaponManager : public Actor,  public IObserver<SceneMessageType>
{
public:
	
	//特定状態のブーメラン１つをの取得
	Boomerang* GetBoomerang(BoomerangState getState);


public:
	//コンストラクタ
	WeaponManager(Scene* scene,Player* player);
	//デストラクタ
	~WeaponManager() override;


	void Notify(SceneMessageType type, void*) override;

private:



private:
	//ブーメラン
	std::vector<Boomerang*> m_boomerangs;

	//手に持っているの武器
	WeaponBase<BoomerangState>* m_holdWeapon;

};

